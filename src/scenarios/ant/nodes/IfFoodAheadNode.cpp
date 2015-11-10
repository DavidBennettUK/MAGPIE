#include "IfFoodAheadNode.h"
#include "../Ant.h"

void IfFoodAheadNode::evaluate(Individual *individual, QStack<Node *> *programStack)
{
    Q_UNUSED(programStack);
    Q_ASSERT(children.size() == arity);

    Ant *ant = (Ant *) individual;

    if (ant->isFoodInFront())
        programStack->push(children[0]);
    else
        programStack->push(children[1]);
}

Node *IfFoodAheadNode::clone() const
{
    Node *newNode = IfFoodAheadNode::create();

    foreach (Node *child, children)
        newNode->addChild(child->clone());

    return newNode;
}
