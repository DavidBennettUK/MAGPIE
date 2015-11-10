#include "LeftNode.h"
#include "../Lawnmower.h"

void LeftNode::evaluate(Individual *individual, QStack<Node *> *programStack)
{
    Q_UNUSED(programStack);
    Q_ASSERT(children.size() == arity);

    Lawnmower *lawnmower = (Lawnmower *) individual;
    int newDir = (lawnmower->getFacing() - 1 + 4) % 4;
    lawnmower->setFacing((Lawnmower::Facing) newDir);

    lawnmower->incrementMoves();
}

Node *LeftNode::clone() const
{
    Node *newNode = LeftNode::create();

    foreach (Node *child, children)
        newNode->addChild(child->clone());

    return newNode;
}
