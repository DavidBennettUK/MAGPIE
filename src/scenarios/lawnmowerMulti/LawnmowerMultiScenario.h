#ifndef LAWNMOWERMULTISCENARIO_H
#define LAWNMOWERMULTISCENARIO_H

#include "../../gp/Scenario.h"
#include "../../gp/IntValue.h"

/**
 * Concrete multi-objective lawnmower scenario, where obstacles are
 * taken into account.
 * @author David Bennett
 */
class LawnmowerMultiScenario : public Scenario
{
public:
    /**
     * Constructs the scenario with a population size.
     * @param populationSize The population size.
     */
    LawnmowerMultiScenario(int populationSize = 50);

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
    int hitPenalty() const { return ((Parameter<IntValue *> *) parameters["HIT_PENALTY"])->getValue()->getValue(); }
    int numObstacles() const { return ((Parameter<IntValue *> *) parameters["NUM_OBSTACLES"])->getValue()->getValue(); }
};

#endif // LAWNMOWERMULTISCENARIO_H
