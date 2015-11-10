#ifndef ANTLEFTNODE_H
#define ANTLEFTNODE_H

#include "../../../gp/Node.h"

/**
 * {@link Ant} node for turning left 90&deg;.
 * @author David Bennett
 */
class AntLeftNode : public Node
{
public:
    /** Constructs the node with an arity of 0 and the name 'Left'. */
    AntLeftNode() : Node(0, "Left") { }

    /** Turns the {@link Ant} left 90&deg;. */
    void evaluate(Individual *individual, QStack<Node *> *programStack);

    /** Clones the node. */
    Node *clone() const;

    /** Create a new {@link AntLeftNode} */
    static Node *create() { return new AntLeftNode(); }
};

#endif // ANTLEFTNODE_H
