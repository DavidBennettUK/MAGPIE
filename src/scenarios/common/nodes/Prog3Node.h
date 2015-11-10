#ifndef PROG3NODE_H
#define PROG3NODE_H

#include "../../../gp/Node.h"

class Prog3Node : public Node
{
public:
    Prog3Node() : Node(3, "Prog3") { }

    void evaluate(Individual *individual, QStack<Node *> *programStack);

    /** Clones the node. */
    Node *clone() const;

    /** Create a new {@link Prog3Node} */
    static Node *create() { return new Prog3Node(); }
};

#endif // PROG3NODE_H
