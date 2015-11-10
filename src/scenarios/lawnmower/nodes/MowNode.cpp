#include "MowNode.h"
#include "../Lawnmower.h"

void MowNode::evaluate(Individual *individual, QStack<Node *> *programStack)
{
    Q_UNUSED(programStack);
    Q_ASSERT(children.size() == arity);

    Lawnmower *lawnmower = (Lawnmower *) individual;
    Environment *env = lawnmower->getEnvironment();

    switch (lawnmower->getFacing())
    {
    case Lawnmower::UP:
        lawnmower->setY((lawnmower->getY() - 1 + env->getHeight()) % env->getHeight());
        break;

    case Lawnmower::RIGHT:
        lawnmower->setX((lawnmower->getX() + 1) % env->getWidth());
        break;

    case Lawnmower::DOWN:
        lawnmower->setY((lawnmower->getY() + 1) % env->getHeight());
        break;

    case Lawnmower::LEFT:
        lawnmower->setX((lawnmower->getX() - 1 + env->getWidth()) % env->getWidth());
        break;

    default:
        Q_ASSERT_X(false, "MowNode::evaluate", "Invalid facing direction");
    }

    if (env->mowTile(lawnmower->getX(), lawnmower->getY()))
        lawnmower->incrementPoints();

    lawnmower->incrementMoves();
}

Node *MowNode::clone() const
{
    Node *newNode = MowNode::create();

    foreach (Node *child, children)
        newNode->addChild(child->clone());

    return newNode;
}
