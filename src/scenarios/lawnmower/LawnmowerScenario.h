#ifndef LAWNMOWERSCENARIO_H
#define LAWNMOWERSCENARIO_H

#include "../../gp/Scenario.h"
#include "../../gp/IntValue.h"

/**
 * Lawnmower problem.
 * @author David Bennett
 */
class LawnmowerScenario : public Scenario
{
public:
    /**
     * Constructs the scenario with a population size.
     * @param populationSize The population size.
     */
    LawnmowerScenario(int populationSize = 50);

    /**
     * Create a random lawnmower.
     * The caller will take repsonsibility for deletion.
     * @return Pointer to a new random lawnmower.
     */
    Individual *randomIndividual() const;

    /**
     * Create a lawnmower from a string, using LISP-like syntax.
     * The caller will take responsibility for deletion.
     * @see Node#toString()
     * @param tree The program tree in string representation.
     * @return The created lawnmower.
     */
    Individual *createIndividual(const QString tree) const;

private:
    int gridSize() const { return ((Parameter<IntValue *> *) parameters["GRID_SIZE"])->getValue()->getValue(); }
    int maxMoves() const { return ((Parameter<IntValue *> *) parameters["MAX_MOVES"])->getValue()->getValue(); }
};

#endif // LAWNMOWERSCENARIO_H
