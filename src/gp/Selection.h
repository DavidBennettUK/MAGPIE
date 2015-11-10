#ifndef SELECTION_H
#define SELECTION_H

#include <QVector>
#include "Individual.h"
#include "Generation.h"

/**
 * Interface for selection methods.
 * @author David Bennett
 */
class Selection
{
public:
    virtual ~Selection() { }

    /**
     * Select an {@link Individual} from the {@link Generation}.
     * @param generation The {@link Generation} to select an {@link Individual} from.
     * @return A reference to the selected {@link Individual} from the {@link Generation}.
     *         Will return NULL if the {@link Generation} is empty.
     */
    virtual Individual *selectIndividual(const Generation *generation) const = 0;
};

#endif // SELECTION_H
