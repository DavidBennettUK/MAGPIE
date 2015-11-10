#include "Environment.h"
#include <cstring>

Environment::Environment(int width, int height) : width(width), height(height)
{
    reset();
}

Environment *Environment::clone()
{
    Environment *newEnv = new Environment(width, height);
    newEnv->grass = grass;
    return newEnv;
}

void Environment::reset()
{
    grass = QVector< QVector<int> >(width, QVector<int>(height));

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            grass[i][j] = 0;
}

int Environment::numMows(int x, int y) const
{
    return grass[x][y];
}

bool Environment::mowTile(int x, int y)
{
    grass[x][y]++;

    return grass[x][y] == 1;
}
