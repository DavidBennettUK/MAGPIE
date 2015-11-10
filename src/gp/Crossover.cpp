#include "Crossover.h"

const CrossoverResult Crossover::crossover(Node *tree1, Node *tree2)
{
    Q_ASSERT(tree1);
    Q_ASSERT(tree2);

    CrossoverResult result = {0,0};

    // Only do crossover if both trees have more than one node
    if (tree1->getArity() == 0 || tree2->getArity() == 0)
        return result;

    Node *node1 = NULL, *node2 = NULL;

    // Get the crossover nodes, ensuring max depth constraint is upheld
    // TODO add max amount of tries? probably slows things down a lot
    do
    {
        result.point1 = getCrossoverPoint(tree1);
        result.point2 = getCrossoverPoint(tree2);

        node1 = tree1->getNode(result.point1);
        node2 = tree2->getNode(result.point2);
    }
    while (node1->getDepth() + node2->getHeight() > treeFactory->getMaxHeight() ||
           node2->getDepth() + node1->getHeight() > treeFactory->getMaxHeight());

    // Swap the subtrees
    Node *parent1 = node1->getParent();
    Node *parent2 = node2->getParent();
    parent1->replaceChild(node1, node2, false);
    parent2->replaceChild(node2, node1, false);

    return result;
}

int Crossover::getCrossoverPoint(Node *tree) const
{
    Q_ASSERT(tree);

    // Don't pick the root node, so start from 1
    return qrand() % (tree->getSize() - 1) + 1;
}

