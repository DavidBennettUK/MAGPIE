#include "Generation.h"
#include "../common.h"

using std::max;
using std::min;

Generation::~Generation()
{
    foreach (Individual *individual, population)
        safeDelete(individual);
    population.clear();
}

Generation *Generation::clone() const
{
    Generation *generation = new Generation(populationSize);

    foreach (Individual *individual, population)
        generation->population << individual->clone();

    return generation;
}

void Generation::addIndividual(Individual *individual)
{
    Q_ASSERT(getSize() < populationSize);

    if (getSize() < populationSize)
        population << individual;
}

int Generation::getTotalFitness() const
{
    int total = 0;

    foreach (Individual *individual, population)
        total += individual->getFitness()->getValue();

    return total;
}

int Generation::getHighestFitness() const
{
    int highest = 0;

    foreach (Individual *individual, population)
        highest = max(highest, individual->getFitness()->getValue());

    return highest;
}

int Generation::getLowestFitness() const
{
    int lowest = INT_MAX;

    foreach (Individual *individual, population)
        lowest = min(lowest, individual->getFitness()->getValue());

    return population.size() == 0 ? 0 : lowest;
}

float Generation::getAverageFitness() const
{
    Q_ASSERT(population.size() > 0);

    return population.size() == 0 ? 0 : (float) getTotalFitness() / (float) population.size();
}

int Generation::getLargestTreeSize() const
{
    int largest = 0;

    foreach (Individual *individual, population)
        largest = max(largest, individual->getRootNode()->getSize());

    return largest;
}

int Generation::getSmallestTreeSize() const
{
    int smallest = INT_MAX;

    foreach (Individual *individual, population)
        smallest = min(smallest, individual->getRootNode()->getSize());

    return population.size() == 0 ? 0 : smallest;
}

float Generation::getAverageTreeSize() const
{
    Q_ASSERT(population.size() > 0);

    int total = 0;

    foreach (Individual *individual, population)
        total += individual->getRootNode()->getSize();

    return population.size() == 0 ? 0 : (float) total / (float) population.size();
}

Individual *Generation::getBestIndividual() const
{
    Q_ASSERT(population.size() > 1);

    Individual *best = population[0];

    foreach (Individual *individual, population)
    {
        if (individual->getFitness()->isBetterThan(best->getFitness()))
            best = individual;
    }

    return best;
}
