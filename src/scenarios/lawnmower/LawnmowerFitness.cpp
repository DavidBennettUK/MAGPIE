#include "LawnmowerFitness.h"

Fitness *LawnmowerFitness::clone() const
{
    return new LawnmowerFitness(points);
}

bool LawnmowerFitness::isBetterThan(const Fitness *other) const
{
    return this->getValue() > other->getValue();
}
