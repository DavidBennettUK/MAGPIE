#include "LawnmowerMultiFitness.h"

LawnmowerMultiFitness::LawnmowerMultiFitness(int points, int hits, int hitPenalty) :
    points(points), hits(hits), hitPenalty(hitPenalty)
{

}

Fitness *LawnmowerMultiFitness::clone() const
{
    return new LawnmowerMultiFitness(points, hits, hitPenalty);
}

bool LawnmowerMultiFitness::isBetterThan(const Fitness *other) const
{
   return this->getValue() > ((LawnmowerMultiFitness *) other)->getValue();
}

int LawnmowerMultiFitness::getValue() const
{
    return points - (hits * hitPenalty);
}
