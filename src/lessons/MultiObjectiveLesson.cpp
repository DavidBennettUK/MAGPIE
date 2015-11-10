#include <QMdiSubWindow>
#include "MultiObjectiveLesson.h"
#include "../windows/StepWindow.h"
#include "../windows/GraphWindow.h"

MultiObjectiveLesson::MultiObjectiveLesson(QMdiArea *workspace) :
    Lesson(workspace)
{
    title = "Multi-objective genetic programming";
    description = "Add another objective to the lawnmower problem - to avoid obstacles.";
    imageRes = ":/resources/lesson7_preview.png";
    stepWindow = NULL;
    generationWindow = NULL;
    graphWindow = NULL;
    runWindow = NULL;
    scenario = NULL;
}

void MultiObjectiveLesson::load()
{
    addStep(new LessonStep("Introduction", "<p><span class='keyword'>Multi-objective</span> genetic programming is where individuals have <span class='important'>more than one</span> <span class='keyword'>objective</span>.</p><p>In the previous lessons, the <span class='thing'>lawnmower</span> only had a <span class='important'>single</span> objective - to mow as many tiles as possible.</p><p>We will now add a <span class='important'>second</span> objective, to increase the complexity of the problem.</p>", this, workspace));
    addStep(new LessonStep("Second Objective", "<p><span class='important'>Obstacles</span> have been randomly placed on the <span class='thing'>lawn</span>. The <span class='important'>second</span> <span class='keyword'>objective</span> of the <span class='thin'>lawnmower</span> is to <span class='important'>avoid</span> these obstacles while mowing the lawn.</p><p>The <span class='keyword'>fitness function</span> must be modified to account for multiple objectives. To encourage individuals to avoid the obstacles, a <span class='important'>penalty</span> is deducted from their fitness if they hit an obstacle. The penalty can be adjusted in the <span class='thing'>problem parameters pane</span>. Fitnesses can now become negative, if too many penalties are incurred.</p>", this, workspace));
    addStep(new LessonStep("A New Functional Node", "<p>To give the lawnmowers a better chance, we have added a new <span class='keyword'>functional node</span> so they can detect obstacles:</p><ul><li><span class='thing'>IfObsAhead</span> - exectutes its left child if there is an obstacle ahead, otherwise its right child is executed.</li></ul><p>Without this new node, the lawnmowers would be <span class='important'>blind</span> - only avoiding obstacles by chance.</p>", this, workspace));
    addStep(new LessonStep("Obstacles", "<p>The positions of the obstacles are <span class='important'>randomised</span>. This is to avoid lawnmowers coincidentally developing paths that avoid the obstacles.</p><p>The number of obstacles can be adjusted in the <span class='thing'>problem parameters pane</span>.</p>", this, workspace));
    addStep(new LessonStep("Challenge 1/2", "<b>Challenge 1</b><p>Try to find a solution that is able to mow all of the grass, whilst avoiding the obstacles.</p><p>You may want to try increasing the number of moves, as the lawnmower has more work to do to avoid obstacles.</p><p>You may also want to try adjusting the penalty, to encourage the solutions to avoid the obstacles.</p>", this, workspace));
    addStep(new LessonStep("Challenge 2/2", "<b>Challenge 2</b><p>Try adding more obstacles for the lawnmower to avoid and see if the lawnmower is still able to cope.</p>", this, workspace));

    stepWindow = workspace->addSubWindow(new StepWindow(this, workspace), Qt::WindowTitleHint);
    stepWindow->resize(500, 250);
    stepWindow->move(workspace->width() / 2 - stepWindow->frameGeometry().width() / 2,
                     workspace->height() - stepWindow->frameGeometry().height());
    stepWindow->show();

    scenario = new LawnmowerMultiScenario();

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

void MultiObjectiveLesson::unload()
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

void MultiObjectiveLesson::runFinished()
{
    generationWindow->setGeneration(scenario->getCurrentGeneration(), scenario->getGenerationNumber());
}

void MultiObjectiveLesson::generationComplete(QSharedPointer<Generation> generation, int number)
{
    Q_UNUSED(generation);
    Q_UNUSED(number);

    if (scenario->getState() == Scenario::PAUSED)
        generationWindow->setGeneration(scenario->getCurrentGeneration(), scenario->getGenerationNumber());
}

void MultiObjectiveLesson::newRun()
{
    generationWindow->closeViewWindows();
    generationWindow->clear();
}
