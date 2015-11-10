#include "DrawTreeBuilder.h"

DrawTreeBuilder::DrawTreeBuilder(float xSpacing, float ySpacing)
    : xSpacing(xSpacing), ySpacing(ySpacing)
{

}

DrawNode *DrawTreeBuilder::build(Node* tree)
{
    DrawNode *root = new DrawNode(tree);
    firstWalk(root);
    secondWalk(root);
    return root;
}

void DrawTreeBuilder::firstWalk(DrawNode* v)
{
    if (v->children.empty())
    {
        if (v->getLeftmostSibling())
            v->x = v->leftSibling()->x + xSpacing;
        else
            v->x = 0;
    }
    else
    {
        DrawNode *defaultAncestor = v->children.first();

        foreach (DrawNode *w, v->children)
        {
            firstWalk(w);
            defaultAncestor = apportion(w, defaultAncestor);
        }

        executeShifts(v);

        float midpoint = (v->children.first()->x + v->children.last()->x) * 0.5f;

        DrawNode *w = v->leftSibling();

        if (w)
        {
            v->x = w->x + xSpacing;
            v->mod = v->x - midpoint;
        }
        else
            v->x = midpoint;
    }
}

void DrawTreeBuilder::secondWalk(DrawNode *v, float m, int depth)
{
    v->x += m;
    v->y = depth * ySpacing;

    foreach (DrawNode *w, v->children)
        secondWalk(w, m + v->mod, depth + 1);
}

DrawNode *DrawTreeBuilder::apportion(DrawNode *v, DrawNode *defaultAncestor)
{
    DrawNode *w = v->leftSibling();

    if (w)
    {
        DrawNode *vir = v;
        DrawNode *vor = v;
        DrawNode *vil = w;
        DrawNode *vol = vir->getLeftmostSibling();
        float sir = vir->mod;
        float sor = vor->mod;
        float sil = vil->mod;
        float sol = vol->mod;

        while (vil->nextRight() && vir->nextLeft())
        {
            vil = vil->nextRight();
            vir = vir->nextLeft();
            vol = vol->nextLeft();
            vor = vor->nextRight();
            vor->ancestor = v;
            float shift = (vil->x + sil) - (vir->x + sir) + xSpacing;
            if (shift > 0)
            {
                moveSubtree(ancestor(vil, v, defaultAncestor), v, shift);
                sir += shift;
                sor += shift;
            }
            sil += vil->mod;
            sir += vir->mod;
            sol += vol->mod;
            sor += vor->mod;
        }

        if (vil->nextRight() && !vor->nextRight())
        {
            vor->thread = vil->nextRight();
            vor->mod += sil - sor;
        }
        if (vir->nextLeft() && !vol->nextLeft())
        {
            vol->thread = vir->nextLeft();
            vol->mod += sir - sol;
            defaultAncestor = v;
        }
    }

    return defaultAncestor;
}

void DrawTreeBuilder::moveSubtree(DrawNode *wl, DrawNode *wr, float shift)
{
    float subtrees = wr->number - wl->number;
    wr->change -= shift / subtrees;
    wr->shift += shift;
    wl->change += shift / subtrees;
    wr->x += shift;
    wr->mod += shift;
}

void DrawTreeBuilder::executeShifts(DrawNode *v)
{
    float shift = 0;
    float change = 0;

    for (int i = v->children.size() - 1; i >= 0; i--)
    {
        DrawNode *w = v->children[i];
        w->x += shift;
        w->mod += shift;
        change += w->change;
        shift += w->shift + change;
    }
}

DrawNode *DrawTreeBuilder::ancestor(DrawNode *vil, DrawNode *v, DrawNode *defaultAncestor)
{
    if (v->parent == vil->ancestor->parent)
        return vil->ancestor;
    else
        return defaultAncestor;
}
