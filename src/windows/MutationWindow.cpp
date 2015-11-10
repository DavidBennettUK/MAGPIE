#include <QVBoxLayout>
#include "MutationWindow.h"
#include "../common.h"

// TODO make resizing look nice
MutationWindow::MutationWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->parent = NULL;
    this->child = NULL;
    mutationPoint = 0;
    glMutation = NULL;

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    this->setWindowTitle("Mutation Viewer");

    QVBoxLayout *verticalContainer = new QVBoxLayout(central);

    glMutation = new MutationWidget(central);
    glMutation->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(glMutation, SIGNAL(finished()), this, SIGNAL(finished()));
    verticalContainer->addWidget(glMutation);
}

MutationWindow::~MutationWindow()
{
    safeDelete(parent);
    safeDelete(child);
}

void MutationWindow::setTrees(Node *parent, Node *child, int mutationPoint)
{
    this->parent = parent;
    this->child = child;
    this->mutationPoint = mutationPoint;
    this->glMutation->setTrees(parent, child, mutationPoint);
}

