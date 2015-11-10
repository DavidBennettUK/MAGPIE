#ifndef MOWMULTINODE_H
#define MOWMULTINODE_H

#include "../../../gp/Node.h"

/**
 * {@link LawnmowerMulti} node for moving forward one tile.
 * @author David Bennett
 */
class MowMultiNode : public Node
{
public:
    /** Constructs the node with an arity of 0 and the name 'Mow'. */
    MowMultiNode() : Node(0, "Mow") { }

    /** Moves the {@link Lawnmower} forward one tile. */
    void evaluate(Individual *individual, QStack<Node *> *programStack);

    /** Clones the node. */
    Node *clone() const;

    /** Create a new {@link LeftNode} */
    static Node *create() { return new MowMultiNode(); }
};

#endif // MOWMULTINODE_H
