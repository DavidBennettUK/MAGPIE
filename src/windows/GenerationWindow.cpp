#include <QMdiSubWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QVector>
#include <QMessageBox>
#include "GenerationWindow.h"
#include "../gp/Generation.h"
#include "../gp/Individual.h"
#include "PlayerWindow.h"
#include "TreeWindow.h"
#include "../gp/TournamentSelection.h"
#include "../gp/RouletteSelection.h"

GenerationWindow::GenerationWindow(QMdiArea *workspace) :
    QMainWindow(workspace)
{
    generation = NULL;
    this->workspace = workspace;
    setGenerationNumber(-1);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout *verticalContainer = new QVBoxLayout(central);

    tblPopulation = new QTableWidget(central);
    tblPopulation->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    tblPopulation->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tblPopulation->setSelectionMode(QAbstractItemView::SingleSelection);
    tblPopulation->setSelectionBehavior(QAbstractItemView::SelectRows);
    tblPopulation->setSortingEnabled(true);
    tblPopulation->horizontalHeader()->setStretchLastSection(true);
    tblPopulation->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    tblPopulation->verticalHeader()->setVisible(false);
    tblPopulation->setColumnCount(2);
    tblPopulation->setHorizontalHeaderLabels(QString("Id;Fitness").split(";"));
    verticalContainer->addWidget(tblPopulation);

    QHBoxLayout *buttonContainer = new QHBoxLayout();
    verticalContainer->addLayout(buttonContainer);

    QPushButton *btnPlayIndividual = new QPushButton("Show in player", central);
    buttonContainer->addWidget(btnPlayIndividual);
    connect(btnPlayIndividual, SIGNAL(clicked()), this, SLOT(playIndividual()));

    QPushButton *btnViewTree = new QPushButton("View tree", central);
    buttonContainer->addWidget(btnViewTree);
    connect(btnViewTree, SIGNAL(clicked()), this, SLOT(viewTree()));

    QPushButton *btnCloseAll = new QPushButton("Close opened windows", central);
    verticalContainer->addWidget(btnCloseAll);
    connect(btnCloseAll, SIGNAL(clicked()), this, SLOT(closeViewWindows()));
}

void GenerationWindow::setGeneration(Generation *generation, int number)
{
    Q_ASSERT(generation);

    clear();

    setGenerationNumber(number);

    this->generation = generation;

    // Fill table with individuals
    for (int i = 0; i < generation->getSize(); i++)
    {
        Individual *ind = generation->getPopulation()[i];
        addIndividual(ind);
    }

    tblPopulation->resizeRowsToContents();
}

void GenerationWindow::setGenerationNumber(int number)
{
    generationNumber = number;

    if (number >= 0)
        setWindowTitle("Generation: " + QString::number(number));
    else
        setWindowTitle("Population");
}

void GenerationWindow::selectIndividual(Individual *individual)
{
    int i = generation->getPopulation().indexOf(individual);
    tblPopulation->selectRow(i);
}

void GenerationWindow::playIndividual()
{
    if (tblPopulation->selectedItems().empty())
    {
        QMessageBox msgBox;
        msgBox.setText("Please select an individual.");
        msgBox.exec();
        return;
    }

    int i = tblPopulation->selectedItems()[0]->text().toInt();

    if (playerWindows.contains(i))
    {
        playerWindows[i]->setFocus();
    }
    else
    {
        Individual *individual = generation->getPopulation()[i]->clone();

        PlayerWindow *playerWindow = new PlayerWindow(individual, this->parentWidget(), i, generationNumber);
        QMdiSubWindow *mdiWindow = workspace->addSubWindow(playerWindow);
        mdiWindow->resize(300,350);

        // Spawn windows on right hand side if the generation window in on the left of the screen, else visa versa
        // TODO make this better with proper window managemnet
        if (this->parentWidget()->pos().x() == 0)
        {
            mdiWindow->move(playerWindows.empty() ? this->parentWidget()->pos().x() + this->parentWidget()->frameGeometry().width() : playerWindowList.last()->x(),
                            playerWindows.empty() ? 0 : playerWindowList.last()->y() + playerWindowList.last()->frameGeometry().height());
        }
        else
        {
            mdiWindow->move(playerWindows.empty() ? this->parentWidget()->pos().x() - mdiWindow->frameGeometry().width() : playerWindowList.last()->x(),
                            playerWindows.empty() ? 0 : playerWindowList.last()->y() + playerWindowList.last()->frameGeometry().height());

        }

        mdiWindow->show();
        connect(mdiWindow, SIGNAL(destroyed(QObject *)), this, SLOT(playerWindowClosed(QObject*)));

        playerWindows.insert(i, mdiWindow);
        playerWindowList << mdiWindow;
    }
}

void GenerationWindow::viewTree()
{
    if (tblPopulation->selectedItems().empty())
    {
        QMessageBox msgBox;
        msgBox.setText("Please select an individual.");
        msgBox.exec();
        return;
    }

    int i = tblPopulation->selectedItems()[0]->text().toInt();

    if (treeWindows.contains(i))
    {
        treeWindows[i]->setFocus();
    }
    else
    {
        Individual *individual = generation->getPopulation()[i]->clone();

        TreeWindow *treeWindow = new TreeWindow(individual, this->parentWidget(), i, generationNumber);
        QMdiSubWindow *mdiWindow = workspace->addSubWindow(treeWindow);

        // Spawn windows on right hand side if the generation window in on the left of the screen, else visa versa
        // TODO make this better with proper window managemnet
        if (this->parentWidget()->pos().x() == 0)
        {
            mdiWindow->move(treeWindows.empty() ? this->parentWidget()->pos().x() + this->parentWidget()->frameGeometry().width() + 300 : treeWindowList.last()->x(),
                            treeWindows.empty() ? 0 : treeWindowList.last()->y() + treeWindowList.last()->frameGeometry().height());
        }
        else
        {
            mdiWindow->move(treeWindows.empty() ? this->parentWidget()->pos().x() - mdiWindow->frameGeometry().width() - 300 : treeWindowList.last()->x() + treeWindowList.last()->frameGeometry().width() - mdiWindow->frameGeometry().width(),
                            treeWindows.empty() ? 0 : treeWindowList.last()->y() + treeWindowList.last()->frameGeometry().height());
        }

        mdiWindow->show();
        connect(mdiWindow, SIGNAL(destroyed(QObject *)), this, SLOT(treeWindowClosed(QObject*)));

        treeWindows.insert(i, mdiWindow);
        treeWindowList << mdiWindow;
    }
}

void GenerationWindow::addIndividual(Individual *individual)
{
    int i = tblPopulation->rowCount();
    tblPopulation->setRowCount(tblPopulation->rowCount() + 1);

    QTableWidgetItem *id = new QTableWidgetItem();
    id->setData(Qt::DisplayRole, i);
    tblPopulation->setItem(i, 0, id);

    QTableWidgetItem *fitness = new QTableWidgetItem();
    fitness->setData(Qt::DisplayRole, individual->getFitness()->getValue());
    tblPopulation->setItem(i, 1, fitness);
}

void GenerationWindow::clear()
{
    setGenerationNumber(-1);
    tblPopulation->clearContents();
    tblPopulation->setRowCount(0);
}

void GenerationWindow::closeViewWindows()
{
    foreach (QMdiSubWindow *window, playerWindows)
        window->close();
    foreach (QMdiSubWindow *window, treeWindows)
        window->close();
}

void GenerationWindow::playerWindowClosed(QObject *object)
{
    QMdiSubWindow *window = (QMdiSubWindow *) object;
    playerWindows.remove(playerWindows.key(window));
    playerWindowList.remove(playerWindowList.indexOf(window));
}

void GenerationWindow::treeWindowClosed(QObject *object)
{
    QMdiSubWindow *window = (QMdiSubWindow *) object;
    treeWindows.remove(treeWindows.key(window));
    treeWindowList.remove(treeWindowList.indexOf(window));
}
