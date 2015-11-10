#include "EnvironmentMulti.h"

EnvironmentMulti::EnvironmentMulti(int width, int height, int numObstacles) : Environment(width, height)
{
    obstacles = QVector< QVector<int> >(width, QVector<int>(height));

    for (int i = 0; i < numObstacles; i++)
    {
        int x = qrand() % width;
        int y = qrand() % height;

        if (isObstacle(x,y))
            i--;
        else
            obstacles[x][y] = 1;
    }
}

EnvironmentMulti *EnvironmentMulti::clone()
{
    EnvironmentMulti *newEnv = new EnvironmentMulti(width, height);
    newEnv->grass = grass;
    newEnv->obstacles = obstacles;
    return newEnv;
}
