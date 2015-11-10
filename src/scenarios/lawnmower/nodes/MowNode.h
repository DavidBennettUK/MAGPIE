#ifndef MOWNODE_H
#define MOWNODE_H

#include "../../../gp/Node.h"

/**
 * {@link Lawnmower} node for moving forward one tile.
 * @author David Bennett
 */
class MowNode : public Node
{
public:
    /** Constructs the node with an arity of 0 and the name 'Mow'. */
    MowNode() : Node(0, "Mow") { }

    /** Moves the {@link Lawnmower} forward one tile. */
    void evaluate(Individual *individual, QStack<Node *> *programStack);

    /** Clones the node. */
    Node *clone() const;

    /** Create a new {@link LeftNode} */
    static Node *create() { return new MowNode(); }
};

#endif // MOWNODE_H
