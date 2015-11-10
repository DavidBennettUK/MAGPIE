#include <QTime>
#include "Scenario.h"
#include "../common.h"
#include "../gp/TournamentSelection.h"

Scenario::Scenario(int populationSize)
{
    this->populationSize = populationSize;

    currentGeneration = NULL;
    selection = new TournamentSelection(5);
    treeFactory = new TreeFactory(5, &functionSet, &terminalSet);
    mutation = new Mutation(treeFactory);
    crossover = new Crossover(treeFactory);
    targetFitness = 100;
    generationNumber = 0;
    maxGenerations = 500;
    crossoverRate = 0.75f;
    mutationRate = 0.15f;
    elitism = false;
    state = PAUSED;
}

Scenario::~Scenario()
{
    safeDelete(currentGeneration);
    safeDelete(selection);
    safeDelete(treeFactory);
    safeDelete(mutation);
    safeDelete(crossover);

    foreach (IParameter *parameter, parameters)
        safeDelete(parameter);
    parameters.clear();
}

void Scenario::initialiseRandomPopulation()
{
    safeDelete(currentGeneration);

    currentGeneration = new Generation(populationSize);

    while (currentGeneration->getSize() < populationSize)
    {
        Individual *individual = randomIndividual();
        currentGeneration->addIndividual(individual);
    }

    emit generationComplete(QSharedPointer<Generation>(currentGeneration->clone()), 0);
    generationNumber = 0;
}

void Scenario::nextGeneration()
{
    Q_ASSERT(crossoverRate + mutationRate <= 1.0f);

    if (currentGeneration == NULL)
    {
        initialiseRandomPopulation();
    }
    else
    {
        Generation *nextGen = new Generation(populationSize);

        if (elitism)
            nextGen->addIndividual(getCurrentGeneration()->getBestIndividual()->clone());

        while (nextGen->getSize() < populationSize)
        {
            float chance = (float) qrand() / (float) RAND_MAX;

            if (chance < crossoverRate && populationSize - nextGen->getSize() >= 2)
            {
                Individual *i = selection->selectIndividual(getCurrentGeneration())->clone();
                Individual *i2 = selection->selectIndividual(getCurrentGeneration())->clone();

                crossover->crossover(i->getRootNode(), i2->getRootNode());
                i->reset(); i2->reset();

                nextGen->addIndividual(i);
                nextGen->addIndividual(i2);
            }
            else if (chance < crossoverRate + mutationRate)
            {
                Individual *i = selection->selectIndividual(getCurrentGeneration())->clone();

                mutation->mutate(i->getRootNode());
                i->reset();

                nextGen->addIndividual(i);
            }
            else
            {
                Individual *i = selection->selectIndividual(getCurrentGeneration())->clone();
                nextGen->addIndividual(i);
            }
        }

        safeDelete(currentGeneration);
        currentGeneration = nextGen;

        generationNumber++;
    }

    emit generationComplete(QSharedPointer<Generation>(currentGeneration->clone()), generationNumber);
}

void Scenario::reset()
{
    safeDelete(currentGeneration);
    generationNumber = 0;
    emit newRun();
}

void Scenario::setInitialGeneration(Generation *generation)
{
    safeDelete(currentGeneration);
    currentGeneration = generation;
    generationNumber = 0;
    emit generationComplete(QSharedPointer<Generation>(generation->clone()), generationNumber);
}

void Scenario::setMaximumGenerations(const int maxGenerations)
{
    this->maxGenerations = maxGenerations;
    emit maxGenerationsChanged(maxGenerations);
}

void Scenario::setSelection(Selection *selection)
{
    safeDelete(this->selection);
    this->selection = selection;
}

void Scenario::run()
{
    qsrand(QTime::currentTime().msec());

    state = RUNNING;
    emit runStarted();

    if (currentGeneration == NULL)
        initialiseRandomPopulation();

    for (int i = generationNumber; i < maxGenerations && state == RUNNING; i++)
    {
        nextGeneration();
        if (getCurrentGeneration()->getHighestFitness() >= targetFitness)
            break;
    }

    state = PAUSED;
    emit runFinished();
}

void Scenario::fullRun()
{
    qsrand(QTime::currentTime().msec());

    state = RUNNING;
    emit runStarted();

    if (currentGeneration == NULL)
        initialiseRandomPopulation();

    for (int i = generationNumber; i < maxGenerations && state == RUNNING; i++)
    {
        nextGeneration();
    }

    state = PAUSED;
    emit runFinished();
}

void Scenario::pauseRun()
{
    state = PAUSING;
}
