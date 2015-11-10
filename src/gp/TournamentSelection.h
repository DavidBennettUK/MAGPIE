#ifndef TOURNAMENTSELECTION_H
#define TOURNAMENTSELECTION_H

#include "Selection.h"

/**
 * Helper class to perform tournament selection on a generation.
 * @author David Bennett
 */
class TournamentSelection : public Selection
{
public:
    /**
     * Constructs the selection with a tournament size.
     * Tournament size should be less than or equal to the population size.
     * @param tournamentSize Number of contestants per tournament.
     */
    TournamentSelection(const int tournamentSize);

    /**
     * @see Selection::selectIndividual(const Generation *) const
     * Uses tournament selection to pick an {@link Individual}. A tournament
     * is held between <code>tournamentSize</code> randomly selected {@link Individual}s
     * from the {@link Generation}. The contestant with the highest fitness value is
     * selected.
     * Will return NULL if there are no {@link Individual}s in the {@link Generation} or
     * if the tournament size is less than the population size.
     * @see Fitness#getValue()
     */
    Individual *selectIndividual(const Generation *generation) const;

    /**
     * Same as {@link TournamentSelection#selectIndividual(const Generation *generation) const}, except the selected
     * contestants will be returned. Contestants are references to
     * {@link Individual}s in the {@link Generation}.
     * <code>contestants</code> should be empty, otherwise it will be cleared.
     * Will return NULL if there are no {@link Individual}s in the {@link Generation} or
     * if the tournament size is less than the population size.
     * @param generation The generation to select {@link Individual}s from.
     * @param[out] contestants Will hold the selected contestants.
     * @return A reference to the selected {@link Individual} from the {@link Generation}.
     */
    Individual *selectIndividual(const Generation *generation, QVector<Individual *> *contestants) const;

private:
    int tournamentSize; /**< The number of contestants each tournament should have. */
};

#endif // TOURNAMENTSELECTION_H
