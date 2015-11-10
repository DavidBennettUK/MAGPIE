#include "Lawnmower.h"
#include "../../common.h"
#include "LawnmowerFitness.h"

Lawnmower::Lawnmower(Environment *environment, int maxMoves) : maxMoves(maxMoves)
{
    this->environment = environment;
    reset();
}

Lawnmower::~Lawnmower()
{
    safeDelete(environment);
}

Individual *Lawnmower::clone() const
{
    Lawnmower *newIndividual = new Lawnmower(environment->clone(), maxMoves);
    newIndividual->x = x;
    newIndividual->y = y;
    newIndividual->facing = facing;
    newIndividual->rootNode = rootNode->clone();
    newIndividual->programStack = programStack;
    newIndividual->moves = moves;
    if (fitness)
        newIndividual->fitness = fitness->clone();

    return newIndividual;
}

bool Lawnmower::step()
{
    return Individual::step() &&
           points != environment->getWidth() * environment->getHeight() &&
           moves < maxMoves;
}

void Lawnmower::reset()
{
    Individual::reset();
    x = 0;
    y = 0;
    points = 0;
    moves = 0;
    facing = DOWN;
    environment->reset();
    safeDelete(fitness); // clear fitnes as tree may have changed from crossover/mutation
}

Fitness *Lawnmower::getFitness()
{
    if (fitness == NULL)
    {
        reset();

        while (step());

        fitness = new LawnmowerFitness(points);
    }

    return fitness;
}
