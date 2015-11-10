#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMdiSubWindow>
#include "RouletteWindow.h"
#include "TreeWindow.h"

RouletteWindow::RouletteWindow(QMdiArea *workspace, Individual *winner, Generation *generation, GenerationWindow *generationWindow) :
    QMainWindow(workspace)
{
    Q_ASSERT(workspace);
    Q_ASSERT(winner);
    Q_ASSERT(generation);
    Q_ASSERT(generationWindow);

    this->winner = winner;
    this->generation = generation;
    this->workspace = workspace;
    this->generationWindow = generationWindow;

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    this->setWindowTitle("Roulette Selection");

    QVBoxLayout *verticalContainer = new QVBoxLayout(central);

    glRoulette = new RouletteWidget(winner, generation, central);
    glRoulette->setMinimumSize(100,100);
    verticalContainer->addWidget(glRoulette);
    connect(glRoulette, SIGNAL(finished()), this, SIGNAL(finished()));

    QHBoxLayout *buttonContainer = new QHBoxLayout();
    verticalContainer->addLayout(buttonContainer);

    QPushButton *btnShowWinner = new QPushButton("Highlight winner", central);
    buttonContainer->addWidget(btnShowWinner);
    connect(btnShowWinner, SIGNAL(clicked()), this, SLOT(showWinner()));

    QPushButton *btnReplay = new QPushButton("Replay", central);
    buttonContainer->addWidget(btnReplay);
    connect(btnReplay, SIGNAL(clicked()), this, SLOT(replay()));
}

void RouletteWindow::showWinner()
{
    generationWindow->selectIndividual(winner);
    generationWindow->parentWidget()->setFocus();
}

void RouletteWindow::replay()
{
    glRoulette->reset();
}
