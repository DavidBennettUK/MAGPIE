#ifndef DRAWTREEBUILDER_H
#define DRAWTREEBUILDER_H

#include "DrawNode.h"
#include "gp/Node.h"

/**
 * Wraps a normal {@link Node} tree in a drawable tree structure.
 * This gives each node an x and y coordinate using Buchheim's tree drawing
 * algorithm.
 * @see DrawNode
 */
class DrawTreeBuilder
{
public:
    /**
     * Constructs the draw tree builder.
     * @param xSpacing The amount of space between nodes on the x-axis.
     * @param ySpacing The amount of space between nodes on the y-axis.
     */
    DrawTreeBuilder(float xSpacing = 1, float ySpacing = 1);

    /**
     * Builds a draw tree from the given tree.
     * @param tree The tree to build a draw tree for.
     * @return A pointer to the draw tree, caller takes responsibily for deletion.
     */
    DrawNode *build(Node *tree);

private:
    const float xSpacing; /**< The amount of spacing between nodes on the x-axis. */
    const float ySpacing; /**< The amount of spacing between nodes on the y-axis. */

    /**
     *
     * @param v
     */
    void firstWalk(DrawNode* v);

    /**
     *
     * @param v
     * @param m
     * @param depth
     */
    void secondWalk(DrawNode *v, float m = 0, int depth = 0);

    /**
     *
     * @param v
     * @param defaultAncestor
     * @return
     */
    DrawNode *apportion(DrawNode *v, DrawNode *defaultAncestor);

    /**
     *
     * @param wl
     * @param wr
     * @param shift
     */
    void moveSubtree(DrawNode *wl, DrawNode *wr, float shift);

    /**
     *
     * @param v
     */
    void executeShifts(DrawNode *v);

    /**
     *
     * @param vil
     * @param v
     * @param defaultAncestor
     * @return
     */
    DrawNode *ancestor(DrawNode *vil, DrawNode *v, DrawNode *defaultAncestor);
};

#endif // DRAWTREEBUILDER_H
