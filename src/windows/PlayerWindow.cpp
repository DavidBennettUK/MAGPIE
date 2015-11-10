#include <QVBoxLayout>
#include <QHBoxLayout>
#include "PlayerWindow.h"
#include "../gp/Individual.h"
#include "../widgets/LawnViewWidget.h"
#include "../widgets/LawnViewMultiWidget.h"
#include "../widgets/AntViewWidget.h"
#include "../common.h"

PlayerWindow::PlayerWindow(Individual *individual, QWidget *parent, int id, int generation) :
    QMainWindow(parent)
{
    setWindowTitle("Solution Viewer");

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout *verticalContainer = new QVBoxLayout(central);

    if (dynamic_cast<LawnmowerMulti *>(individual))
        glPlayer = new LawnViewMultiWidget(central);
    else if (dynamic_cast<Lawnmower *>(individual))
        glPlayer = new LawnViewWidget(central);
    else if (dynamic_cast<Ant *>(individual))
        glPlayer = new AntViewWidget(central);

    Q_ASSERT(glPlayer);
    verticalContainer->addWidget(glPlayer);

    QHBoxLayout *buttonContainer = new QHBoxLayout();
    verticalContainer->addLayout(buttonContainer);

    btnPlay = new QPushButton("Play", central);
    btnPlay->setCheckable(true);
    btnPlay->setMinimumWidth(60);
    buttonContainer->addWidget(btnPlay);
    connect(btnPlay, SIGNAL(clicked()), this, SLOT(play()));

    btnStep = new QPushButton("Step", central);
    btnStep->setMinimumWidth(60);
    buttonContainer->addWidget(btnStep);
    connect(btnStep, SIGNAL(clicked()), this, SLOT(stepButton()));

    btnReset = new QPushButton("Reset", central);
    btnReset->setMinimumWidth(60);
    buttonContainer->addWidget(btnReset);
    connect(btnReset, SIGNAL(clicked()), this, SLOT(reset()));

    this->individual = NULL;
    setIndividual(individual, id, generation);

    playTimer.setInterval(50);
    connect(&playTimer, SIGNAL(timeout()), this, SLOT(step()), Qt::QueuedConnection);
}

PlayerWindow::~PlayerWindow()
{
    safeDelete(individual);
}

void PlayerWindow::setIndividual(Individual *individual, int id, int generation)
{
    if (id >= 0 && generation >= 0)
        setWindowTitle("Lawnmower (Id: " + QString::number(id) + ", generation: " + QString::number(generation) + ")");
    else if (id >= 0 && generation < 0)
        setWindowTitle("Lawnmower (Id: " + QString::number(id) + ")");
    else
        setWindowTitle("Solution Viewer");

    if (this->individual)
    {
        stop();
        safeDelete(this->individual);
    }

    this->individual = individual;
    individual->reset();
    glPlayer->setIndividual(individual);
    glPlayer->update();
}

void PlayerWindow::stepButton()
{
    stop();
    step();
}

void PlayerWindow::play()
{
    if (btnPlay->isChecked())
        start();
    else
        stop();
}

void PlayerWindow::reset()
{
    stop();
    individual->reset();
    glPlayer->update();
}

void PlayerWindow::start()
{
    playTimer.start();
    btnPlay->setChecked(true);
}

void PlayerWindow::stop()
{
    playTimer.stop();
    btnPlay->setChecked(false);
}

void PlayerWindow::step()
{
    bool progress = individual->step();

    if (progress == false && playTimer.isActive())
    {
        playTimer.stop();
        btnPlay->setChecked(false);
    }

    glPlayer->update();
}
