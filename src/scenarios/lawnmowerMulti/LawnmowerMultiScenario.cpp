#include "LawnmowerMultiScenario.h"
#include "../lawnmower/nodes/LeftNode.h"
#include "../common/nodes/Prog2Node.h"
#include "nodes/IfObstacleAheadNode.h"
#include "nodes/MowMultiNode.h"
#include "LawnmowerMulti.h"

LawnmowerMultiScenario::LawnmowerMultiScenario(int populationSize) : Scenario(populationSize)
{
    functionSet << Prog2Node::create << IfObstacleAheadNode::create;
    terminalSet << MowMultiNode::create << LeftNode::create;

    parameters["GRID_SIZE"] = new Parameter<IntValue *>(QString("Grid Size"), new IntValue(10, 5, 25));
    parameters["MAX_MOVES"] = new Parameter<IntValue *>(QString("Max Moves"), new IntValue(300, 1, 999999));
    parameters["HIT_PENALTY"] = new Parameter<IntValue *>(QString("Hit Penalty"), new IntValue(10, 0, 100));
    parameters["NUM_OBSTACLES"] = new Parameter<IntValue *>(QString("Obstacles"), new IntValue(5, 0, 10));
}

Individual *LawnmowerMultiScenario::randomIndividual() const
{
    EnvironmentMulti *environment = new EnvironmentMulti(gridSize(), gridSize(), numObstacles());
    Individual *individual = new LawnmowerMulti(environment, maxMoves(), hitPenalty());
    Node *rootNode = treeFactory->build();
    individual->setRootNode(rootNode);

    return individual;
}

Individual *LawnmowerMultiScenario::createIndividual(const QString tree) const
{
    EnvironmentMulti *environment = new EnvironmentMulti(gridSize(), gridSize(), numObstacles());
    Individual *individual = new LawnmowerMulti(environment, maxMoves(), hitPenalty());
    Node *rootNode = treeFactory->buildFromString(tree);
    individual->setRootNode(rootNode);

    return individual;
}
