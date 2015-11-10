#ifndef NODE_H
#define NODE_H

#include <QVector>
#include <QStack>
#include <QString>
#include "Individual.h"

class Individual;

/**
 * Base node class for program trees.
 * @author David Bennett
 */
class Node
{
public:
    /**
     * Construct the node with the given arity.
     * @param arity The number of children the node should have.
     * @param name Name of the node.
     */
    Node(int arity, QString name) : arity(arity), name(name), parent(NULL) { }

    /**
     * Destructs the node, deleting its children recursively.
     */
    virtual ~Node();

    /**
     * Evaluate the node, performing its actions.
     * Functional nodes should evaluate their children recursively, using the <code>programStack</code>.
     * @param individual Reference the to the {@link Individual} the tree belongs to.
     * @param programStack Program stack, needed for recursion.
     */
    virtual void evaluate(Individual *individual, QStack<Node *> *programStack) = 0;

    /**
     * Creates a deep-copy of this node.
     * @return A deep-copy of this node.
     */
    virtual Node *clone() const = 0;

    /**
     * Get the children of this node.
     * @return The children of this node.
     */
    QVector<Node *> getChildren() const { return children; }

    /**
     * Get the number of children this node has.
     * @return The number of children this node has.
     */
    int getNumChildren() const { return children.size(); }

    /**
     * Add a child to this node.
     * Will fail to add if the number of children equals the arity.
     * @param child Child node to add.
     */
    void addChild(Node *child);

    /**
     * Replace a child node with a new node.
     * Deletes the node that is replaced.
     * @param child Child node to replace.
     * @param newChild Node to replace child with.
     * @param deleteOld True to delete the old node, false to keep it (called will gain resposibility for its deletion)
     */
    void replaceChild(Node *child, Node *newChild, bool deleteOld = true);

    /**
     * Clears the children of this node.
     * Deletes the children.
     */
    void clearChildren();

    /**
     * Get the parent node of this node.
     * @return The parent node of this node, NULL if this node has no parent.
     */
    Node *getParent() { return parent; }

    /**
     * Get the total number of nodes in this tree, including the root node.
     * @return The total number of nodes in this tree.
     */
    int getSize() const;

    /**
     * Get the number of levels in the tree, including the root level.
     * @return The number of levels in the tree.
     */
    int getHeight() const;

    /**
     * Get the depth of the current node in the tree.
     * 0 depth is root.
     * @return
     */
    int getDepth() const;

    /**
     * Get the number of children this node should have.
     * Does not necessarily have this number of children.
     * @return
     */
    int getArity() const { return arity; }

    /**
     * Get a reference to a child {@link Node} by its index.
     * Depth-first numbering is used, starting from 0 (being the root node).
     * @param index Index of the node to get.
     * @return A reference to the requested {@link Node} in the tree.
     */
    Node *getNode(const int index);

    /**
     * Get the name of this node.
     * @return The name of this node.
     */
    QString getName() const { return name; }

    /**
     * Formats this node as a string.
     * Using LISP-like syntax.
     * E.g. (Prog2 (Prog2 (Mow) (Mow)) (Left)).
     * @return The node as a string.
     */
    QString toString() const;

protected:
    const int arity; /**< The number of child nodes this node should have. */
    const QString name; /**< The name of this node. */
    Node *parent; /**< The parent of this node. */
    QVector<Node *> children; /**< The children of this node. */
};

/**
 * A pointer to a function to create an instance of a node.
 */
typedef Node* (*CreateNode)();

#endif // NODE_H
