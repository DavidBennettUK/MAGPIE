#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <QStack>
#include "Node.h"
#include "Fitness.h"

class Node;

/**
 * Base individual class.
 * Extend this class to create concrete individuals for a scenario.
 * @author David Bennett
 */
class Individual
{
public:
    /** Constructs an individual. */
    Individual();

    /** Destructs an individual */
    virtual ~Individual();

    /**
     * Deep-copy the individual.
     * @return A deep-copy of the individual.
     */
    virtual Individual *clone() const = 0;

    /**
     * Perform one step of the program tree.
     * Make sure to call the base method if you override.
     * @return True if the step was performed, otherwise false (e.g. if maximum number of steps reached).
     */
    virtual bool step();

    /**
     * Reset the individual to initial state, where no steps have been performed.
     * Make sure to call the base method if you override.
     */
    virtual void reset();

    /**
     * Gets the root {@link Node} of the individual's program tree.
     * @return The root {@link Node} of the individual's program tree.
     */
    Node *getRootNode() const { return rootNode; }

    /**
     * Set the root {@link Node} of the indivdiual's program tree.
     * @param rootNode The root {@link Node} of the individual's program tree.
     */
    void setRootNode(Node *rootNode) { this->rootNode = rootNode; }

    /**
     * Get the fitness of the individual.
     * @return The fitness of the individual.
     */
    virtual Fitness *getFitness() = 0;

protected:
    Fitness *fitness; /**< The fitness of the individual */
    Node *rootNode; /**< Root node of the individual's program tree. */
    QStack<Node *> programStack; /**< Holds nodes to be executed in {@link step()}, top is the next to be executed. */
};

#endif // INDIVIDUAL_H
