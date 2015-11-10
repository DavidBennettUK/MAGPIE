#ifndef MUTATION_H
#define MUTATION_H

#include "TreeFactory.h"
#include "Node.h"

/**
 * Helper class to perform mutation operations on a tree.
 * Performs single-point mutation.
 * @author David Bennett
 */
class Mutation
{
public:
    /**
     * Construct the class with a {@link TreeFactory} reference.
     * A {@link TreeFactory} reference is needed to get {@link Node}s from the terminal
     * and functional sets to replace the mutation node with.
     * @param treeFactory Reference to a {@link TreeFactory}, usually belonging to the current
     * {@link Scenario}.
     */
    Mutation(const TreeFactory *treeFactory) : treeFactory(treeFactory) { }

    /**
     * Performs point-mutation at a random point in the tree.
     * The old node at the mutation point will be deleted.
     * @param tree The tree to perform mutation on.
     */
    void mutate(Node *tree);

private:
    /**
     * Reference to a {@link TreeFactory}, usually from the current {@link Scenario}.
     * Needed to obtain nodes from the terminal and functional sets.
     */
    const TreeFactory *treeFactory;

    /**
     * Gets a random mutation point on the tree.
     * @param tree Tree to find a random mutation point for.
     * @return A random mutation point.
     */
    int getMutationPoint(Node *tree) const;
};

#endif // MUTATION_H
