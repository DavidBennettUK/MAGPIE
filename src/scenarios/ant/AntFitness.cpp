#include "AntFitness.h"

Fitness *AntFitness::clone() const
{
    return new AntFitness(points, moves);
}

bool AntFitness::isBetterThan(const Fitness *other) const
{
    if (this->getValue() == other->getValue())
        return this->moves < ((AntFitness *) other)->moves;
    else
        return this->getValue() > other->getValue();
}

int AntFitness::getValue() const
{
    return points;
}
