#include <QMdiSubWindow>
#include "AntLesson.h"
#include "../windows/StepWindow.h"
#include "../windows/GraphWindow.h"

#include "../windows/PlayerWindow.h"
#include "../windows/TreeWindow.h"

AntLesson::AntLesson(QMdiArea *workspace) :
    Lesson(workspace)
{
    title = "The artifical ant problem";
    description = "A more complex problem to solve.";
    imageRes = ":/resources/lesson8_preview.png";
    stepWindow = NULL;
    generationWindow = NULL;
    graphWindow = NULL;
    runWindow = NULL;
    scenario = NULL;
}

void AntLesson::load()
{
    addStep(new LessonStep("Introduction", "<p>The artificial ant problem features an <span class='thing'>ant</span> on a 32x32 <span class='keyword'>toroidal</span> <span class='thing'>grid</span>. There are <span class='thing'>food pellets</span> scattered in a <span class='thing'>trail</span> accross the <span class='thing'>grid</span>. The <span class='keyword'>goal</span> is to evolve an ant that is capable of collecting <span class='important'>all</span> <span class='thing'>food pellets</span> on the <span class='thing'>trail</span>.</p><p>The trail features several <span class='important'>gaps</span> of varying sizes, which the ant must learn to overcome.</p>", this, workspace));
    addStep(new LessonStep("Functional Nodes", "<p>The <span class='keyword'>functional set</span> contains the following nodes:</p><ul><li><span class='thing'>Prog2</span> - executes its two children from left to right</li><li><span class='thing'>Prog3</span> - executes its three children from left to right</li><li><span class='thing'>IfFoodAhead</span> - executes its left child if there is food in front of the ant, otherwise its right child is executed</li></ul>", this, workspace));
    addStep(new LessonStep("Terminal Nodes", "<p>The <span class='keyword'>terminal set</span> contains the following nodes:</p><ul><li><span class='thing'>Forward</span> - move the ant forward, collecting a food pellet from the new cell if present</li><li><span class='thing'>Left</span> - turn the ant left by 90&deg;</li><li><span class='thing'>Right</span> - turn the ant right by 90&deg;</li></ul>", this, workspace));
    addStep(new LessonStep("Ants", "<p>Ant <span class='keyword'>fitness</span> is calculated from the number of <span class='thing'>food pellets</span> <span class='important'>collected</span>. The more pellets collected, the better the solution.</p><p>A maximum number of moves is given to each ant, to stop solutions from simply visitng every cell on the grid and not learning to follow the trail. <span class='thing'>Forward</span>, <span class='thing'>left</span> and <span class='thing'>right</span> <span class='keyword'>actions</span> are all counted as moves.</p><p>The <span class='keyword'>termination criteria</span> will be met if all <span class='thing'>food pellets</span> are collected, or the maximum number of moves has been reached.</p>", this, workspace));
    addStep(new LessonStep("Challenge", "<p>Now it's your turn - try to find a solution for the problem.</p><p>It is very difficult to find a perfect solution for the problem, so try to collect as many pellets as possible.</p><p>Press next to see a solution.</p>", this, workspace));
    addStep(new FinalStep("Solution", "<p>A solution is now shown in the tree and player windows.</p><p>The ant will always move forward if there is food in front of it. Otherwise, it will make use of its sensor to check if there is food on its left or right side before continuing to move forward again.</p><p>Notice the size of the tree is relatively small, whereas most solutions generated are larger.</p>", this, workspace));

    stepWindow = workspace->addSubWindow(new StepWindow(this, workspace), Qt::WindowTitleHint);
    stepWindow->resize(500, 250);
    stepWindow->move(workspace->width() / 2 - stepWindow->frameGeometry().width() / 2,
                     workspace->height() - stepWindow->frameGeometry().height());
    stepWindow->show();

    scenario = new AntScenario();

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

void AntLesson::unload()
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

void AntLesson::runFinished()
{
    generationWindow->setGeneration(scenario->getCurrentGeneration(), scenario->getGenerationNumber());
}

void AntLesson::generationComplete(QSharedPointer<Generation> generation, int number)
{
    Q_UNUSED(generation);
    Q_UNUSED(number);

    if (scenario->getState() == Scenario::PAUSED)
        generationWindow->setGeneration(scenario->getCurrentGeneration(), scenario->getGenerationNumber());
}

void AntLesson::newRun()
{
    generationWindow->closeViewWindows();
    generationWindow->clear();
}

void AntLesson::FinalStep::load()
{
    AntScenario *scenario = ((AntLesson *) lesson)->scenario;
    Individual *ind = scenario->createIndividual("(IfFoodAhead (Forward) (Prog3 (Left) (Prog2 (IfFoodAhead (Forward) (Right)) (Right)) (Prog2 (IfFoodAhead (Forward) (Left)) (Forward))))");

    QMdiSubWindow *playerWindow = workspace->addSubWindow(new PlayerWindow(ind));
    playerWindow->resize(350, 400);
    playerWindow->move(0, 0);
    playerWindow->show();

    QMdiSubWindow *treeWindow = workspace->addSubWindow(new TreeWindow(ind->clone()));
    treeWindow->move(playerWindow->frameGeometry().width(), 0);
    treeWindow->show();

    playerWindow->move(workspace->width() / 2 - playerWindow->frameGeometry().width() / 2 - treeWindow->frameGeometry().width() / 2, 0);
    treeWindow->move(playerWindow->pos().x() + playerWindow->frameGeometry().width(), 0);
}
