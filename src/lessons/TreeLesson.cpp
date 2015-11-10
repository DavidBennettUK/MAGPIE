#include <QMdiSubWindow>
#include "TreeLesson.h"
#include "../windows/StepWindow.h"
#include "../windows/GenerationWindow.h"
#include "../windows/TreeWindow.h"
#include "../windows/PlayerWindow.h"
#include "../scenarios/lawnmower/LawnmowerScenario.h"
#include "../scenarios/lawnmower/Lawnmower.h"

TreeLesson::TreeLesson(QMdiArea *workspace) :
    Lesson(workspace)
{
    title = "Program trees";
    description = "Shows how genetic programs can be represented using tree structures.";
    imageRes = ":/resources/lesson2_preview.png";

    individual = NULL;
    stepWindow = NULL;
    playerWindow = NULL;
    treeWindow = NULL;
}

void TreeLesson::load()
{
    LawnmowerScenario scenario;
    TreeFactory *treeBuilder = scenario.getTreeBuilder();
    individual = new Lawnmower(new Environment());
    Node *root = treeBuilder->buildFromString("(Prog2 (Prog2 (Prog2 (Mow) (Mow)) (Mow)) (Prog2 (Mow) (Left))");
    individual->setRootNode(root);

    addStep(new Step1("Trees", "<p>Genetic programs may be represented using <span class='keyword'>tree structures</span>, with each <span class='keyword'>node</span> of the tree representing an instruction. Nodes are generally executed from <span class='important'>left to right</span>.</p>", this, workspace));
    addStep(new LessonStep("Tree Viewer", "<p>The <span class='thing'>tree viewer</span> is used to graphically represent a program tree, it currently shows an example solution for the lawnmower problem. The following actions may be performed:</p><ul><li><span class='thing'>Zoom</span> - mouse scroll wheel</li><li><span class='thing'>Pan</span> - click and drag</li><li><span class='thing'>Fit tree to window</span> - double click</li></ul>", this, workspace));
    addStep(new LessonStep("Functional and Terminal Sets", "<p>Every problem has a <span class='important'>limited</span> number of <span class='keyword'>node types</span> which solutions can be built from, categorised into <span class='keyword'>terminal</span> and <span class='keyword'>functional</span> nodes.</p><p>The <span class='thing'>terminal set</span> contains <span class='keyword'>leaf</span> nodes, which <span class='important'>cannot</span> have child nodes. These nodes are displayed in <span style='background-color:#FFF'>white</span>.</p><p>The <span class='thing'>functional set</span> contains nodes which <span class='important'>must</span> have child nodes. These nodes are displayed in <span style='background-color:#FF0'>yellow</span></p>", this, workspace));
    addStep(new LessonStep("Lawnmower Representation", "<p>The lawnmower problem is represented using the following nodes:</p><h4>Functional set</h4><ul><li><span class='thing'>Prog2</span> - program node with <span class='important'>two</span> children, executing them from left to right</li></ul><h4>Terminal set</h4></p><ul><li><span class='thing'>Left</span> - rotate 90&deg; anticlockwise</li><li><span class='thing'>Mow</span> - move forward and mow the tile</li></ul>", this, workspace));
    addStep(new Step5("Lawnmower Tree", "<p>The <span class='thing'>program tree</span> currently shown represents the lawnmower displayed in the <span class='thing'>player window</span>.</p><p>Use the <span class='thing'>play button</span> to view the solution.</p><p>The <span class='thing'>step button</span> may be used to execute the program tree one node at a time.</p>", this, workspace));

    stepWindow = workspace->addSubWindow(new StepWindow(this, workspace), Qt::WindowTitleHint);
    stepWindow->resize(500, 250);
    stepWindow->move(workspace->width() / 2 - stepWindow->frameGeometry().width() / 2,
                     workspace->height() - stepWindow->frameGeometry().height());
    stepWindow->show();
}

void TreeLesson::unload()
{
    Lesson::unload();

    safeDelete(individual);
    stepWindow = NULL;
    treeWindow = NULL;
    playerWindow = NULL;
}

void TreeLesson::Step1::load()
{
    TreeWindow *treeWindow = new TreeWindow(((TreeLesson *) lesson)->individual->clone(), workspace);
    ((TreeLesson *) lesson)->treeWindow = workspace->addSubWindow(treeWindow, Qt::WindowTitleHint);
    ((TreeLesson *) lesson)->treeWindow->move(workspace->width() / 2 - ((TreeLesson *) lesson)->treeWindow->frameGeometry().width() / 2, 0);
    ((TreeLesson *) lesson)->treeWindow->show();
}

void TreeLesson::Step5::load()
{
    QMdiSubWindow *treeMDI = ((TreeLesson *) lesson)->treeWindow;
    PlayerWindow *playWindow = new PlayerWindow((Lawnmower *) ((TreeLesson *) lesson)->individual->clone(), workspace);
    QMdiSubWindow *playMDI = workspace->addSubWindow(playWindow, Qt::WindowTitleHint);
    playMDI->resize(500,400);
    playMDI->move(workspace->width() / 2 - playMDI->frameGeometry().width() / 2 - treeMDI->frameGeometry().width() / 2, 0);
    treeMDI->move(playMDI->pos().x() + playMDI->frameGeometry().width(), 0);
    playMDI->show();
    ((TreeLesson *) lesson)->playerWindow = playMDI;
}
