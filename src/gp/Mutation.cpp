#include "Mutation.h"
#include "../common.h"

void Mutation::mutate(Node *tree)
{
    Q_ASSERT(tree);

    // Only do mutation if the tree has more than 1 node
    if (tree->getArity() == 0)
        return;

    // Find a mutation point
    int mutationPoint = getMutationPoint(tree);
    Node *mutationNode = tree->getNode(mutationPoint);
    Node *mutationParent = mutationNode->getParent();

    // Generate a new node to replace mutation node with
    Node *newNode = NULL;

    // Generate a new random node
    // Must have an arity equal or less than the node to replace
    // TODO add a max amount of tries?
    do
    {
        safeDelete(newNode); // delete the previous attempt if needed
        newNode = treeFactory->randomNode();
    }
    while (newNode->getArity() > mutationNode->getArity());

    // Copy the old node's children to the new node
    for (int i = 0; i < newNode->getArity(); i++)
    {
        Node *child = mutationNode->getChildren().at(i);
        newNode->addChild(child->clone());
    }

    mutationParent->replaceChild(mutationNode, newNode, true);
}

int Mutation::getMutationPoint(Node *tree) const
{
    Q_ASSERT(tree);

    // Don't pick the root node, so start from 1
    return qrand() % (tree->getSize() - 1) + 1;
}
