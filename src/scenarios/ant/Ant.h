#ifndef ANT_H
#define ANT_H

#include "../../gp/Individual.h"

/**
 * Represents an ant in the artifical ant problem.
 * @author David Bennett
 */
class Ant : public Individual
{
public:
    /** Shows which way the lawnmower is facing. */
    enum Facing { UP, RIGHT, DOWN, LEFT };

    /**
     * Constructs the ant.
     * @param maxMoves The maximum number of moves (turn or forward) the ant can make.
     */
    Ant(int maxMoves);

    /** Execute the next step in the program tree. */
    bool step();

    /** Reset the ant to its initial state. */
    void reset();

    /** Creates a deep-copy of the ant. */
    virtual Individual *clone() const;

    /**
     * Get the fitness of the individual.
     * @return The fitness of the individual.
     */
    virtual Fitness *getFitness();

    /**
     * Gets the direction the ant is facing.
     * @return The direction the ant is facing.
     */
    Facing getFacing() { return facing; }

    /**
     * Sets the direction the ant is facing.
     * @param facing The direction the ant is facing.
     */
    void setFacing(Facing facing) { this->facing = facing; }

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
     * Check if there is food at the given coordinates.
     * @param x Column number to check.
     * @param y Row number to check.
     * @return True if food is in the cell, otherwise false.
     */
    bool isFoodAt(int x, int y) { return grid[y][x] > 0; }

    /**
     * @return True if there is food in front of the ant, otherwise false.
     */
    bool isFoodInFront();

    /** Move the ant forward, eating the food if there is any in the new cell. */
    void moveForward();

    /**
     * Turn the ant 90&deg;
     * @param left True to turn left, false to turn right.
     */
    void turn(bool left);

    /**
     * @return The width of the grid.
     */
    int getGridWidth() { return gridWidth; }

    /**
     * @return The height of the grid.
     */
    int getGridHeight() { return gridHeight; }

    /**
     * @return The number of food pellets eaten so far.
     */
    int getPoints() { return points; }

    /**
     * @return The number of moves (turn or forward) made so far.
     */
    int getMoves() { return moves; }

    /**
     * Check if the ant has visited the given coordinates.
     * @param x The column number.
     * @param y The row number.
     * @return True if the ant has visited the square, otherwise false.
     */
    bool hasVisited(int x, int y) { return visits[y][x] > 0; }

private:
    int gridWidth; /**< The width of the grid. */
    int gridHeight; /**< The height of the grid. */
    int grid[32][32]; /**< The grid of pellets. 0 if empty, 1 if there is a pellet. */
    int visits[32][32]; /**< Holds the path the ant has made. 1 if visited, otherwise 0. */
    Facing facing; /**< The direction the lawnmower is facing. */
    int x; /**< The column number of the lawnmower, 0 being the leftmost column. */
    int y; /**< The row number of the lawnmower, 0 being the topmost column. */
    int points; /**< The number of food pellets eaten so far. */
    int moves; /**< The number of moves (turn or forward) made so far. */
    int maxMoves; /**< The maximum number of moves (turn or forward) the ant can make. */
};

#endif // ANT_H
