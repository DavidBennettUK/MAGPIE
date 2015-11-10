#include <QVBoxLayout>
#include <QTabWidget>
#include "GraphWindow.h"

GraphWindow::GraphWindow(Scenario *scenario, QWidget *parent) :
    QMainWindow(parent)
{
    this->scenario = scenario;

    QTabWidget *tabs = new QTabWidget(this);
    setCentralWidget(tabs);

    this->setWindowTitle("Run Statistics");

    fitnessGraph = new GraphWidget();
    tabs->addTab(fitnessGraph, "Fitness");

    fitnessGraph->xAxis->setLabel("Generation");

    fitnessGraph->yAxis->setLabel("Fitness");
   /* fitnessGraph->yAxis->setAutoTicks(false);
    QVector<double> yTicks;
    yTicks << 0 << 10 << 20 << 30 << 40 << 50 << 60 << 70 << 80 << 90 << 100;
    fitnessGraph->yAxis->setTickVector(yTicks);*/
    fitnessGraph->yAxis->setSubTickCount(4);
    fitnessGraph->yAxis->setRange(0, 100);

    fitnessGraph->addGraph();
    fitnessGraph->graph(0)->setName("Average");
    fitnessGraph->graph(0)->setPen(QPen(Qt::blue));

    fitnessGraph->addGraph();
    fitnessGraph->graph(1)->setName("Highest");
    fitnessGraph->graph(1)->setPen(QPen(Qt::red));

    fitnessGraph->addGraph();
    fitnessGraph->graph(2)->setName("Lowest");
    fitnessGraph->graph(2)->setPen(QPen(Qt::green));

    treeGraph = new GraphWidget();
    tabs->addTab(treeGraph, "Tree Size");

    treeGraph->xAxis->setLabel("Generation");

    treeGraph->yAxis->setLabel("Size");
    treeGraph->yAxis->setRangeLower(0);

    treeGraph->addGraph();
    treeGraph->graph(0)->setName("Average");
    treeGraph->graph(0)->setPen(QPen(Qt::blue));

    treeGraph->addGraph();
    treeGraph->graph(1)->setName("Largest");
    treeGraph->graph(1)->setPen(QPen(Qt::red));

    treeGraph->addGraph();
    treeGraph->graph(2)->setName("Smallest");
    treeGraph->graph(2)->setPen(QPen(Qt::green));

    setRange(scenario->getMaximumGenerations());

    connect(&animationTimer, SIGNAL(timeout()), this, SLOT(updateGraph()));
    connect(scenario, SIGNAL(runFinished()), this, SLOT(runFinished()));
    connect(scenario, SIGNAL(newRun()), this, SLOT(clear()));
    connect(scenario, SIGNAL(maxGenerationsChanged(int)), this, SLOT(setRange(int)));
    connect(scenario, SIGNAL(generationComplete(QSharedPointer<Generation>,int)), this, SLOT(generationComplete(QSharedPointer<Generation>,int)));
}

void GraphWindow::generationComplete(QSharedPointer<Generation> generation, int number)
{
    fitnessGraph->graph(0)->addData(number, generation->getAverageFitness());
    fitnessGraph->graph(1)->addData(number, generation->getHighestFitness());
    fitnessGraph->graph(2)->addData(number, generation->getLowestFitness());

    treeGraph->graph(0)->addData(number, generation->getAverageTreeSize());
    treeGraph->graph(1)->addData(number, generation->getLargestTreeSize());
    treeGraph->graph(2)->addData(number, generation->getSmallestTreeSize());

    if (!animationTimer.isActive())
        animationTimer.start(50); // TODO this is lame and shouldn't start timer for stepping
}

void GraphWindow::updateGraph()
{
    fitnessGraph->graph(0)->rescaleValueAxis();
    fitnessGraph->graph(1)->rescaleValueAxis(true);
    fitnessGraph->graph(2)->rescaleValueAxis(true);
    fitnessGraph->replot();

    treeGraph->graph(0)->rescaleValueAxis();
    treeGraph->graph(1)->rescaleValueAxis(true);
    treeGraph->graph(2)->rescaleValueAxis(true);
    treeGraph->replot();
}

void GraphWindow::clear()
{
    fitnessGraph->graph(0)->clearData();
    fitnessGraph->graph(1)->clearData();
    fitnessGraph->graph(2)->clearData();
    fitnessGraph->replot();

    treeGraph->graph(0)->clearData();
    treeGraph->graph(1)->clearData();
    treeGraph->graph(2)->clearData();
    treeGraph->replot();
}

void GraphWindow::runFinished()
{
    animationTimer.stop();
    updateGraph();
}

void GraphWindow::setRange(int range)
{
    fitnessGraph->xAxis->setRange(0, range);
    treeGraph->xAxis->setRange(0, range);
    fitnessGraph->replot();
    treeGraph->replot();
}
