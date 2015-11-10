#ifndef LAWNMOWERFITNESS_H
#define LAWNMOWERFITNESS_H

#include "../../gp/Fitness.h"

/**
 * Represents the fitness for a {@link Lawnmower}.
 * Rates lawnmowers on the amount of unique grass tiles they have mowed.
 * @author David Bennett
 */
class LawnmowerFitness : public Fitness
{
public:
    /**
     * Creates a fitness for a {@link Lawnmower}.
     * @param points Number of unique grass tiles mowed.
     */
    LawnmowerFitness(int points) : points(points) { }

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
    int getValue() const { return points; }

private:
    int points; /**< Number of unique tiles mowed. */
};

#endif // LAWNMOWERFITNESS_H
