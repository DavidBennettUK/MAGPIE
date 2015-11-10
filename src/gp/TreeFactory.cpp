#include <QStack>
#include <QStringList>
#include "TreeFactory.h"

TreeFactory::TreeFactory(int maxHeight, QVector<CreateNode> *functionSet, QVector<CreateNode> *terminalSet)
{
    this->maxHeight = maxHeight;
    this->functionSet = functionSet;
    this->terminalSet = terminalSet;
    this->method = HALFANDHALF;
}

Node *TreeFactory::build() const
{
    if (method == HALFANDHALF)
    {
        int chance = qrand() % 2;

        if (chance == 0)
            return buildGrow(maxHeight);
        else
            return buildFull(maxHeight);
    }
    else if (method == GROW)
    {
        return buildGrow(maxHeight);
    }
    else if (method == FULL)
    {
        return buildFull(maxHeight);
    }
    else
    {
        Q_ASSERT(false);
        return NULL;
    }
}

Node *TreeFactory::buildGrow(int maxHeight) const
{
    Node *node;

    // Pick a random node, must pick a terminal if we've reached max depth
    if (maxHeight > 1)
        node = randomNode();
    else
        node = randomTerminal();

    // Recursively build children
    for (int i = 0; i < node->getArity(); i++)
        node->addChild(buildGrow(maxHeight - 1));

    return node;
}

Node *TreeFactory::buildFull(int maxHeight) const
{
    Node *node;

    // Pick a random functional node, only pick a terminal if we've reached max depth
    if (maxHeight > 1)
        node = randomFunction();
    else
        node = randomTerminal();

    // Recursively build children
    for (int i = 0; i < node->getArity(); i++)
        node->addChild(buildFull(maxHeight - 1));

    return node;
}

Node *TreeFactory::buildFromString(QString expression) const
{
    QStack<Node *> nodeStack;
    Node *root = NULL;

    for (int i = 0; i < expression.length(); i++)
    {
        QChar c = expression.at(i);

        // Push a new node onto the stack if a ( is found
        if (c == '(')
        {
            // Find the name of the node
            int nameIndex = i + 1;
            int spaceIndex = expression.indexOf(" ", nameIndex);
            int bracketIndex = expression.indexOf(")", nameIndex);

            if (spaceIndex != -1 && bracketIndex != -1)
                i = std::min(spaceIndex, bracketIndex);
            else if (spaceIndex != -1)
                i = spaceIndex;
            else if (bracketIndex != -1)
                i = bracketIndex;

            Node *node = nodeFromString(expression.mid(nameIndex, i - nameIndex));

            // Set this node as a child of the last node on the stack
            if (!nodeStack.isEmpty())
                nodeStack.top()->addChild(node);

            nodeStack.push(node);
            i--;

            if (!root)
                root = node;
        }
        // Pop the last node off the stack if a ) is found
        else if (c == ')')
        {
            nodeStack.pop();
        }
    }

    return root;
}

Node *TreeFactory::randomNode() const
{
    int chance = qrand() % 100;

    if (chance < 50)
        return randomFunction();
    else
        return randomTerminal();
}

Node *TreeFactory::randomFunction() const
{
    Q_ASSERT(functionSet->size() > 0);

    int chance = qrand() % functionSet->size();
    return functionSet->at(chance)();
}

Node *TreeFactory::randomTerminal() const
{
    Q_ASSERT(terminalSet->size() > 0);

    int chance = qrand() % terminalSet->size();
    return terminalSet->at(chance)();
}

Node *TreeFactory::nodeFromString(QString nodeName) const
{
    for (int i = 0; i < functionSet->size(); i++)
    {
        Node *node = functionSet->at(i)();
        if (node->getName() == nodeName)
            return node;
    }

    for (int i = 0; i < terminalSet->size(); i++)
    {
        Node *node = terminalSet->at(i)();
        if (node->getName() == nodeName)
            return node;
    }

    return NULL;
}
