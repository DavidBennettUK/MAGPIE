#include "AntScenario.h"
#include "nodes/AntLeftNode.h"
#include "nodes/AntRightNode.h"
#include "../common/nodes/Prog2Node.h"
#include "nodes/ForwardNode.h"
#include "nodes/IfFoodAheadNode.h"
#include "../common/nodes/Prog3Node.h"
#include "../../gp/RouletteSelection.h"
#include "Ant.h"

AntScenario::AntScenario(int populationSize) : Scenario(populationSize)
{
    functionSet << Prog2Node::create << Prog3Node::create << IfFoodAheadNode::create;
    terminalSet << ForwardNode::create << AntLeftNode::create << AntRightNode::create;

    maxGenerations = 1000;
    targetFitness = 89;
    this->populationSize = 100;
    mutationRate = 0.1f;
    crossoverRate = 0.7f;
    elitism = true;
    selection = new RouletteSelection();
    parameters["MAX_MOVES"] = new Parameter<IntValue *>(QString("Max Moves"), new IntValue(450, 1, 999999));
}

Individual *AntScenario::randomIndividual() const
{
    Individual *individual = new Ant(maxMoves());
    Node *rootNode = treeFactory->build();
    individual->setRootNode(rootNode);

    return individual;
}

Individual *AntScenario::createIndividual(const QString tree) const
{
    Individual *individual = new Ant(maxMoves());
    Node *rootNode = treeFactory->buildFromString(tree);
    individual->setRootNode(rootNode);

    return individual;
}
