#include "ForwardNode.h"
#include "../Ant.h"

void ForwardNode::evaluate(Individual *individual, QStack<Node *> *programStack)
{
    Q_UNUSED(programStack);
    Q_ASSERT(children.size() == arity);

    Ant *ant = (Ant *) individual;
    ant->moveForward();
}

Node *ForwardNode::clone() const
{
    Node *newNode = ForwardNode::create();

    foreach (Node *child, children)
        newNode->addChild(child->clone());

    return newNode;
}
