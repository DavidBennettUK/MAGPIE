#ifndef GPRUNWINDOW_H
#define GPRUNWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QThread>
#include <QProgressBar>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QCheckBox>
#include <QGroupBox>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include "../gp/Scenario.h"

/**
 * Gives control over a GP run.
 * Allows various run parameters to be changed.
 * @author David Bennett
 */
class GPRunWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * Constructs the window.
     * @param scenario Scenario to control.
     * @param workspace Parent for this window.
     */
    explicit GPRunWindow(Scenario *scenario, QMdiArea *workspace);

private slots:
    /** Begins the GP run. If the run was paused it will continue. */
    void run();

    /** Step forward to the next generation. */
    void step();

    /** Restart the run from the beginning. */
    void reset();

    /**
     * Called when a generation has been completed to update the GUI.
     * @param generation Copy of the generation that has just completed.
     * @param number Number of the generation. 0 is the initial random generation.
     */
    void generationComplete(QSharedPointer<Generation> generation, int number);

    /** Called when the run has been completed to update the GUI. */
    void runFinished();

    /**
     * Set the target fitness for the scenario.
     * @param targetFitness The target fitness for the scenario to have.
     * @see Scenario#setTargetFitness(int)
     */
    void setTargetFitness(int targetFitness);

    /**
     * Set the maximum number of generations for the scenario.
     * @param maxGenerations The maximum number of generations for the scenario.
     * @see Scenario#setMaximumGenerations(int)
     */
    void setMaximumGenerations(int maxGenerations);

    /**
     * Set the population size of the scenario.
     * @param popluationSize The population size for the scenario.
     * @see Scenario#setPopulationSize(int)
     */
    void setPopulationSize(int popluationSize);

    /**
     * Set the maximum tree height of the scenario.
     * @param maxHeight The maximum tree height for the scenario.
     * @see Scenario#setMaximumTreeHeight(int)
     */
    void setMaximumTreeHeight(int maxHeight);

    /**
     * Ste the mutation rate for the scenario.
     * @param mutationRate The mutation rate for the scenario.
     * @see Scenario#setMutationRate(double)
     */
    void setMutationRate(double mutationRate);

    /**
     * Set the crossover rate for the scenario.
     * @param crossoverRate The crossover rate for the scenario.
     * @see Scenario#setCrossoverRate(double)
     */
    void setCrossoverRate(double crossoverRate);

    /**
     * Set the selection method for the scenario.
     * @param selection The selection method for the scenario.
     * @see Scenario#setSelection(QString)
     */
    void setSelection(QString selection);

    /**
     * Set the tournament size for the scenario.
     * @param tournamentSize The tournament size for the scenario.
     * @see Scenario#setTournamentSize(int)
     */
    void setTournamentSize(int tournamentSize);

    /**
     * Enable or disable elitism for the scenario.
     * @param enabled True if elitism should be enabled.
     * @see Scenario#setElitism(int)
     */
    void setElitism(int enabled);

    /** Update the elpased time of the run. */
    void updateTime();

public:
    QThread runThread; /**< Thread for the scenario to run in. */

private:
    QMdiArea *workspace; /**< Workspace for the window. */
    QProgressBar *progressBar; /**< The generation progress bar. */
    QPushButton *btnRun; /**< The run button. */
    QPushButton *btnStep; /**< The step button. */
    QPushButton *btnReset; /**< The reset button. */
    QCheckBox *chkFullRun; /**< Checkbox to set if a full run should be conducted. */
    QDoubleSpinBox *spnMutationRate; /**< Mutation rate spinner. */
    QDoubleSpinBox *spnCrossoverRate; /**< Crossover rate spinner. */
    QSpinBox *spnTournamentSize; /**< Tournamen size spinner. */
    QLabel *lblTime; /**< Label showing the elapsed time of the run. */
    QGroupBox *grpRun; /**< Group box of run parameters. */
    QGroupBox*grpSelection; /**< Group box of selection parameters. */
    QGroupBox *grpOperators; /**< Group box of operator parameters. */
    QGroupBox *grpParams; /**< Group box of problem specific parameters. */
    Scenario *scenario; /**< Pointer to the scenario being run. */
    QTimer runTimer; /**< Times the run. */
    QTime runTime; /**< Time since the run started. */
    int elapsedTime; /**< Amount of time elpased since the run started. */
    bool movedToThread; /**< True if the scenario has been moved into its own thread. */
    bool isRunFinished; /**< True if the run has finished. */

    /**
     * Toggle the usability of run options.
     * @param disable True if all options should be disabled.
     */
    void disableOptions(bool disable);
};

#endif // GPRUNWINDOW_H
