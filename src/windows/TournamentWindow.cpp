#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QMdiSubWindow>
#include "TournamentWindow.h"
#include "TreeWindow.h"
#include "../common.h"

TournamentWindow::TournamentWindow(QMdiArea *workspace, Individual *winner, QVector<Individual *> contestants, GenerationWindow *generationWindow) :
    QMainWindow(workspace)
{
    this->workspace = workspace;
    this->winner = winner;
    this->contestants = contestants;
    this->generationWindow = generationWindow;
    timer = NULL;

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    this->setWindowTitle("Tournament Selection");

    QVBoxLayout *verticalContainer = new QVBoxLayout(central);

    for (int i = 0; i < contestants.size(); i++)
    {
        Individual *contestant = contestants[i];

        QGroupBox *groupBox = new QGroupBox("Contestant " + QString::number(i + 1), central);
        groupBox->setMinimumWidth(200);
        QVBoxLayout *contestantContainer = new QVBoxLayout();

        QLabel *lblContestant = new QLabel(central);
        lblContestant->setText("Fitness: " + QString::number(contestant->getFitness()->getValue()));
        contestantContainer->addWidget(lblContestant);

        groupBox->setLayout(contestantContainer);
        verticalContainer->addWidget(groupBox);

        contestantLabels << lblContestant;
    }

    QHBoxLayout *buttonContainer = new QHBoxLayout();
    verticalContainer->addLayout(buttonContainer);

    QPushButton *btnShowWinner = new QPushButton("Highlight winner", central);
    buttonContainer->addWidget(btnShowWinner);
    connect(btnShowWinner, SIGNAL(clicked()), this, SLOT(showWinner()));

    QPushButton *btnReplay = new QPushButton("Replay", central);
    buttonContainer->addWidget(btnReplay);
    connect(btnReplay, SIGNAL(clicked()), this, SLOT(replay()));

    replay();
}

TournamentWindow::~TournamentWindow()
{
    safeDelete(timer);
}

void TournamentWindow::tick()
{
    if (comparing < contestants.size())
    {
        if (comparing > 0)
        {
            int fitness = contestants[comparing]->getFitness()->getValue();

            if (fitness > contestants[highest]->getFitness()->getValue())
            {
                contestantLabels[comparing]->setStyleSheet("background-color: #3F3");
                contestantLabels[highest]->setStyleSheet("background-color: #F33");
                highest = comparing;
            }
            else
                contestantLabels[comparing]->setStyleSheet("background-color: #F33");
        }
        else
            contestantLabels[comparing]->setStyleSheet("background-color: #3F3");

        comparing++;
    }
    else
    {
        timer->stop();
    }
}

void TournamentWindow::replay()
{
    safeDelete(timer);
    comparing = 0;
    highest = 0;

    for (int i = 0; i < contestantLabels.size(); i++)
        contestantLabels[i]->setStyleSheet("background-color: #EEE");

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer->start(1000);
}

void TournamentWindow::showWinner()
{
    generationWindow->selectIndividual(winner);
    generationWindow->parentWidget()->setFocus();
}
