#ifndef ANTFITNESS_H
#define ANTFITNESS_H

#include "../../gp/Fitness.h"

/**
 * Represents the fitness for an {@link Ant}.
 * Ants are rated on the number of food pellets they eat, the more the better.
 * @author David Bennett
 */
class AntFitness : public Fitness
{
public:
    /**
     * Creates a fitness with the number of food pellets eaten.
     * @param points The number of food pellets eaten.
     * @param moves The maximum number of moves the ant can make.
     */
    AntFitness(int points, int moves) : points(points), moves(moves) { }

    /** Creates a deep-copy of this fitness. */
    Fitness *clone() const;

    /**
     * Check if this fitness is better than another.
     * Based on the number of points.
     * If both trees have the same fitness, the smaller is better.
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
    int points; /**< The number of food pellets eaten. */
    int moves; /**< The number of nodes in the program tree. */
};

#endif // ANTFITNESS_H
