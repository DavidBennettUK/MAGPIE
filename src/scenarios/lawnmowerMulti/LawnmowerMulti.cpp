#include "LawnmowerMulti.h"
#include "LawnmowerMultiFitness.h"
#include "../../common.h"

LawnmowerMulti::LawnmowerMulti(EnvironmentMulti *environment, int maxMoves, int hitPenalty) :
    Lawnmower(environment, maxMoves)
{
    this->environment = environment;
    this->hitPenalty = hitPenalty;
    hits = 0;
}

Individual *LawnmowerMulti::clone() const
{
    LawnmowerMulti *newIndividual = new LawnmowerMulti(environment->clone(), maxMoves);
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

bool LawnmowerMulti::step()
{
    return Lawnmower::step() &&
           (points != environment->getWidth() * environment->getHeight()) - environment->getNumObstacles();
}

Fitness *LawnmowerMulti::getFitness()
{
    if (fitness == NULL)
    {
        reset();

        while (step());

        fitness = new LawnmowerMultiFitness(points, hits, hitPenalty);
    }

    return fitness;
}

