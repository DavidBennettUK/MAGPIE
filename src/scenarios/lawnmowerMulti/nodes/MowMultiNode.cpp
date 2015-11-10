#include "MowMultiNode.h"
#include "../LawnmowerMulti.h"

void MowMultiNode::evaluate(Individual *individual, QStack<Node *> *programStack)
{
    Q_UNUSED(programStack);
    Q_ASSERT(children.size() == arity);

    LawnmowerMulti *lawnmower = (LawnmowerMulti *) individual;
    EnvironmentMulti *env = lawnmower->getEnvironment();

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

    if (env->isObstacle(lawnmower->getX(), lawnmower->getY()))
        lawnmower->incrementHits();

    lawnmower->incrementMoves();
}

Node *MowMultiNode::clone() const
{
    Node *newNode = MowMultiNode::create();

    foreach (Node *child, children)
        newNode->addChild(child->clone());

    return newNode;
}
