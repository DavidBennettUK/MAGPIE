#ifndef LAWNMOWERMULTI_H
#define LAWNMOWERMULTI_H

#include "../lawnmower/Lawnmower.h"
#include "EnvironmentMulti.h"

/**
 * Represents a multi-objective lawnmower, to be used in lawnmower scenarios,
 * that accounts for obstacles in the environment.
 * @author David Bennett
 */
class LawnmowerMulti : public Lawnmower
{
public:
    /**
     * Constructs the lawnmower.
     * @param environment The environment for the lawnmower to belong to.
     * @param maxMoves The maximum number of moves the lawnmower can make.
     * @param hitPenalty The amount of fitness to deduct if an obstacle is hit.
     */
    LawnmowerMulti(EnvironmentMulti *environment, int maxMoves = 300, int hitPenalty = 10);

    /** Destructs the lawnmower. */
    ~LawnmowerMulti() { }

    /** Creates a deep-copy of the lawnmower. */
    Individual *clone() const;

    /** Execute the next step in the program tree. */
    bool step();

    /**
     * Gets the environment of the lawnmower.
     * @return The environment of the lawnmower.
     */
    EnvironmentMulti *getEnvironment() const { return environment; }

    /**
     * Get the fitness of the lawnmower.
     * @return The fitness of the lawnmower.
     */
    Fitness *getFitness();

    /**
     * @return The number times the lawnmower has hit obstacles.
     */
    int getHits() { return hits; }

    /** Increment the number of obstacle hits. */
    void incrementHits() { hits++; }

private:
    EnvironmentMulti *environment; /**< The environment the lawnmower exists in */
    int hits; /**< The number of times the lawnmower has hit obstacles. */
    int hitPenalty; /** The amount of fitness to deduct if an obstacle is hit. */
};

#endif // LAWNMOWERMULTI_H
