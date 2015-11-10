#include "Prog3Node.h"

void Prog3Node::evaluate(Individual *individual, QStack<Node *> *programStack)
{
    Q_UNUSED(individual);
    Q_ASSERT(children.size() == arity);
    Q_ASSERT(children[0] != NULL);
    Q_ASSERT(children[1] != NULL);

    programStack->push(children[2]);
    programStack->push(children[1]);
    programStack->push(children[0]);
}

Node *Prog3Node::clone() const
{
    Node *newNode = Prog3Node::create();

    foreach (Node *child, children)
        newNode->addChild(child->clone());

    return newNode;
}
