#ifndef FITNESS_H
#define FITNESS_H

/**
 * Base fitness class.
 * Extend this class to provide fitness in concrete scenarios.
 * @author David Bennett
 */
class Fitness
{
public:
    virtual ~Fitness() { }

    /**
     * Create a deep-copy clone of this fitness.
     * @return A copy of this fitness.
     */
    virtual Fitness *clone() const = 0;

    /**
     * Compare this fitness to another to see if this is better.
     * @param other Fitness to compare to.
     * @return True if this is better, otherwise false (including if they are equal).
     */
    virtual bool isBetterThan(const Fitness *other) const = 0;

    /**
     * Get the fitness value.
     * @return The fitness value.
     */
    virtual int getValue() const = 0;
};

#endif // FITNESS_H
