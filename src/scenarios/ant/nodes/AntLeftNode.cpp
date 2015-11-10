#include "AntLeftNode.h"
#include "../Ant.h"

void AntLeftNode::evaluate(Individual *individual, QStack<Node *> *programStack)
{
    Q_UNUSED(programStack);
    Q_ASSERT(children.size() == arity);

    Ant *ant = (Ant *) individual;
    ant->turn(true);
}

Node *AntLeftNode::clone() const
{
    Node *newNode = AntLeftNode::create();

    foreach (Node *child, children)
        newNode->addChild(child->clone());

    return newNode;
}
