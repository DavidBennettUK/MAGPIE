#include "LawnmowerScenario.h"
#include "nodes/MowNode.h"
#include "nodes/LeftNode.h"
#include "../common/nodes/Prog2Node.h"
#include "Environment.h"
#include "Lawnmower.h"
#include "../../gp/Parameter.h"

LawnmowerScenario::LawnmowerScenario(int populationSize) : Scenario(populationSize)
{
    functionSet << Prog2Node::create;
    terminalSet << MowNode::create << LeftNode::create;

    parameters["GRID_SIZE"] = new Parameter<IntValue *>(QString("Grid Size"), new IntValue(10, 1, 25));
    parameters["MAX_MOVES"] = new Parameter<IntValue *>(QString("Max Moves"), new IntValue(200, 1, 999999));
}

Individual *LawnmowerScenario::randomIndividual() const
{
    Individual *individual = new Lawnmower(new Environment(gridSize(), gridSize()), maxMoves());
    Node *rootNode = treeFactory->build();
    individual->setRootNode(rootNode);

    return individual;
}

Individual *LawnmowerScenario::createIndividual(const QString tree) const
{
    Individual *individual = new Lawnmower(new Environment(gridSize(), gridSize()), maxMoves());
    Node *rootNode = treeFactory->buildFromString(tree);
    individual->setRootNode(rootNode);

    return individual;
}
