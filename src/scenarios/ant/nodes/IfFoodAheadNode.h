#ifndef IFFOODAHEADNODE_H
#define IFFOODAHEADNODE_H

#include "../../../gp/Node.h"

/**
 * {@link Ant} node for detecting if there is food in the cell ahead.
 * @author David Bennett
 */
class IfFoodAheadNode : public Node
{
public:
    /** Constructs the node with an arity of 2 and the name 'IfFoodAhead'. */
    IfFoodAheadNode() : Node(2, "IfFoodAhead") { }

    /** Executes the first child if there is food ahead, otherwise the second. */
    void evaluate(Individual *individual, QStack<Node *> *programStack);

    /** Clones the node. */
    Node *clone() const;

    /** Create a new {@link IfFoodAheadNode} */
    static Node *create() { return new IfFoodAheadNode(); }
};

#endif // IFFOODAHEADNODE_H
