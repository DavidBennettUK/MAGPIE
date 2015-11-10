#ifndef LAWNMOWER_H
#define LAWNMOWER_H

#include "../../gp/Individual.h"
#include "Environment.h"

/**
 * Represents a lawnmower, to be used in lawnmower scenarios.
 * @author David Bennett
 */
class Lawnmower : public Individual
{
public:
    /** Shows which way the lawnmower is facing. */
    enum Facing { UP, RIGHT, DOWN, LEFT };

    /**
     * Constructs the lawnmower.
     * @param environment The environment for the lawnmower to belong to.
     * @param maxMoves The maximum number of moves the lawnmower can take.
     *                 Only terminal nodes are counted as moves.
     */
    Lawnmower(Environment *environment, int maxMoves = 200);

    /** Destructs the lawnmower. */
    virtual ~Lawnmower();

    /** Creates a deep-copy of the lawnmower. */
    virtual Individual *clone() const;

    /** Execute the next step in the program tree. */
    bool step();

    /** Reset the lawnmower to its initial state. */
    void reset();

    /**
     * Get the fitness of the lawnmower.
     * @return The fitness of the lawnmower.
     */
    virtual Fitness *getFitness();

    /**
     * Gets the column the lawnmower is currently in.
     * @return The column number. 0 being the leftmost column.
     */
    int getX() const { return x; }

    /**
     * Sets the column number of the lawnmower.
     * @param x The column number 0 being the leftmost column.
     */
    void setX(const int x) { this->x = x; }

    /**
     * Gets the row the lawnmower is currently in.
     * @return The row number. 0 being the topmost column.
     */
    int getY() const { return y; }

    /**
     * Sets the row number of the lawnmower.
     * @param y The row number. 0 being the topmost column.
     */
    void setY(const int y) { this->y = y; }

    /**
     * Gets the direction the lawnmower is facing.
     * @return The direction the lawnmower is facing.
     */
    Facing getFacing() { return facing; }

    /**
     * Sets the direction the lawnmower is facing.
     * @param facing The direction the lawnmower is facing.
     */
    void setFacing(Facing facing) { this->facing = facing; }

    /**
     * Gets the environment of the lawnmower.
     * @return The environment of the lawnmower.
     */
    Environment *getEnvironment() const { return environment; }

    /**
     * Gets the number of tiles that have been mowed.
     * Does not count tiles mowed more than once.
     * @return The number of tiles that have been mowed.
     */
    int getPoints() const { return points; }

    /**
     * Increment the number of grass tiles that have been mowed.
     * @see Lawnmower#getPoints()
     */
    void incrementPoints() { points++; }

    /**
     * Get the number of moves the program has made.
     * Only terminal nodes count as moves.
     * @return The number of moves the individual has performed.
     */
    int getMoves() const { return moves; }

    /**
     * Increment the number of moves the program has made.
     * @see Lawnmower#getMoves()
     */
    void incrementMoves() { moves++; }

protected:
    Environment *environment; /**< The environment the lawnmower exists in */
    int x; /**< The column number of the lawnmower, 0 being the leftmost column. */
    int y; /**< The row number of the lawnmower, 0 being the topmost column. */
    Facing facing; /**< The direction the lawnmower is facing. */
    int points; /**< The number of tiles that have been mowed at least once. */
    const int maxMoves; /**< The maximum number of moves the program may take */
    int moves; /**< The current number of moves that have been taken. */
};

#endif // LAWNMOWER_H
