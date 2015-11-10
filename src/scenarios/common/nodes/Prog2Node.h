#ifndef PROG2NODE_H
#define PROG2NODE_H

#include "../../../gp/Node.h"

/**
 * {@link Lawnmower} node for joining two child nodes together.
 */
class Prog2Node : public Node
{
public:
    /** Constructs the node with an arity of 2 and the name 'Prog2' */
    Prog2Node() : Node(2, "Prog2") { }

    /** Evaluate child nodes from left to right. */
    void evaluate(Individual *individual, QStack<Node *> *programStack);

    /** Clones the node. */
    Node *clone() const;

    /** Create a new {@link LeftNode} */
    static Node *create() { return new Prog2Node(); }
};

#endif // PROG2NODE_H
