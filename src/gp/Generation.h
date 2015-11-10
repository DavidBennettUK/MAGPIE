#ifndef GENERATION_H
#define GENERATION_H

#include <QVector>
#include <QObject>
#include <QSharedPointer>
#include "Individual.h"

/**
 * Holds one generation of a population of {@link Individual}s.
 * Owns references to individuals - if you need to keep an {@link Individual} after the generation
 * is destroyed then make a copy beforehand.
 * @author David Bennett
 */
class Generation : public QObject
{
    Q_OBJECT

public:
    /**
     * Constructs the generation with a maximum population size.
     * @param populationSize The number of {@link Individual}s the population should hold.
     */
    Generation(int populationSize) : populationSize(populationSize) { }

    /**
     * Destructs the generation.
     * Deletes all {@link Individual}s in the population.
     */
    ~Generation();

    /**
     * Creates a deep-copy clone of the generation.
     * @return A copy of the generation.
     */
    Generation *clone() const;

    /**
     * Add an individual to the population.
     * The generation will take ownership of the {@link Individual} reference, so do not
     * delete it elsewhere.
     * Will not add if population is full.
     * @param individual The {@link Individual} to add to the population.
     */
    void addIndividual(Individual *individual);

    /**
     * Get the current number of {@link Individual}s in the population.
     * @return The number of {@link Individual}s in the population.
     */
    int getSize() const { return population.size(); }

    /**
     * Get the population size of the generation.
     * This is the number of {@link Individual}s the generation should hold.
     * @return The number of {@link Individual}s the generation should hold
     */
    int getPopulationSize() const { return populationSize; }

    /**
     * Get the total fitness value of all {@link Individual} in the population.
     * @return The total fitness value of all {@link Individual}s in the population.
     * @see Fitness#getValue()
     */
    int getTotalFitness() const;

    /**
     * Get the highest fitness value in the population.
     * @return The highest fitness value in the population.
     * @see Fitness#getValue()
     */
    int getHighestFitness() const;

    /**
     * Get the lowest fitness value in the population
     * @return The lowest fitness value in the population.
     * @see Fitness#getValue()
     */
    int getLowestFitness() const;

    /**
     * Get the average fitness value of the population.
     * @return The average fitness value of the population.
     * @see Fitness#getValue()
     */
    float getAverageFitness() const;

    /**
     * Get the highest number of tree nodes in an {@link Individual} in the population.
     * @return The highest number of tree nodes in the population.
     * @see Node#getSize()
     */
    int getLargestTreeSize() const;

    /**
     * Get the lowest number of tree nodes in an {@link Individual} in the population.
     * @return The highest number of tree nodes in the population.
     * @see Node#getSize()
     */
    int getSmallestTreeSize() const;

    /**
     * Get the average number of tree nodes in {@link Individual}s in the population.
     * @return The average number of tree nodes in the population.
     * @see Node#getSize()
     */
    float getAverageTreeSize() const;

    /**
     * Get the {@link Individual} with the highest fitness value in the population.
     * @return A reference to the {@link Individual} with the highest fitness value in the poplution.
     * @see Fitness#getValue()
     */
    Individual *getBestIndividual() const;

    /**
     * Get a list of {@link Individual}s in the population.
     * @return A list of {@link Individual}s in the population.
     */
    QVector<Individual *> getPopulation() const { return population; }

private:
    const int populationSize; /**< What the population size should be. */
    QVector<Individual *> population; /**< List of {@link Individual}s in the popluation. */
};

#endif // GENERATION_H
