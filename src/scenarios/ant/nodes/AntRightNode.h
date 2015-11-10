#ifndef ANTRIGHTNODE_H
#define ANTRIGHTNODE_H

#include "../../../gp/Node.h"

/**
 * {@link Ant} node for turning right 90&deg;.
 * @author David Bennett
 */
class AntRightNode : public Node
{
public:
    /** Constructs the node with an arity of 0 and the name 'Right'. */
    AntRightNode() : Node(0, "Right") { }

    /** Turns the {@link Ant} right 90&deg;. */
    void evaluate(Individual *individual, QStack<Node *> *programStack);

    /** Clones the node. */
    Node *clone() const;

    /** Create a new {@link AntRightNode} */
    static Node *create() { return new AntRightNode(); }
};

#endif // ANTRIGHTNODE_H
