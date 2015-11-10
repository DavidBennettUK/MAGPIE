#ifndef IFOBSTACLEAHEADNODE_H
#define IFOBSTACLEAHEADNODE_H

#include "../../../gp/Node.h"

/**
 * {@link LawnmowerMulti} node for checking if an obstacle is in the tile ahead.
 * @author David Bennett
 */
class IfObstacleAheadNode : public Node
{
public:
    /** Constructs the node with an arity of 2 and the name 'IfObstacleAhead'. */
    IfObstacleAheadNode() : Node(2, "IfObsAhead") { }

    /** If an obstacle is ahead execute the first child, otherwise the second. */
    void evaluate(Individual *individual, QStack<Node *> *programStack);

    /** Clones the node. */
    Node *clone() const;

    /** Create a new {@link IfObstacleAheadNode} */
    static Node *create() { return new IfObstacleAheadNode(); }
};

#endif // IFOBSTACLEAHEADNODE_H
