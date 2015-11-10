#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QFormLayout>
#include <QTime>
#include "GPRunWindow.h"
#include "../common.h"
#include "../gp/TournamentSelection.h"
#include "../gp/RouletteSelection.h"
#include "../gp/IntValue.h"

GPRunWindow::GPRunWindow(Scenario *scenario, QMdiArea *workspace) :
    QMainWindow(workspace)
{
    this->scenario = scenario;
    connect(scenario, SIGNAL(generationComplete(QSharedPointer<Generation>,int)), this, SLOT(generationComplete(QSharedPointer<Generation>,int)));
    connect(scenario, SIGNAL(runFinished()), this, SLOT(runFinished()));

    this->workspace = workspace;

    movedToThread = false;
    isRunFinished = false;

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    this->setWindowTitle("Run");

    QVBoxLayout *verticalContainer = new QVBoxLayout(central);
    verticalContainer->setAlignment(Qt::AlignTop);

    QHBoxLayout *topContainer = new QHBoxLayout();
    verticalContainer->addLayout(topContainer);

    QLabel *lblGenerations = new QLabel("Generations");
    topContainer->addWidget(lblGenerations);

    elapsedTime = 0;
    lblTime = new QLabel("Time elapsed: 00:00:00:000");
    topContainer->addWidget(lblTime, 0, Qt::AlignRight);
    connect(&runTimer, SIGNAL(timeout()), this, SLOT(updateTime()));

    progressBar = new QProgressBar();
    progressBar->setMinimum(0);
    progressBar->setMaximum(scenario->getMaximumGenerations());
    progressBar->setValue(0);
    progressBar->setMinimumWidth(200);
    progressBar->setFormat("%v/%m");
    verticalContainer->addWidget(progressBar);

    QHBoxLayout *buttonContainer = new QHBoxLayout();
    verticalContainer->addLayout(buttonContainer);

    btnRun = new QPushButton("Run");
    btnRun->setCheckable(true);
    buttonContainer->addWidget(btnRun);
    connect(btnRun, SIGNAL(clicked()), this, SLOT(run()));

    btnStep = new QPushButton("Step");
    buttonContainer->addWidget(btnStep);
    connect(btnStep, SIGNAL(clicked()), this, SLOT(step()));

    btnReset = new QPushButton("Reset");
    buttonContainer->addWidget(btnReset);
    connect(btnReset, SIGNAL(clicked()), this, SLOT(reset()));

    chkFullRun = new QCheckBox("Stop run when target fitness reached", central);
    chkFullRun->setChecked(true);
    verticalContainer->addWidget(chkFullRun);

    grpRun = new QGroupBox("Run");
    verticalContainer->addWidget(grpRun);
    QFormLayout *grpRunLayout = new QFormLayout(grpRun);
    grpRun->setLayout(grpRunLayout);

    QSpinBox *spnTargetFitness = new QSpinBox(grpRun);
    spnTargetFitness->setMinimum(-999999);
    spnTargetFitness->setMaximum(999999);
    spnTargetFitness->setValue(scenario->getTargetFitness());
    grpRunLayout->addRow("Target Fitness", spnTargetFitness);
    connect(spnTargetFitness, SIGNAL(valueChanged(int)), this, SLOT(setTargetFitness(int)));

    QSpinBox *spnMaxGenerations = new QSpinBox(grpRun);
    spnMaxGenerations->setMinimum(1);
    spnMaxGenerations->setMaximum(50000);
    spnMaxGenerations->setSingleStep(100);
    spnMaxGenerations->setValue(scenario->getMaximumGenerations());
    grpRunLayout->addRow("Maximum Generations", spnMaxGenerations);
    connect(spnMaxGenerations, SIGNAL(valueChanged(int)), this, SLOT(setMaximumGenerations(int)));

    QSpinBox *spnPopulationSize = new QSpinBox(grpRun);
    spnPopulationSize->setMinimum(5);
    spnPopulationSize->setMaximum(500);
    spnPopulationSize->setSingleStep(5);
    spnPopulationSize->setValue(scenario->getPopulationSize());
    grpRunLayout->addRow("Population Size", spnPopulationSize);
    connect(spnPopulationSize, SIGNAL(valueChanged(int)), this, SLOT(setPopulationSize(int)));

    QSpinBox *spnMaxHeight = new QSpinBox(grpRun);
    spnMaxHeight->setMinimum(1);
    spnMaxHeight->setMaximum(10);
    spnMaxHeight->setSingleStep(1);
    spnMaxHeight->setValue(scenario->getTreeBuilder()->getMaxHeight());
    grpRunLayout->addRow("Maximum Tree Height", spnMaxHeight);
    connect(spnMaxHeight, SIGNAL(valueChanged(int)), this, SLOT(setMaximumTreeHeight(int)));

    grpSelection = new QGroupBox("Selection");
    verticalContainer->addWidget(grpSelection);
    QFormLayout *grpSelectionLayout = new QFormLayout(grpSelection);
    grpSelection->setLayout(grpSelectionLayout);

    QComboBox *cmbSelection = new QComboBox(grpSelection);
    cmbSelection->addItem("Tournament");
    cmbSelection->addItem("Roulette");
    grpSelectionLayout->addRow("Selection", cmbSelection);
    connect(cmbSelection, SIGNAL(currentIndexChanged(QString)), this, SLOT(setSelection(QString)));

    spnTournamentSize = new QSpinBox(grpSelection);
    spnTournamentSize->setMinimum(1);
    spnTournamentSize->setMaximum(scenario->getPopulationSize());
    spnTournamentSize->setSingleStep(1);
    spnTournamentSize->setValue(5);
    grpSelectionLayout->addRow("Tournament Size", spnTournamentSize);
    connect(spnTournamentSize, SIGNAL(valueChanged(int)), this, SLOT(setTournamentSize(int)));

    QCheckBox *chkElitism = new QCheckBox(grpSelection);
    chkElitism->setChecked(scenario->getElitism());
    grpSelectionLayout->addRow("Elitism", chkElitism);
    connect(chkElitism, SIGNAL(stateChanged(int)), this, SLOT(setElitism(int)));

    QString selectionMethod;
    if (dynamic_cast<RouletteSelection *>(scenario->getSelection()))
        selectionMethod = "Roulette";
    else
        selectionMethod = "Tournament";
    cmbSelection->setCurrentIndex(cmbSelection->findText(selectionMethod));
    setSelection(selectionMethod);

    grpOperators = new QGroupBox("GP Operators");
    verticalContainer->addWidget(grpOperators);
    QFormLayout *grpOperatorsLayout = new QFormLayout(grpOperators);
    grpOperators->setLayout(grpOperatorsLayout);

    spnMutationRate = new QDoubleSpinBox(grpOperators);
    spnMutationRate->setMinimum(0.0);
    spnMutationRate->setMaximum(1.0);
    spnMutationRate->setSingleStep(0.05);
    spnMutationRate->setValue(scenario->getMutationRate());
    grpOperatorsLayout->addRow("Mutation Rate", spnMutationRate);
    connect(spnMutationRate, SIGNAL(valueChanged(double)), this, SLOT(setMutationRate(double)));

    spnCrossoverRate = new QDoubleSpinBox(grpOperators);
    spnCrossoverRate->setMinimum(0.0);
    spnCrossoverRate->setMaximum(1.0);
    spnCrossoverRate->setSingleStep(0.05);
    spnCrossoverRate->setValue(scenario->getCrossoverRate());
    grpOperatorsLayout->addRow("Crossover Rate", spnCrossoverRate);
    connect(spnCrossoverRate, SIGNAL(valueChanged(double)), this, SLOT(setCrossoverRate(double)));

    grpParams = new QGroupBox("Problem Parameters");
    verticalContainer->addWidget(grpParams);
    QFormLayout *grpParamsLayout = new QFormLayout(grpParams);
    grpParams->setLayout(grpParamsLayout);

    foreach (IParameter *parameter, scenario->getParameters())
    {
        if (dynamic_cast<Parameter<IntValue *> *>(parameter))
        {
            IntValue *value = ((Parameter<IntValue *> *) parameter)->getValue();

            QSpinBox *spnParam = new QSpinBox(grpRun);
            spnParam->setMinimum(value->getMin());
            spnParam->setMaximum(value->getMax());
            spnParam->setSingleStep(1);
            spnParam->setValue(value->getValue());
            grpParamsLayout->addRow(parameter->getName(), spnParam);
            connect(spnParam, SIGNAL(valueChanged(int)), value, SLOT(setValue(int)));
        }
    }
}

void GPRunWindow::run()
{
    if (!btnRun->isChecked())
    {
        scenario->pauseRun();
    }
    else
    {
        if (!movedToThread)
        {
            scenario->moveToThread(&runThread);
            connect(scenario, SIGNAL(runFinished()), &runThread, SLOT(quit()));
            movedToThread = true;
        }
        else
        {
            disconnect(&runThread, SIGNAL(started()), scenario, SLOT(run()));
            disconnect(&runThread, SIGNAL(started()), scenario, SLOT(fullRun()));
        }

        if (isRunFinished || !chkFullRun->isChecked())
            connect(&runThread, SIGNAL(started()), scenario, SLOT(fullRun()));
        else
            connect(&runThread, SIGNAL(started()), scenario, SLOT(run()));

        chkFullRun->setDisabled(true);

        btnStep->setDisabled(true);
        btnReset->setDisabled(true);

        disableOptions(true);

        runTimer.start(10);
        runTime.start();
        runTime.restart();

        runThread.start();
    }
}

void GPRunWindow::step()
{
    disableOptions(true);
    scenario->nextGeneration();
}

void GPRunWindow::reset()
{
    isRunFinished = false;
    scenario->reset();
    progressBar->setValue(0);

    chkFullRun->setEnabled(true);

    btnRun->setEnabled(true);
    btnStep->setEnabled(true);

    elapsedTime = 0;
    lblTime->setText("Time Elapsed: 00:00:00:000");

    disableOptions(false);
}

void GPRunWindow::generationComplete(QSharedPointer<Generation> generation, int number)
{
    Q_UNUSED(generation);
    progressBar->setValue(number);
}

void GPRunWindow::runFinished()
{
    isRunFinished = true;

    if (scenario->getGenerationNumber() < scenario->getMaximumGenerations())
    {
        btnStep->setEnabled(true);
    }
    else
    {
        btnRun->setEnabled(false);
    }

    btnRun->setChecked(false);
    btnReset->setEnabled(true);

    runTimer.stop();
}

void GPRunWindow::setTargetFitness(int targetFitness)
{
    scenario->setTargetFitness(targetFitness);
}

void GPRunWindow::setMaximumGenerations(int maxGenerations)
{
    scenario->setMaximumGenerations(maxGenerations);
    progressBar->setMaximum(maxGenerations);
}

void GPRunWindow::setPopulationSize(int popluationSize)
{
    scenario->setPopulationSize(popluationSize);
    spnTournamentSize->setMaximum(popluationSize);
}

void GPRunWindow::setMaximumTreeHeight(int maxHeight)
{
    scenario->getTreeBuilder()->setMaxHeight(maxHeight);
}

void GPRunWindow::setMutationRate(double mutationRate)
{
    scenario->setMutationRate(mutationRate);

    if (mutationRate + spnCrossoverRate->value() > 1.0)
        spnCrossoverRate->setValue(1.0 - mutationRate);
}

void GPRunWindow::setCrossoverRate(double crossoverRate)
{
    scenario->setCrossoverRate(crossoverRate);

    if (crossoverRate + spnMutationRate->value() > 1.0)
        spnMutationRate->setValue(1.0 - crossoverRate);
}

void GPRunWindow::setSelection(QString selection)
{
    if (selection == "Roulette")
    {
        scenario->setSelection(new RouletteSelection());
        ((QFormLayout *) grpSelection->layout())->itemAt(2)->widget()->hide();
        ((QFormLayout *) grpSelection->layout())->itemAt(3)->widget()->hide();
    }
    else if (selection == "Tournament")
    {
        scenario->setSelection(new TournamentSelection(5));
        ((QFormLayout *) grpSelection->layout())->itemAt(2)->widget()->show();
        ((QFormLayout *) grpSelection->layout())->itemAt(3)->widget()->show();
    }
    else
    {
        Q_ASSERT_X(false, "GPRunWindow::setSelection", "Invalid selection method chosen");
    }
}

void GPRunWindow::setTournamentSize(int tournamentSize)
{
    Q_ASSERT(tournamentSize <= scenario->getPopulationSize());

    scenario->setSelection(new TournamentSelection(tournamentSize));
}

void GPRunWindow::setElitism(int enabled)
{
    scenario->setElitism(enabled == 2);
}

void GPRunWindow::updateTime()
{
    elapsedTime += runTime.elapsed();
    runTime.restart();

    QString hrs = QString::number(elapsedTime / (1000 * 60 * 60)).rightJustified(2, '0');
    QString mins = QString::number((elapsedTime % (1000 * 60 * 60)) / (1000 * 60)).rightJustified(2, '0');
    QString secs = QString::number(((elapsedTime % (1000 * 60 * 60)) % (1000 * 60)) / 1000).rightJustified(2, '0');
    QString ms = QString::number(((elapsedTime % (1000 * 60 * 60)) % (1000 * 60)) % 1000).rightJustified(3, '0');

    lblTime->setText("Time Elapsed: " + hrs + ":" + mins + ":" + secs + ":" + ms);
}

void GPRunWindow::disableOptions(bool disable)
{
    grpRun->setDisabled(disable);
    grpOperators->setDisabled(disable);
    grpSelection->setDisabled(disable);
    grpParams->setDisabled(disable);
}
