#include "Prog2Node.h"

void Prog2Node::evaluate(Individual *individual, QStack<Node *> *programStack)
{
    Q_UNUSED(individual);
    Q_ASSERT(children.size() == arity);
    Q_ASSERT(children[0] != NULL);
    Q_ASSERT(children[1] != NULL);

    programStack->push(children[1]);
    programStack->push(children[0]);
}

Node *Prog2Node::clone() const
{
    Node *newNode = Prog2Node::create();

    foreach (Node *child, children)
        newNode->addChild(child->clone());

    return newNode;
}
