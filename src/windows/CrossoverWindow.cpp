#include <QVBoxLayout>
#include <QPushButton>
#include "CrossoverWindow.h"
#include "../common.h"

// TODO make resizing look nice
CrossoverWindow::CrossoverWindow(QWidget *parent) :
    QMainWindow(parent)
{
    parent1 = NULL;
    parent2 = NULL;
    child1 = NULL;
    child2 = NULL;
    memset(&crossoverResult, 0, sizeof(CrossoverResult));

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    this->setWindowTitle("Crossover Viewer");

    QVBoxLayout *verticalContainer = new QVBoxLayout(central);

    glCrossover = new CrossoverWidget(central);
    glCrossover->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(glCrossover, SIGNAL(finished()), this, SIGNAL(finished()));
    verticalContainer->addWidget(glCrossover);

    QPushButton *btnReset = new QPushButton("Replay", central);
    connect(btnReset, SIGNAL(clicked()), this, SLOT(reset()));
    verticalContainer->addWidget(btnReset);
}

CrossoverWindow::~CrossoverWindow()
{
    safeDelete(parent1);
    safeDelete(parent2);
    safeDelete(child1);
    safeDelete(child2);
}

void CrossoverWindow::setTrees(Node *parent1, Node *parent2, Node *child1, Node *child2, CrossoverResult crossoverResult)
{
    this->parent1 = parent1;
    this->parent2 = parent2;
    this->child1 = child1;
    this->child2 = child2;
    this->crossoverResult = crossoverResult;
    this->glCrossover->setTrees(parent1, parent2, child1, child2, crossoverResult);
}

void CrossoverWindow::reset()
{
    glCrossover->setTrees(parent1, parent2, child1, child2, crossoverResult);
    glCrossover->update();
}
