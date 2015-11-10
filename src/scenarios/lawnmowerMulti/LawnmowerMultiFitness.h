#ifndef LAWNMOWERMULTIFITNESS_H
#define LAWNMOWERMULTIFITNESS_H

#include "../../gp/Fitness.h"

/**
 * Represents a multi-objective fitness for a {@link LawnmowerMulti}.
 * Rates lawnmowers on the number of unique tiles mowed, but deducts
 * a penalty for hitting obstacles.
 * @author David Bennett
 */
class LawnmowerMultiFitness : public Fitness
{
public:
    /**
     * Creates a fitness for a {@link LawnmowerMulti}.
     * @param points Number of unique grass tiles mowed.
     * @param hits Number of times obstacles have been hit.
     * @param hitPenalty How much fitness should be dedected when hitting an obstacle.
     */
    LawnmowerMultiFitness(int points, int hits, int hitPenalty);

    /** Creates a deep-copy of this fitness. */
    Fitness *clone() const;

    /**
     * Check if this fitness is better than another.
     * Based on the number of points.
     * @param other The fitness to compare to.
     * @return True if this fitness is better, otherwise false.
     */
    bool isBetterThan(const Fitness *other) const;

    /**
     * Gets the fitness value, based on the number of points.
     * @return The fitness value.
     */
    int getValue() const;

private:
    int points; /**< Number of unique tiles mowed. */
    int hits; /**< Numbef of times obstactles have been hit. */
    int hitPenalty; /**< How much fitness should be deducted when hitting an obstacle. */
};

#endif // LAWNMOWERMULTIFITNESS_H
