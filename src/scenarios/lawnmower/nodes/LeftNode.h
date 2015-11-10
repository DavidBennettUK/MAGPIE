#ifndef LEFTNODE_H
#define LEFTNODE_H

#include "../../../gp/Node.h"

/**
 * {@link Lawnmower} node for turning left 90&deg;.
 * @author David Bennett
 */
class LeftNode : public Node
{
public:
    /** Constructs the node with an arity of 0 and the name 'Left'. */
    LeftNode() : Node(0, "Left") { }

    /** Turns the {@link Lawnmower} left 90&deg;. */
    void evaluate(Individual *individual, QStack<Node *> *programStack);

    /** Clones the node. */
    Node *clone() const;

    /** Create a new {@link LeftNode} */
    static Node *create() { return new LeftNode(); }
};

#endif // LEFTNODE_H
