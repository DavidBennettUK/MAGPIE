#include "OperatorsLesson.h"
#include "../windows/CrossoverWindow.h"
#include "../windows/MutationWindow.h"
#include "../windows/RouletteWindow.h"
#include "../windows/GenerationWindow.h"
#include "../windows/StepWindow.h"
#include "../common.h"
#include "../scenarios/lawnmower/LawnmowerScenario.h"

OperatorsLesson::OperatorsLesson(QMdiArea *workspace) : Lesson(workspace)
{
    title = "Genetic programming operators";
    description = "The basic operations that may be performed on genetic programming trees.";
    imageRes = ":/resources/lesson4_preview.png";
    scenario = NULL;
    stepWindow = NULL;
    generationWindow = NULL;
    rouletteWindow1 = NULL;
    rouletteWindow2 = NULL;
    individual1 = NULL;
    individual2 = NULL;
    individual3 = NULL;
}

void OperatorsLesson::load()
{
    // Set a seed so the lesson is the same every time
    qsrand(100);

    scenario = new LawnmowerScenario();

    generationWindow = new GenerationWindow(workspace);
    Generation *generation = new Generation(scenario->getPopulationSize());

    individual1 = scenario->createIndividual("(Prog2 (Mow) (Left))");
    individual2 = scenario->createIndividual("(Prog2 (Prog2 (Left) (Mow)) (Prog2 (Mow) (Left)))");
    individual3 = scenario->createIndividual("(Prog2 (Prog2 (Left) (Mow)) (Left))");
    generation->addIndividual(individual1);
    generation->addIndividual(individual2);
    generation->addIndividual(individual3);
    generation->addIndividual(scenario->createIndividual("(Mow)"));
    generation->addIndividual(scenario->createIndividual("(Left)"));
    generation->addIndividual(scenario->createIndividual("(Prog2 (Prog2 (Mow) (Mow)) (Left))"));
    generation->addIndividual(scenario->createIndividual("(Left)"));
    generation->addIndividual(scenario->createIndividual("(Prog2 (Left) (Mow))"));
    generation->addIndividual(scenario->createIndividual("(Prog2 (Mow) (Prog2 (Left) (Mow)))"));
    generation->addIndividual(scenario->createIndividual("(Mow)"));

    scenario->setInitialGeneration(generation);
    generationWindow->setGeneration(generation);

    QMdiSubWindow *generationMDI = workspace->addSubWindow(generationWindow, Qt::WindowTitleHint);
    generationMDI->resize(200, 550);
    generationMDI->show();

    addStep(new LessonStep("Introduction", "<p>Producing individuals at random until a perfect solution is found would take a very long time, especially for more complex problems. Instead of performing a <span class='keyword'>blind search</span> like this, we need to <span class='important'>direct</span> the search to find solutions. We can do this by taking individuals from the <span class='thing'>current population</span> with high fitnesses and adapting them.</p><p><span class='keyword'>Genetic programming operators</span> are used to create new individuals based on current ones, with the intention of producing better solutions - although this is not always the case.</p>", this, workspace));
    addStep(new Step2("Mutation", "<p><span class='keyword'>Mutation</span> is a genetic programming operator that is performed on <span class='important'>one</span> individual.</p><p><span class='keyword'>Mutation</span> works by <span class='important'>randomly</span> changing the <span class='thing'>program tree</span> of individuals. Mutation is useful to prevent <span class='keyword'>stagnation</span> in the population, where all individuals become very similar, by reintroducing variety.</p><p>In order to perform mutation, we need to <span class='keyword'>select</span> an individual from the population using a selection method. For this example we will use <span class='keyword'>roulette selection</span>.</p>", this, workspace));
    addStep(new Step3("Mutation", "<p>A <span class='important'>single</span> node on the program tree is <span class='important'>randomly</span> <span class='keyword'>selected</span>, called the <span class='keyword'>mutation point</span>.</p><p>In <span class='keyword'>point mutation</span>, the mutation point is replaced by a random new node.</p><p>In <span class='keyword'>subtree mutation</span>, the mutation point is replaced by a newly generated random subtree.</p><p>The <span class='thing'>mutation window</span> shows <span class='keyword'>point mutation</span> being performed on the <span class='thing'>selected individual</span>.</p>", this, workspace));
    addStep(new Step4("Crossover", "<p><span class='keyword'>Crossover</span> is a genetic programming operator that is performed on <span class='important'>two</span> individuals.</p><p>We will use <span class='keyword'>roulette selection</span> again to select two individuals.</p>", this, workspace));
    addStep(new Step5("Crossover", "<p><span class='keyword'>Crossover</span> is performed by <span class='important'>swapping subtrees</span> between two trees. A <span class='important'>random</span> point in each tree is selected to perform the swap, called the <span class='keyword'>crossover point</span>.</p><p>The <span class='thing'>crossover window</span> shows the two <span class='thing'>selected individuals</span> as the parents, and the result of the <span class='keyword'>crossover</span> as the children.</p><p>The <span style='background-color:#F00'>red</span> nodes show the subtrees selected to be swapped. The <span style='background-color:#F00'>red</span> lines show how the subtrees have been swapped to produce the two new individuals.</p>", this, workspace));
    addStep(new LessonStep("Reproduction", "<p>Finally, the simplest genetic programming operator is called <span class='keyword'>reproduction</span>. This is where the selected individual is <span class='important'>copied</span>, without making any changes to it. This operation is useful for allowing good solutions to <span class='keyword'>survive</span> for longer, so that future solutions may be based on them.</p>", this, workspace));

    stepWindow = workspace->addSubWindow(new StepWindow(this, workspace), Qt::WindowTitleHint);
    stepWindow->resize(500, 250);
    stepWindow->move(workspace->width() / 2 - stepWindow->frameGeometry().width() / 2,
                     workspace->height() - stepWindow->frameGeometry().height());
    stepWindow->show();
}

void OperatorsLesson::unload()
{
    Lesson::unload();

    safeDelete(scenario);
    stepWindow = NULL;
    generationWindow = NULL;
    rouletteWindow1 = NULL;
    rouletteWindow2 = NULL;
    // Don't need to delete the 3 individuals as generation deletes them
    individual1 = NULL;
    individual2 = NULL;
    individual3 = NULL;
}

void OperatorsLesson::Step2::load()
{
    OperatorsLesson *lesson = (OperatorsLesson *) this->lesson;

    RouletteWindow *roulWindow = new RouletteWindow(workspace, lesson->individual1, lesson->scenario->getCurrentGeneration(), lesson->generationWindow);
    QMdiSubWindow *rouletteWindow = workspace->addSubWindow(roulWindow, Qt::WindowTitleHint);
    rouletteWindow->resize(200,250);
    rouletteWindow->move(lesson->generationWindow->parentWidget()->pos().x() + rouletteWindow->frameGeometry().width(), 0);
    rouletteWindow->show();
    lesson->rouletteWindow1 = rouletteWindow;
}

OperatorsLesson::Step3::Step3(QString title, QString description, Lesson *lesson, QMdiArea *workspace) :
    LessonStep(title, description, lesson, workspace)
{
    mutationMDI = NULL;
}

void OperatorsLesson::Step3::load()
{
    Node *p = ((OperatorsLesson *) lesson)->individual1->getRootNode()->clone();
    Node *c = ((OperatorsLesson *) lesson)->scenario->createIndividual("(Prog2 (Left) (Left))")->getRootNode();

    MutationWindow *mutationWindow = new MutationWindow(workspace);
    mutationWindow->setTrees(p, c, 1);
    mutationMDI = workspace->addSubWindow(mutationWindow, Qt::WindowTitleHint);
    //mutationMDI->resize(325,345);
    mutationMDI->move(workspace->width() / 2 - mutationMDI->frameGeometry().width() / 2, 0);
    mutationMDI->show();
}

void OperatorsLesson::Step3::next()
{
    ((OperatorsLesson *) lesson)->rouletteWindow1->close();
    mutationMDI->close();
}

void OperatorsLesson::Step4::load()
{
    OperatorsLesson *lesson = (OperatorsLesson *) this->lesson;

    RouletteWindow *roulWindow1 = new RouletteWindow(workspace, lesson->individual2, lesson->scenario->getCurrentGeneration(), lesson->generationWindow);
    QMdiSubWindow *rouletteWindow1 = workspace->addSubWindow(roulWindow1, Qt::WindowTitleHint);
    rouletteWindow1->resize(200,250);
    rouletteWindow1->move(lesson->generationWindow->parentWidget()->pos().x() + rouletteWindow1->frameGeometry().width(), 0);
    rouletteWindow1->show();
    lesson->rouletteWindow1 = rouletteWindow1;

    RouletteWindow *roulWindow2 = new RouletteWindow(workspace, lesson->individual3, lesson->scenario->getCurrentGeneration(), lesson->generationWindow);
    QMdiSubWindow *rouletteWindow2 = workspace->addSubWindow(roulWindow2, Qt::WindowTitleHint);
    rouletteWindow2->resize(200,250);
    rouletteWindow2->move(rouletteWindow1->pos().x(),
                          rouletteWindow1->pos().y() + rouletteWindow2->frameGeometry().height());
    rouletteWindow2->show();
    lesson->rouletteWindow2 = rouletteWindow2;
}

OperatorsLesson::Step5::Step5(QString title, QString description, Lesson *lesson, QMdiArea *workspace) :
    LessonStep(title, description, lesson, workspace)
{
    crossoverMDI = NULL;
}

void OperatorsLesson::Step5::load()
{
    Node *p1 = ((OperatorsLesson *) lesson)->individual2->getRootNode()->clone();
    Node *p2 = ((OperatorsLesson *) lesson)->individual3->getRootNode()->clone();
    Node *c1 = p1->clone();
    Node *c2 = p2->clone();

    CrossoverResult r;
    r.point1 = 2;
    r.point2 = 1;

    CrossoverWindow *crossoverWindow = new CrossoverWindow(workspace);
    crossoverWindow->setTrees(p1, p2, c1, c2, r);
    crossoverMDI = workspace->addSubWindow(crossoverWindow, Qt::WindowTitleHint);
    //crossoverMDI->resize(625,375);
    //crossoverMDI->move(workspace->width() - crossoverMDI->frameGeometry().width(), 0);
    crossoverMDI->show();
}

void OperatorsLesson::Step5::next()
{
    ((OperatorsLesson *) lesson)->rouletteWindow1->close();
    ((OperatorsLesson *) lesson)->rouletteWindow2->close();
    crossoverMDI->close();
}
