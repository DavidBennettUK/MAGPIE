#include "Individual.h"
#include "../common.h"

Individual::Individual()
{
    rootNode = NULL;
    fitness = NULL;
}

Individual::~Individual()
{
    safeDelete(rootNode);
    safeDelete(fitness);
}

bool Individual::step()
{
    Q_ASSERT(rootNode);

    if (programStack.empty())
        programStack.push(rootNode);

    Node *node = programStack.pop();
    node->evaluate(this, &programStack);

    return true;
}

void Individual::reset()
{
    programStack.clear();
}
