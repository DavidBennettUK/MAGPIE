#ifndef ROULETTESELECTION_H
#define ROULETTESELECTION_H

#include "Selection.h"

/**
 * Helper class to perform roulette selection on a generation.
 * @author David Bennett
 */
class RouletteSelection : public Selection
{
public:
    /**
     * Uses roulette selection to pick a random {@link Individual}, with chance of
     * selection based on fitness value. The higher the fitness, the higher the
     * chance of selection.
     * @see Fitness#getValue()
     * @see Selection::selectIndividual(const Generation *) const
     */
    Individual *selectIndividual(const Generation *generation) const;
};

#endif // ROULETTESELECTION_H
