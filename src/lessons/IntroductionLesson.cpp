#include <QMdiSubWindow>
#include "IntroductionLesson.h"
#include "../windows/StepWindow.h"
#include "../scenarios/lawnmower/Lawnmower.h"
#include "../scenarios/lawnmower/LawnmowerScenario.h"
#include "../common.h"
#include "../gp/TreeFactory.h"

IntroductionLesson::IntroductionLesson(QMdiArea *workspace) :
    Lesson(workspace)
{
    title = "The lawnmower problem";
    description = "A simple problem that can be solved using genetic programming techniques.";
    imageRes = ":/resources/lesson1_preview.png";
    stepWindow = NULL;
    playerWindow = NULL;
}

void IntroductionLesson::load()
{
    addStep(new Step1("Introduction", "<p>The aim of the <span class='keyword'>lawnmower problem</span> is to produce a lawnmower that is capable of mowing <span class='important'>all</span> <span class='thing'>grass tiles</span> in a garden.</p><p>The <span class='thing'>player window</span> is used to graphically represent solutions for the problem.</p><p>The following <span class='keyword'>actions</span> may be performed:</p><ul><li><span class='thing'>Play</span> - toggle playing and pausing of the animation</li><li><span class='thing'>Step</span> - step through the animation one frame at a time</li><li><span class='thing'>Reset</span> - start the solution from the beginning</li></ul>", this, workspace));
    addStep(new LessonStep("Introduction", "<p>The garden is represented as a 10x10 <span class='thing'>grid</span> of tiles, initially <span class='important'>unmowed</span>.</p><p>The garden is <span class='keyword'>toroidal</span>, meaning that when the lawnmower reaches an edge it will jump to the opposite side of the garden.</p><p>The lawnmower is only capable of performing the following two <span class='keyword'>actions</span>:<ul><li><span class='thing'>Turn left</span> - rotate 90&deg; anticlockwise</li><li><span class='thing'>Mow</span> - move forward and mow the tile</li></ul></p><p>A 'turn right' action is not given, to keep the problem simple. The lawnmower can turn left three times to achieve the same effect.</p>", this, workspace));
    addStep(new LessonStep("Perfect Individual", "<p>The solution currently displayed is a <span class='keyword'>perfect solution</span> for the problem, where all <span class='thing'>grass tiles</span> are mowed <span class='important'>exactly once</span>.</p><p>The <span class='thing'>player window</span> shows the following statistics:</p><ul><li><span class='thing'>Moves</span> - the number of forward or left actions taken</li><li><span class='thing'>Points</span> - the number of mowed grass tiles, not including tiles mowed more than once</li></ul>", this, workspace));
    addStep(new Step4("Poor Individual", "<p>The <span class='thing'>player</span> now shows a <span class='keyword'>poor individual</span>, which is <span class='important'>not</span> able to mow all <span class='thing'>grass tiles</span>.</p><p>When the lawnmower repeatedly mows the same tile, the <span class='thing'>brightness</span> of that tile increases. This can be useful to help identify <span class='keyword'>repetitive patterns</span> a <span class='keyword'>solution</span> may have.</p><p>The lawnmower is given a maximum number of <span class='keyword'>moves</span> to complete the <span class='keyword'>solution</span> in, this prevents bad solutions from taking too much time. Some solutions, such as the one shown, may never be able to solve the problem.</p>", this, workspace));

    stepWindow = workspace->addSubWindow(new StepWindow(this, workspace), Qt::WindowTitleHint);
    stepWindow->resize(500, 250);
    stepWindow->move(workspace->width() / 2 - stepWindow->frameGeometry().width() / 2,
                     workspace->height() - stepWindow->frameGeometry().height());
    stepWindow->show();
}

void IntroductionLesson::unload()
{
    Lesson::unload();

    stepWindow = NULL;
    playerWindow = NULL;
}

void IntroductionLesson::Step1::load()
{
    LawnmowerScenario scenario;
    TreeFactory *treeBuilder = scenario.getTreeBuilder();

    Lawnmower *idealIndividual = new Lawnmower(new Environment());
    Node *idealRoot = treeBuilder->buildFromString("(Prog2 (Prog2 (Prog2 (Prog2 (Mow) (Mow)) (Prog2 (Mow) (Left))) (Prog2 (Prog2 (Left) (Left)) (Prog2 (Mow) (Left)))) (Prog2 (Prog2 (Mow) (Mow)) (Prog2 (Prog2 (Mow) (Mow)) (Prog2 (Mow) (Mow)))))");
    idealIndividual->setRootNode(idealRoot);

    ((IntroductionLesson *) lesson)->playerWindow = new PlayerWindow(idealIndividual, workspace);
    QMdiSubWindow *playerMDI = workspace->addSubWindow(((IntroductionLesson *) lesson)->playerWindow, Qt::WindowTitleHint);
    playerMDI->resize(500, 400);
    playerMDI->move(workspace->width() / 2 - playerMDI->frameGeometry().width() / 2, 0);
    playerMDI->show();
}

void IntroductionLesson::Step4::load()
{
    LawnmowerScenario scenario;
    TreeFactory *treeBuilder = scenario.getTreeBuilder();

    Lawnmower *poorIndividual = new Lawnmower(new Environment());
    Node *poorRoot = treeBuilder->buildFromString("(Mow)");
    poorIndividual->setRootNode(poorRoot);

    ((IntroductionLesson *) lesson)->playerWindow->setIndividual(poorIndividual);
}
