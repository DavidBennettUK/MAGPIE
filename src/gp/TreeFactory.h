#ifndef TREEFACTORY_H
#define TREEFACTORY_H

#include "Node.h"

using std::max;

/**
 * Helper class for creating program trees, composed of {@link Node}s.
 * @author David Bennett
 */
class TreeFactory
{
public:
    /** Tree building method. */
    enum Method { GROW, FULL, HALFANDHALF };

    /**
     * Constructs the tree factory.
     * @param maxHeight The maximum number of levels a randomly generated trees can have,
     *                  including the root node.
     * @param functionSet Reference to the set of functional {@link Node}s.
     * @param terminalSet Reference to the set of terminal {@link Node}s.
     */
    TreeFactory(int maxHeight, QVector<CreateNode> *functionSet, QVector<CreateNode> *terminalSet);

    /**
     * Build a random tree from the terminal and functional nodes, constrained to
     * the maximum depth.
     * @return The randomly generated tree.
     */
    Node *build() const;

    /**
     * Build a tree from the given string.
     * Using LISP-like syntax, same as in {@link Node#toString()}.
     * Does not adhere to maximum depth.
     * @param expression Expression to build tree from.
     * @return The generated tree.
     */
    Node *buildFromString(QString expression) const;

    /**
     * Get a random node from the terminal or functional set.
     * @return The randomly chosen {@link Node}.
     */
    Node *randomNode() const;

    /**
     * Get a random node from the functional set.
     * @return The randomly chosen {@link Node}.
     */
    Node *randomFunction() const;

    /**
     * Get a random node from the functional set.
     * @return The randomly chosen {@link Node}.
     */
    Node *randomTerminal() const;

    /**
     * Helper method to get a node from the terminal and functional sets by name.
     * @param nodeName Name of the node to get.
     * @return The {@link Node} with the given name. NULL if the {@link Node} was not found.
     */
    Node *nodeFromString(QString nodeName) const;

    /**
     * Get the maximum number of levels randomly generated trees can have,
     * including the root node.
     * @return The maximum number of levels randomy generated trees can have.
     */
    int getMaxHeight() const { return maxHeight; }

    /**
     * Set the maximum number of levels randomly generated trees can have,
     * including the root node.
     * Must be greater than 0.
     * @param maxHeight The maximum number of levels randomly generated trees can have.
     */
    void setMaxHeight(int maxHeight) { Q_ASSERT(maxHeight > 0); this->maxHeight = max(1,maxHeight); }

private:
    int maxHeight; /**< The maximum number of levels randomly generated trees can have, including the root. */
    QVector<CreateNode> *functionSet; /**< The set of functional nodes than may be used to generate trees. */
    QVector<CreateNode> *terminalSet; /**< The set of terminal nodes that may be used to generate trees. */
    Method method; /**< The tree building method to use for random trees. */

    /**
     * Helper function to recursively build a random tree using the growth method.
     * @see TreeFactory#build()
     * @param maxHeight The maximum height the tree may have.
     * @return The randomly generated tree.
     */
    Node *buildGrow(int maxHeight) const;

    /**
     * Helper function to recursively build a random full tree.
     * @see TreeFactory#build()
     * @param maxHeight The maximum height the tree may have.
     * @return The randomly generated tree.
     */
    Node *buildFull(int maxHeight) const;
};

#endif // TREEFACTORY_H
