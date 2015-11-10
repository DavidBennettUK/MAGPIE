#ifndef ANTSCENARIO_H
#define ANTSCENARIO_H

#include "../../gp/Scenario.h"
#include "../../gp/IntValue.h"

/**
 * Artifical ant problem.
 * @author David Bennett
 */
class AntScenario : public Scenario
{
public:
    /**
     * Constructs the scenario with a population size.
     * @param populationSize The population size.
     */
    AntScenario(int populationSize = 200);

    /**
     * Create a random ant.
     * The caller will take repsonsibility for deletion.
     * @return Pointer to a new random ant.
     */
    Individual *randomIndividual() const;

    /**
     * Create an ant from a string, using LISP-like syntax.
     * The caller will take responsibility for deletion.
     * @see Node#toString()
     * @param tree The program tree in string representation.
     * @return The created ant.
     */
    Individual *createIndividual(const QString tree) const;

private:
    int maxMoves() const { return ((Parameter<IntValue *> *) parameters["MAX_MOVES"])->getValue()->getValue(); }
};

#endif // ANTSCENARIO_H
