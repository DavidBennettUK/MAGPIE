#include "AntRightNode.h"
#include "../Ant.h"

void AntRightNode::evaluate(Individual *individual, QStack<Node *> *programStack)
{
    Q_UNUSED(programStack);
    Q_ASSERT(children.size() == arity);

    Ant *ant = (Ant *) individual;
    ant->turn(false);
}

Node *AntRightNode::clone() const
{
    Node *newNode = AntRightNode::create();

    foreach (Node *child, children)
        newNode->addChild(child->clone());

    return newNode;
}
