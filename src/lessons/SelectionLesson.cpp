#include <QMdiSubWindow>
#include <QVector>
#include "SelectionLesson.h"
#include "../windows/StepWindow.h"
#include "../windows/RouletteWindow.h"
#include "../windows/TournamentWindow.h"
#include "../gp/RouletteSelection.h"
#include "../gp/TournamentSelection.h"
#include "../gp/Scenario.h"
#include "../gp/Generation.h"
#include "../scenarios/lawnmower/LawnmowerScenario.h"

SelectionLesson::SelectionLesson(QMdiArea *workspace) :
    Lesson(workspace)
{
    title = "Fitness and selection";
    description = "How individuals are selected to perform genetic programming operations on.";
    imageRes = ":/resources/lesson3_preview.png";
    scenario = NULL;
    stepWindow = NULL;
    generationWindow = NULL;
}

void SelectionLesson::load()
{
    // Set a seed so the lesson is the same every time
    qsrand(100);

    scenario = new LawnmowerScenario(10);

    generationWindow = new GenerationWindow(workspace);
    scenario->initialiseRandomPopulation();
    generationWindow->setGeneration(scenario->getCurrentGeneration());
    QMdiSubWindow *generationMDI = workspace->addSubWindow(generationWindow, Qt::WindowTitleHint);
    generationMDI->resize(200, 550);
    generationMDI->show();

    addStep(new LessonStep("Populations", "<p>A <span class='keyword'>population</span> contains a number of <span class='keyword'>individuals</span>. The <span class='important'>initial</span> population is usually filled with <span class='important'>randomly generated</span> individuals, until the maximum <span class='keyword'>population size</span> is reached.</p><p>The <span class='thing'>population window</span> shows all individuals in the <span class='important'>current</span> population. The <span class='thing'>solution player</span> or <span class='thing'>program tree</span> may be viewed for an individual by <span class='thing'>selecting</span> the individual and pressing the corresponding <span class='thing'>button</span>.</p>", this, workspace));
    addStep(new LessonStep("Fitness", "<p><span class='keyword'>Selection</span> is needed to find <span class='important'>promising</span> individuals in the population to apply <span class='keyword'>genetic operations</span> to, with the intention of creating <span class='important'>better</span> solutions.</p><p>In order to <span class='keyword'>compare</span> individuals with one another, a measure of <span class='keyword'>fitness</span> is needed.</p><p>In the lawnmower problem the number of tiles mowed can be used as a measure of fitness. The more <span class='thing'>tiles of grass</span> a lawnmower has mowed, the better the solution.</p>", this, workspace));
    addStep(new Step3("Roulette Selection", "<p>One method of selection is <span class='keyword'>roulette selection</span>.</p><p>Each individual is given a <span class='important'>chance</span> of selection based on its <span class='keyword'>fitness value</span>. The larger the fitness value, the higher the chance of being selected.</p><p>As shown on the <span class='thing'>roulette wheel</span>, individuals with a higher fitness have a larger slice of the wheel.</p><p>The wheel is spun and the individual it lands on is the <span class='keyword'>winner</span>.</p>", this, workspace));
    addStep(new Step4("Tournament Selection", "<p><span class='keyword'>Tournament selection</span> is where several individuals are selected from the population at <span class='important'>random</span>, until the maximum number of <span class='keyword'>contestants</span> has been reached. The contestants are then <span class='keyword'>compared</span> against one another.</p><p>The contestant with the <span class='important'>highest</span> <span class='keyword'>fitness value</span> is the <span class='keyword'>winner</span>.</p><p>In the <span class='thing'>tournament selection window</span> the <span class='keyword'>winner</span> is displayed in <span style='background-color:#0F0'>green</span>, and the losers in <span style='background-color:#F00'>red</span>.</p>", this, workspace));

    stepWindow = workspace->addSubWindow(new StepWindow(this, workspace), Qt::WindowTitleHint);
    stepWindow->resize(500, 250);
    stepWindow->move(workspace->width() / 2 - stepWindow->frameGeometry().width() / 2,
                     workspace->height() - stepWindow->frameGeometry().height());
    stepWindow->show();
}

void SelectionLesson::unload()
{
    Lesson::unload();

    safeDelete(scenario);
    stepWindow = NULL;
    generationWindow = NULL;
}

SelectionLesson::Step3::Step3(QString title, QString description, Lesson *lesson, QMdiArea *workspace) :
    LessonStep(title, description, lesson, workspace)
{
    rouletteWindow = NULL;
}

void SelectionLesson::Step3::load()
{
    GenerationWindow *generationWindow = ((SelectionLesson *) lesson)->generationWindow;
    Generation *generation = ((SelectionLesson *) lesson)->scenario->getCurrentGeneration();
    RouletteSelection selection;
    Individual *winner = selection.selectIndividual(generation);

    RouletteWindow *roulWindow = new RouletteWindow(workspace, winner, generation, generationWindow);
    rouletteWindow = workspace->addSubWindow(roulWindow, Qt::WindowTitleHint);
    rouletteWindow->resize(400,400);
    rouletteWindow->move(workspace->width() / 2 - rouletteWindow->frameGeometry().width() / 2, 0);
    rouletteWindow->show();
}

void SelectionLesson::Step3::next()
{
    rouletteWindow->close();
}

SelectionLesson::Step4::Step4(QString title, QString description, Lesson *lesson, QMdiArea *workspace) :
    LessonStep(title, description, lesson, workspace)
{
    tournamentWindow = NULL;
}

void SelectionLesson::Step4::load()
{
    GenerationWindow *generationWindow = ((SelectionLesson *) lesson)->generationWindow;
    Generation *generation = ((SelectionLesson *) lesson)->scenario->getCurrentGeneration();
    QVector<Individual *> contestants;
    TournamentSelection selection(5);
    Individual *winner = selection.selectIndividual(generation, &contestants);

    TournamentWindow *tournWindow = new TournamentWindow(workspace, winner, contestants, generationWindow);
    tournamentWindow = workspace->addSubWindow(tournWindow, Qt::WindowTitleHint);
    tournamentWindow->move(workspace->width() / 2 - tournamentWindow->frameGeometry().width() / 2, 0);
    tournamentWindow->show();
}

void SelectionLesson::Step4::next()
{
    tournamentWindow->close();
}
