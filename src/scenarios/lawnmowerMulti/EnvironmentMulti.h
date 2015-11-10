#ifndef ENVIRONMENTMULTI_H
#define ENVIRONMENTMULTI_H

#include "../lawnmower/Environment.h"

/**
 * Represents a garden a {@link LawnmowerMulti} mows.
 * @author David Bennett
 */
class EnvironmentMulti : public Environment
{
public:
    /**
     * Constructs the environment.
     * @param width Number of horizontal tiles.
     * @param height Number of vertical tiles.
     * @param numObstacles Number of obstacles to spawn.
     */
    EnvironmentMulti(int width = 10, int height = 10, int numObstacles = 3);

    /**
     * Creates a deep-copy of the environment.
     * @return A deep-copy of the environment.
     */
    EnvironmentMulti *clone();

    /**
     * Check if there is an obstactle at the given coordinates.
     * @param x The column number of the tile to check.
     * @param y The row number of the tile to check.
     */
    bool isObstacle(const int x, const int y) { return obstacles[x][y] > 0; }

    /**
     * @return The total number of obstacles in the environment.
     */
    int getNumObstacles() { return obstacles.count(); }

private:
    QVector< QVector<int> > obstacles; /**< The obstacles in the garden. */
};

#endif // ENVIRONMENTMULTI_H
