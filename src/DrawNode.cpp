#include <QQueue>
#include "DrawNode.h"
#include "common.h"

DrawNode::DrawNode(Node *tree, DrawNode *parent, int depth, int number)
{
    x = -1.0f;
    y = depth;
    this->parent = parent;
    thread = NULL;
    offset = 0;
    change = 0;
    shift = 0;
    mod = 0;
    ancestor = this;
    this->number = number;
    this->node = tree;

    for (int i = 0; i < tree->getNumChildren(); i++)
    {
        Node *child = tree->getChildren()[i];
        DrawNode *node = new DrawNode(child, this, depth + 1, i + 1);
        children << node;
    }
}

DrawNode::~DrawNode()
{
    foreach (DrawNode *child, children)
        safeDelete(child);
}

float DrawNode::getWidth()
{
    QPointF bounds = getBoundsH();
    return bounds.y() - bounds.x();
}

float DrawNode::getHeight()
{
    QPointF bounds = getBoundsV();
    return bounds.y() - bounds.x();
}

QPointF DrawNode::getBoundsH()
{
    QQueue<DrawNode *> queue;
    queue.enqueue(this);

    float minX = 0, maxX = 0;

    while (!queue.empty())
    {
        DrawNode *node = queue.dequeue();

        if (node->getX() < minX)
            minX = node->getX();
        if (node->getX() > maxX)
            maxX = node->getX();

        foreach (DrawNode *child, node->children)
            queue.enqueue(child);
    }

    return QPointF(minX, maxX);
}

QPointF DrawNode::getBoundsV()
{
    QQueue<DrawNode *> queue;
    queue.enqueue(this);

    float minY = 0, maxY = 0;

    while (!queue.empty())
    {
        DrawNode *node = queue.dequeue();

        if (node->getY() < minY)
            minY = node->getY();
        if (node->getY() > maxY)
            maxY = node->getY();

        foreach (DrawNode *child, node->children)
            queue.enqueue(child);
    }

    return QPointF(minY, maxY);
}

DrawNode *DrawNode::getNode(int position)
{
    QQueue<DrawNode *> queue;
    queue.enqueue(this);

    for (int i = 0; i < position; i++)
    {
        DrawNode *node = queue.dequeue();

        foreach (DrawNode *child, node->getChildren())
            queue.enqueue(child);
    }

    return queue.front();
}

DrawNode *DrawNode::leftSibling()
{
    DrawNode *n = NULL;

    if (parent)
    {
        foreach (DrawNode *node, parent->children)
        {
            if (node == this)
                return n;
            else
                n = node;
        }
    }

    return n;
}

DrawNode *DrawNode::getLeftmostSibling()
{
    if (parent)
    {
        if (parent->children.first() != this)
            return parent->children.first();
    }

    return NULL;
}

DrawNode *DrawNode::nextRight()
{
    if (children.empty())
        return thread;
    else
        return children.last();
}

DrawNode *DrawNode::nextLeft()
{
    if (children.empty())
        return thread;
    else
        return children.first();
}
