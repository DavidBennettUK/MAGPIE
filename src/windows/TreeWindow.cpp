#include <QVBoxLayout>
#include "TreeWindow.h"
#include "../common.h"

TreeWindow::TreeWindow(Individual *individual, QWidget *parent, int id, int generation) :
    QMainWindow(parent)
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    this->setWindowTitle("Tree Viewer");

    QVBoxLayout *verticalContainer = new QVBoxLayout(central);

    glTree = new TreeViewWidget(central);
    verticalContainer->addWidget(glTree);

    this->individual = NULL;
    setIndividual(individual, id, generation);
}

TreeWindow::~TreeWindow()
{
    safeDelete(individual);
}

void TreeWindow::setIndividual(Individual *individual, int id, int generation)
{
    if (id >= 0 && generation >= 0)
        setWindowTitle("Tree (Id: " + QString::number(id) + ", generation: " + QString::number(generation) + ")");
    else if (id >= 0 && generation < 0)
        setWindowTitle("Tree (Id: " + QString::number(id) + ")");
    else
        setWindowTitle("Tree Viewer");

    if (this->individual)
        safeDelete(this->individual);

    this->individual = individual;
    individual->reset();
    glTree->setIndividual(individual);
    glTree->update();
}
