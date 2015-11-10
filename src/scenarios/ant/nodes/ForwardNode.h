#ifndef FORWARDNODE_H
#define FORWARDNODE_H

#include "../../../gp/Node.h"

/**
 * {@link Ant} node for moving forward one tile.
 * @author David Bennett
 */
class ForwardNode : public Node
{
public:
    /** Constructs the node with an arity of 0 and the name 'Forward'. */
    ForwardNode() : Node(0, "Forward") { }

    /** Move the {@link Ant} forwards one cell. */
    void evaluate(Individual *individual, QStack<Node *> *programStack);

    /** Clones the node. */
    Node *clone() const;

    /** Create a new {@link ForwardNode} */
    static Node *create() { return new ForwardNode(); }
};

#endif // FORWARDNODE_H
