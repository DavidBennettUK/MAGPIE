#include <QString>
#include <QQueue>
#include "Node.h"
#include "../common.h"

Node::~Node()
{
    clearChildren();
}

void Node::addChild(Node *child)
{
    Q_ASSERT(children.size() < arity);

    if (children.size() >= arity)
        return;

    children << child;
    child->parent = this;
}

void Node::replaceChild(Node *child, Node *newChild, bool deleteOld)
{
    Q_ASSERT(children.contains(child));

    if (!children.contains(child))
        return;

    int i = children.indexOf(child);
    Node *oldChild = children[i];
    children[i] = newChild;
    newChild->parent = this;

    if (deleteOld)
        safeDelete(oldChild);
}

void Node::clearChildren()
{
    foreach (Node *node, children)
        safeDelete(node);
    children.clear();
}

int Node::getSize() const
{
    if (children.empty())
        return 1;
    else
    {
        int size = 1;

        foreach (Node *child, children)
            size += child->getSize();

        return size;
    }
}

int Node::getHeight() const
{
    int height = 0;

    foreach (Node *child, children)
        height = std::max(height, child->getHeight());

    return height + 1;
}

int Node::getDepth() const
{
    if (parent)
        return parent->getDepth() + 1;
    else
        return 0;
}

Node *Node::getNode(const int index)
{
    Q_ASSERT(index < getSize() && index >= 0);

    // Check a valid index is given
    if (index >= getSize() || index < 0)
        return NULL;

    // Do depth-first traversal until we reach the target index
    QQueue<Node *> queue;
    queue.enqueue(this);

    for (int i = 0; i < index; i++)
    {
        Node *node = queue.dequeue();

        foreach (Node *child, node->getChildren())
            queue.enqueue(child);
    }

    return queue.front();
}

QString Node::toString() const
{
    QString s = "(" + name;

    foreach (Node *node, children)
        s += " " + node->toString();

    s += ")";

    return s;
}
