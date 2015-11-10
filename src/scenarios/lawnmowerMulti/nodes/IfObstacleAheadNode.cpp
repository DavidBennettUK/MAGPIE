#include "IfObstacleAheadNode.h"
#include "../LawnmowerMulti.h"

void IfObstacleAheadNode::evaluate(Individual *individual, QStack<Node *> *programStack)
{
    Q_UNUSED(programStack);
    Q_ASSERT(children.size() == arity);

    LawnmowerMulti *lawnmower = (LawnmowerMulti *) individual;
    EnvironmentMulti *env = lawnmower->getEnvironment();
    bool obstacleAhead = false;

    switch (lawnmower->getFacing())
    {
    case Lawnmower::UP:
        obstacleAhead = env->isObstacle(lawnmower->getX(), (lawnmower->getY() - 1 + env->getHeight()) % env->getHeight());
        break;

    case Lawnmower::RIGHT:
        obstacleAhead = env->isObstacle((lawnmower->getX() + 1) % env->getWidth(), lawnmower->getY());
        break;

    case Lawnmower::DOWN:
        obstacleAhead = env->isObstacle(lawnmower->getX(), (lawnmower->getY() + 1) % env->getHeight());
        break;

    case Lawnmower::LEFT:
        obstacleAhead = env->isObstacle((lawnmower->getX() - 1 + env->getWidth()) % env->getWidth(), lawnmower->getY());
        break;

    default:
        Q_ASSERT_X(false, "IfObstacleAheadNode::evaluate", "Invalid facing direction");
    }

    if (obstacleAhead)
        programStack->push(children[0]);
    else
        programStack->push(children[1]);
}

Node *IfObstacleAheadNode::clone() const
{
    Node *newNode = IfObstacleAheadNode::create();

    foreach (Node *child, children)
        newNode->addChild(child->clone());

    return newNode;
}
