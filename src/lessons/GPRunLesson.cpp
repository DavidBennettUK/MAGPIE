#include <QMdiSubWindow>
#include <QEventLoop>
#include "GPRunLesson.h"
#include "../common.h"
#include "../windows/StepWindow.h"
#include "../windows/RouletteWindow.h"
#include "../windows/MutationWindow.h"
#include "../windows/CrossoverWindow.h"

GPRunLesson::GPRunLesson(QMdiArea *workspace) :
    Lesson(workspace)
{
    title = "Putting it all together";
    description = "Perform a GP run for the lawnmower problem using the techniques learned so far.";
    imageRes = ":/resources/lesson5_preview.png";
    stepWindow = NULL;
    generationWindow = NULL;
    newGenerationWindow = NULL;
    scenario = NULL;
}

void GPRunLesson::load()
{
    addStep(new LessonStep("Introduction", "<p>We will now bring together all of the techniques taught so far and perform a simple <span class='keyword'>GP run</span> for the lawnmower problem.</p><p>This time there are two <span class='thing'>generation windows</span> - the <span class='thing'>left</span> shows the <span class='important'>current</span> generation and the <span class='thing'>right</span> shows the <span class='important'>next</span> generation being built. The <span class='thing'>initial population</span> has been <span class='important'>randomly</span> generated.</p>", this, workspace));
    addStep(new LessonStep("Introduction", "<p><span class='keyword'>Individuals</span> will be <span class='keyword'>selected</span> from the <span class='thing'>population</span>, using <span class='keyword'>roulette selection</span>.</p><p>Selected individuals will have <span class='keyword'>GP operators</span> applied to them. These are <span class='keyword'>crossover</span>, <span class='keyword'>mutation</span> and <span class='keyword'>reproduction</span>.</p><p>Newly generated individuals, resulting from GP operators, will be inserted into the new population.</p><p>Pressing <span class='thing'>next</span> will begin the first <span class='keyword'>iteration</span> of the GP run.</p>", this, workspace));
    addStep(new Step2("First Generation", "<p>The initial population is displayed in the left generation window, and the new generation in the right.</p><p>We were not able to generate a <span class='keyword'>perfect individual</span> from just one iteration.</p><p>Press <span class='thing'>next</span> to perform another iteration.</p>", this, workspace));
    addStep(new Step3("Success", "<p>We have generated an individual with a <span class='keyword'>fitness</span> value of <span class='important'>100</span> that can mow <span class='important'>all</span> <span class='thing'>grass tiles</span>, making this <span class='keyword'>GP run</span> a success. In practice it would usually take many more iterations until a perfect individual is found.</p><p>Try to view the solution in the <span class='thing'>player</span>, but notice the lawnmower mows several tiles <span class='important'>more than once</span>. This is because the <span class='keyword'>fitness function</span> does not account for repeated mows, only judging individuals on the number of tiles they mow.</p>", this, workspace));

    stepWindow = workspace->addSubWindow(new StepWindow(this, workspace), Qt::WindowTitleHint);
    stepWindow->resize(500, 250);
    stepWindow->move(workspace->width() / 2 - stepWindow->frameGeometry().width() / 2,
                     workspace->height() - stepWindow->frameGeometry().height());
    stepWindow->show();

    scenario = new LawnmowerScenario(5);

    Generation *generation = new Generation(scenario->getPopulationSize());
    generation->addIndividual(scenario->createIndividual("(Prog2 (Mow) (Left))"));
    generation->addIndividual(scenario->createIndividual("(Left)"));
    generation->addIndividual(scenario->createIndividual("(Prog2 (Prog2 (Left) (Prog2 (Prog2 (Mow) (Left)) (Prog2 (Mow) (Left)))) (Prog2 (Prog2 (Mow) (Prog2 (Mow) (Mow))) (Prog2 (Prog2 (Mow) (Left)) (Prog2 (Mow) (Mow)))))"));
    generation->addIndividual(scenario->createIndividual("(Prog2 (Mow) (Prog2 (Prog2 (Mow) (Left)) (Prog2 (Mow) (Mow))))"));
    generation->addIndividual(scenario->createIndividual("(Prog2 (Prog2 (Mow) (Prog2 (Mow) (Left))) (Left))"));
    scenario->setInitialGeneration(generation);
    QVector<Individual *> population = generation->getPopulation();

    // Generation 1
    individuals << scenario->createIndividual("(Prog2 (Prog2 (Mow) (Prog2 (Prog2 (Mow) (Left)) (Prog2 (Mow) (Left)))) (Prog2 (Prog2 (Mow) (Prog2 (Mow) (Mow))) (Prog2 (Prog2 (Mow) (Left)) (Prog2 (Mow) (Mow)))))");
    generation1 << new NewIndividual(individuals[0], population[2], 3);
    individuals << scenario->createIndividual("(Prog2 (Mow) (Prog2 (Prog2 (Mow) (Left)) (Prog2 (Mow) (Mow))))");
    generation1 << new NewIndividual(individuals[1], population[3]);
    individuals << scenario->createIndividual("(Prog2 (Mow) (Prog2 (Mow) (Prog2 (Mow) (Left)))");
    individuals << scenario->createIndividual("(Prog2 (Left) (Left))");
    generation1 << new NewIndividual(individuals[2], individuals[3], population[0], population[4], 2, 1);
    individuals << scenario->createIndividual("(Prog2 (Prog2 (Mow) (Prog2 (Mow) (Mow))) (Left))");
    generation1 << new NewIndividual(individuals[4], population[4], 6);

    // Generation 2
    individuals << scenario->createIndividual("(Prog2 (Prog2 (Prog2 (Prog2 (Mow) (Left)) (Prog2 (Mow) (Mow))) (Prog2 (Prog2 (Mow) (Left)) (Prog2 (Mow) (Left)))) (Prog2 (Prog2 (Mow) (Prog2 (Mow) (Mow))) (Prog2 (Prog2 (Mow) (Left)) (Prog2 (Mow) (Mow)))))");
    individuals << scenario->createIndividual("(Prog2 (Mow) (Mow))");
    generation2 << new NewIndividual(individuals[5], individuals[6], individuals[0], individuals[1], 3, 2);
    individuals << scenario->createIndividual("(Prog2 (Left) (Prog2 (Mow) (Prog2 (Mow) (Left)))");
    generation2 << new NewIndividual(individuals[7], individuals[2], 1);
    individuals << scenario->createIndividual("(Prog2 (Mow) (Prog2 (Mow) (Prog2 (Mow) (Left)))");
    generation2 << new NewIndividual(individuals[8], individuals[2]);
    individuals << scenario->createIndividual("(Prog2 (Left) (Prog2 (Prog2 (Mow) (Left)) (Prog2 (Mow) (Mow))))");
    generation2 << new NewIndividual(individuals[9], individuals[1], 1);

    generationWindow = new GenerationWindow(workspace);
    generationWindow->setGeneration(scenario->getCurrentGeneration(), 0);
    QMdiSubWindow *genMDI = workspace->addSubWindow(generationWindow, Qt::WindowTitleHint);
    genMDI->resize(200, 400);
    genMDI->show();

    newGenerationWindow = new GenerationWindow(workspace);
    newGenerationWindow->setGenerationNumber(1);
    QMdiSubWindow *newGenMDI = workspace->addSubWindow(newGenerationWindow, Qt::WindowTitleHint);
    newGenMDI->resize(200, 400);
    newGenMDI->move(workspace->width() - newGenMDI->frameGeometry().width(), 0);
    newGenMDI->show();
}

void GPRunLesson::unload()
{
    Lesson::unload();

    safeDelete(scenario);
    stepWindow = NULL;
    generationWindow = NULL;
    newGenerationWindow = NULL;
    individuals.clear();
    generation1.clear();
    generation2.clear();
}

GPRunLesson::NewIndividual::NewIndividual(Individual *individual, Individual *parent)
{
    memset(this, 0, sizeof(NewIndividual));
    operationType = REPRODUCTION;
    individual1 = individual;
    parent1 = parent;
}

GPRunLesson::NewIndividual::NewIndividual(Individual *individual, Individual *parent, int point)
{
    memset(this, 0, sizeof(NewIndividual));
    operationType = MUTATION;
    individual1 = individual;
    parent1 = parent;
    point1 = point;
}

GPRunLesson::NewIndividual::NewIndividual(Individual *individual1, Individual *individual2,  Individual *parent1, Individual *parent2, int point1, int point2)
{
    memset(this, 0, sizeof(NewIndividual));
    operationType = CROSSOVER;
    this->individual1 = individual1;
    this->individual2 = individual2;
    this->parent1 = parent1;
    this->parent2 = parent2;
    this->point1 = point1;
    this->point2 = point2;
}

void GPRunLesson::doRun(QVector<NewIndividual *> generation, int newGenNumber)
{
    generationWindow->closeViewWindows();
    newGenerationWindow->closeViewWindows();

    Generation *newGeneration = new Generation(5);
    newGenerationWindow->setGeneration(newGeneration, newGenNumber);

    foreach (NewIndividual *newIndividual, generation)
    {
        RouletteWindow *rouletteWindow = new RouletteWindow(workspace, newIndividual->parent1, scenario->getCurrentGeneration(), generationWindow);
        QMdiSubWindow *rouletteMDI = workspace->addSubWindow(rouletteWindow, Qt::WindowTitleHint);
        rouletteMDI->resize(200,200);
        rouletteMDI->move(generationWindow->parentWidget()->pos().x() + generationWindow->parentWidget()->frameGeometry().width(), 0);
        rouletteMDI->show();

        QEventLoop q;
        connect(rouletteWindow, SIGNAL(finished()), &q, SLOT(quit()));
        q.exec();

        QMdiSubWindow *rouletteMDI2 = NULL;
        if (newIndividual->operationType == NewIndividual::CROSSOVER)
        {
            RouletteWindow *rouletteWindow2 = new RouletteWindow(workspace, newIndividual->parent2, scenario->getCurrentGeneration(), generationWindow);
            rouletteMDI2 = workspace->addSubWindow(rouletteWindow2, Qt::WindowTitleHint);
            rouletteMDI2->resize(200,200);
            rouletteMDI2->move(rouletteMDI->x(), rouletteMDI->y() + rouletteMDI->frameGeometry().height());
            rouletteMDI2->show();

            QEventLoop q2;
            connect(rouletteWindow2, SIGNAL(finished()), &q2, SLOT(quit()));
            q2.exec();

            CrossoverWindow *crossoverWindow = new CrossoverWindow(workspace);
            CrossoverResult r;
            r.point1 = newIndividual->point1;
            r.point2 = newIndividual->point2;
            crossoverWindow->setTrees(newIndividual->parent1->getRootNode()->clone(),
                                      newIndividual->parent2->getRootNode()->clone(),
                                      newIndividual->individual1->getRootNode()->clone(),
                                      newIndividual->individual2->getRootNode()->clone(), r);
            QMdiSubWindow *crossoverMDI = workspace->addSubWindow(crossoverWindow, Qt::WindowTitleHint);
            //crossoverMDI->resize(625,375);
            crossoverMDI->show();

            QEventLoop q3;
            connect(crossoverWindow, SIGNAL(finished()), &q3, SLOT(quit()));
            q3.exec();

            newGeneration->addIndividual(newIndividual->individual1);
            newGeneration->addIndividual(newIndividual->individual2);
            crossoverMDI->close();
            rouletteMDI->close();
            rouletteMDI2->close();
        }
        else if (newIndividual->operationType == NewIndividual::MUTATION)
        {
            MutationWindow *mutationWindow = new MutationWindow(workspace);
            mutationWindow->setTrees(newIndividual->parent1->getRootNode()->clone(),
                                     newIndividual->individual1->getRootNode()->clone(),
                                     newIndividual->point1);
            QMdiSubWindow *mutationMDI = workspace->addSubWindow(mutationWindow, Qt::WindowTitleHint);
            //mutationMDI->resize(325,345);
            mutationMDI->show();

            QEventLoop q4;
            connect(mutationWindow, SIGNAL(finished()), &q4, SLOT(quit()));
            q4.exec();

            newGeneration->addIndividual(newIndividual->individual1);
            mutationMDI->close();
            rouletteMDI->close();
        }
        else
        {
            newGeneration->addIndividual(newIndividual->individual1);
            rouletteMDI->close();
        }

        newGenerationWindow->setGeneration(newGeneration, newGenNumber);
    }
}

void GPRunLesson::Step2::load()
{
    GPRunLesson *theLesson = ((GPRunLesson *) lesson);
    theLesson->stepWindow->hide();
    theLesson->doRun(theLesson->generation1, 1);
    theLesson->stepWindow->show();
}

void GPRunLesson::Step3::load()
{
    GPRunLesson *theLesson = ((GPRunLesson *) lesson);
    Generation *currentGeneration = theLesson->newGenerationWindow->getGeneration();
    theLesson->generationWindow->setGeneration(currentGeneration, 1);
    theLesson->scenario->setInitialGeneration(currentGeneration);
    theLesson->stepWindow->hide();
    theLesson->doRun(theLesson->generation2, 2);
    theLesson->stepWindow->show();
}
