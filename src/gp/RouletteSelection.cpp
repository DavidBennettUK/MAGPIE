#include "RouletteSelection.h"

Individual *RouletteSelection::selectIndividual(const Generation *generation) const
{
    Q_ASSERT(generation->getSize() > 0);

    if (generation->getSize() <= 0)
        return NULL;

    int totalFitness = generation->getTotalFitness();
    int minFitness = generation->getLowestFitness();
    double chance = (((double) qrand() / (double) RAND_MAX)) * (totalFitness + (abs(minFitness) * generation->getSize()));

    QVector<Individual *> population = generation->getPopulation();

    int i;
    for (i = 0; i < population.size() && chance >= 0; i++)
        chance -= population[i]->getFitness()->getValue() + abs(minFitness);

    return population[i - 1];
}
