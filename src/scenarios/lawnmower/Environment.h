#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QVector>

/**
 * Represents a garden a {@link Lawnmower} mows.
 * @author David Bennett
 */
class Environment
{
public:
    /**
     * Constructs the environment.
     * @param width Number of horizontal tiles.
     * @param height Number of vertical tiles.
     */
    Environment(int width = 10, int height = 10);

    /** Destructs the environment. */
    virtual ~Environment() { }

    /**
     * Creates a deep-copy of the environment.
     * @return A deep-copy of the environment.
     */
    virtual Environment *clone();

    /**
     * Find the number of mows a certain tile has.
     * @param x Column number of the tile to mow.
     * @param y Row number of the tile to mow.
     * @return The number of mows the tile has.
     */
    int numMows(const int x, const int y) const;

    /**
     * Mark a tile as mowed.
     * Can be called multiple times on the same tile.
     * @param x Column number of the tile to mow.
     * @param y Row number of the tile to mow.
     * @return
     */
    bool mowTile(const int x, const int y);

    /** Resets the garden to an unmowed state. */
    void reset();

    /**
     * @return The number of tiles wide the garden is.
     */
    int getWidth() const { return width; }

    /**
     * @return The number of tiles high the garden is.
     */
    int getHeight() const { return height; }

protected:
    const int width; /**< The number of tiles wide the garden is. */
    const int height; /**< The number of tiles tall the garden is. */
    QVector< QVector<int> > grass; /**< Represents the grid of grass tiles. */
};

#endif // ENVIRONMENT_H
