#include "TournamentSelection.h"

TournamentSelection::TournamentSelection(const int tournamentSize)
{
    this->tournamentSize = tournamentSize;
}

Individual *TournamentSelection::selectIndividual(const Generation *generation) const
{
    QVector<Individual *> contestants;

    return selectIndividual(generation, &contestants);
}

Individual *TournamentSelection::selectIndividual(const Generation *generation, QVector<Individual *> *contestants) const
{
    Q_ASSERT(contestants != NULL);
    Q_ASSERT(contestants->empty());
    Q_ASSERT(generation->getPopulation().size() >= tournamentSize);

    if (contestants == NULL || generation->getPopulation().size() < tournamentSize)
        return NULL;

    // Ensure the contestants vector is empty
    contestants->clear();

    // Select the contestants
    for (int i = 0; i < tournamentSize; i++)
    {
        int contestantId = qrand() % generation->getPopulation().size();
        Individual *contestant = generation->getPopulation()[contestantId];

        // Only add if contestest has not already been selected
        if (!contestants->contains(contestant))
            contestants->append(contestant);
        else
            i--;
    }

    // Find the best individual
    Individual *best = contestants->first();

    for (int i = 1; i < contestants->size(); i++)
    {
        if (contestants->at(i)->getFitness()->isBetterThan(best->getFitness()))
            best = contestants->at(i);
    }

    return best;
}
