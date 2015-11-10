#include <QMdiSubWindow>
#include "ExperimentLesson.h"
#include "../windows/StepWindow.h"
#include "../windows/GraphWindow.h"

ExperimentLesson::ExperimentLesson(QMdiArea *workspace) :
    Lesson(workspace)
{
    title = "Experiment";
    description = "Fully control a GP run, experiment with the parameters and see the results.";
    imageRes = ":/resources/lesson6_preview.png";
    stepWindow = NULL;
    generationWindow = NULL;
    graphWindow = NULL;
    runWindow = NULL;
    scenario = NULL;
}

void ExperimentLesson::load()
{
    addStep(new LessonStep("Introduction", "<p>Now it's your chance to experiment with a real <span class='keyword'>GP run</span>.</p><p>You may ignore these steps and experiment with the <span class='keyword'>parameters</span> as you wish, or <span class='thing'>carry on</span> for instructions, challenges and experiment ideas.</p>", this, workspace));
    addStep(new LessonStep("Run Statistics", "<p>The <span class='thing'>run statistics window</span> is used to display the results of the GP run. The <span class='thing'>fitness graph</span> shows how the fitness of indivdiuals <span class='keyword'>evolves</span> over generations. The <span class='thing'>tree graph</span> shows how the sizes of program trees <span class='keyword'>evolve</span>.</p><ul><li><span class='thing'>Zoom</span> -  scroll wheel</li><li><span class='thing'>Pan</span> - drag the mouse</li><li><span class='thing'>Zoom to fit</span> - double click the either axis label</li><li><span class='thing'>Hide plot line</span> - single click legend item</li></ul>", this, workspace));
    addStep(new LessonStep("Run Window", "<p>The <span class='thing'>run window</span> allows you to control the GP run, as well as being able to change the <span class='keyword'>parameters</span>.</p><ul><li><span class='thing'>Run</span> - starts the run</li><li><span class='thing'>Step</span> - advance one generation</li><li><span class='thing'>Reset</span> - clear the run and start again</li></ul><p>If the <span class='thing'>'stop run when target fitness reached' checkbox</span> is <span class='important'>ticked</span>, the GP run will <span class='important'>stop</span> when an individual with the <span class='thing'>target fitness</span> is found. You may continue the run by pressing the <span class='thing'>run button</span> again.</p>", this, workspace));
    addStep(new LessonStep("Challenge 1/4", "<b>Challenge 1</b><p>What is the least amount of generations a perfect solution can be found in?</p><p>Increasing the population or maximum tree size can help to find a solution in an earlier run, as there is more chance for a perfect solution to be found in a larger search space. Note that finding a solution in an earlier generation does not mean that the run was quicker, the execution time may increase.</p>", this, workspace));
    addStep(new LessonStep("Challenge 2/4", "<b>Challenge 2</b><p>What is the minimum tree height needed to produce a perfect solution?</p><p>Set the <span class='thing'>maximum tree height</span> to limit the height of trees.</p><p>Finding the right value for the maximum tree height is very important for more complex problems - if it is set too low then a solution may not be possible, but if set too high then it may take too long to find a solution.</p>", this, workspace));
    addStep(new LessonStep("Challenge 3/4", "<b>Challenge 3</b><p>What is the least amount of steps the problem can be solved in?</p><p>Try adjusting the <span class='thing'>'Max Moves'</span> parameter to set the maximum number of moves the lawnmower can take.</p>", this, workspace));
    addStep(new LessonStep("Challenge 4/4", "<b>Challenge 4</b><p>Can you find a solution for a bigger garden?</p><p>Use the <span class='thing'>'Grid Size'</span> parameter to adjust the size of the garden.</p><p>Remember to change the <span class='thing'>target fitness</span> when adjusting the grid size. A larger garden will require a larger fitness to complete. For example a 20x20 garden will need a solution with a fitness of 400 (20 * 20 = 400).</p><p>The lawnmower will also likely need a larger maximum number of moves, as it has more grass to mow.</p>", this, workspace));
    addStep(new LessonStep("Experiments", "<p>The next few steps will give ideas for experiments you may wish to try. A discussion of the results for each experiment will be in the following step.</p>", this, workspace));
    addStep(new LessonStep("Experiment 1/4", "<b>Experiment 1 - task</b><p>What is the difference between roulette and tournament selection?<br/>Hint: notice the effects on the highest fitness.</p>", this, workspace));
    addStep(new LessonStep("Experiment 1/4", "<b>Experiment 1 - results</b><p>Notice that the highest fitness tends to fluctuate more for roulette selection, where it is more steady for tournament selection. This is because roulette selection is more random, meaning that some of the best individuals may not be selected - whereas tournament selection tends to keep the best individuals.</p>", this, workspace));
    addStep(new LessonStep("Experiment 2/4", "<b>Experiment 2 - task</b><p>What is the effect of enabling elitism, especially on roulette selection?<br/>Hint: elitism is where the best individual from every generation is kept.</p>", this, workspace));
    addStep(new LessonStep("Experiment 2/4", "<b>Experiment 2 - results</b><p>Notice that the highest fitness will not decrease when elitism is enabled, as the best individual is always kept. This is very useful for improving roulette selection, where the best individuals may be lost due to chance.</p>", this, workspace));
    addStep(new LessonStep("Experiment 3/4", "<b>Experiment 3 - task</b><p>Is the perfect solution found always the same in different runs?<br/>Hint: use the player and tree views to view an individual.</p>", this, workspace));
    addStep(new LessonStep("Experiment 3/4", "<b>Experiment 3 - results</b><p>There are many different variations that may be found with 100 fitness. Some solutions may be similar to how a human would mow a lawn. Some solutions may be unexpected, such as a spiral pattern - this shows the usefulness of genetic programming to find solutions to problems we wouldn't necessarily think of.</p>", this, workspace));
    addStep(new LessonStep("Experiment 4/4", "<b>Experiment 4 - task</b><p>What is the effect of changing the mutation and crossover rates?</p>", this, workspace));
    addStep(new LessonStep("Experiment 4/4", "<b>Experiment 4 - results</b><p>Notice it is more difficult to achive a solution with either crossover or mutation alone.</p>", this, workspace));
    addStep(new LessonStep("Complete", "<p>All the experiments are now complete. Try to think of some of your own and why certain changes have the effects they do, revisiting some of the previous lessons for help if needed.</p>", this, workspace));

    stepWindow = workspace->addSubWindow(new StepWindow(this, workspace), Qt::WindowTitleHint);
    stepWindow->resize(500, 250);
    stepWindow->move(workspace->width() / 2 - stepWindow->frameGeometry().width() / 2,
                     workspace->height() - stepWindow->frameGeometry().height());
    stepWindow->show();

    scenario = new LawnmowerScenario();

    generationWindow = new GenerationWindow(workspace);
    QMdiSubWindow *genMDI = workspace->addSubWindow(generationWindow, Qt::WindowTitleHint);
    genMDI->resize(200, 550);
    genMDI->show();

    runWindow = new GPRunWindow(scenario, workspace);
    QMdiSubWindow *runMDI = workspace->addSubWindow(runWindow, Qt::WindowTitleHint);
    runMDI->move(workspace->width() - runMDI->frameGeometry().width(), 0);
    runMDI->show();

    graphWindow = new GraphWindow(scenario, workspace);
    QMdiSubWindow *graphMDI = workspace->addSubWindow(graphWindow, Qt::WindowTitleHint);
    graphMDI->resize(500, 400);
    graphMDI->move(workspace->width() / 2 - graphMDI->frameGeometry().width() / 2, 0);
    graphMDI->show();

    connect(scenario, SIGNAL(runFinished()), this, SLOT(runFinished()));
    connect(scenario, SIGNAL(generationComplete(QSharedPointer<Generation>,int)), this, SLOT(generationComplete(QSharedPointer<Generation>,int)));
    connect(scenario, SIGNAL(newRun()), this, SLOT(newRun()));
    connect(scenario, SIGNAL(runStarted()), generationWindow, SLOT(closeViewWindows()));
    connect(scenario, SIGNAL(runStarted()), generationWindow, SLOT(clear()));
}

void ExperimentLesson::unload()
{
    Lesson::unload();

    if (runWindow != NULL && runWindow->runThread.isRunning())
    {
        scenario->pauseRun();
        runWindow->runThread.quit();
        while (runWindow->runThread.isRunning());
    }

    safeDelete(scenario);
    stepWindow = NULL;
    generationWindow = NULL;
    runWindow = NULL;
    graphWindow = NULL;
}

void ExperimentLesson::runFinished()
{
    generationWindow->setGeneration(scenario->getCurrentGeneration(), scenario->getGenerationNumber());
}

void ExperimentLesson::generationComplete(QSharedPointer<Generation> generation, int number)
{
    Q_UNUSED(generation);
    Q_UNUSED(number);

    if (scenario->getState() == Scenario::PAUSED)
        generationWindow->setGeneration(scenario->getCurrentGeneration(), scenario->getGenerationNumber());
}

void ExperimentLesson::newRun()
{
    generationWindow->closeViewWindows();
    generationWindow->clear();
}
