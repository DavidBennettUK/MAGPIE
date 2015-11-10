#ifndef GPRUNLESSON_H
#define GPRUNLESSON_H

#include <QObject>
#include <QVector>
#include "Lesson.h"
#include "LessonStep.h"
#include "../gp/Generation.h"
#include "../scenarios/lawnmower/LawnmowerScenario.h"
#include "../windows/GenerationWindow.h"
#include "../windows/RouletteWindow.h"

/**
 * Teaches how the basic GP components are brought together to perform
 * a GP run.
 * @author David Bennett
 */
class GPRunLesson : public QObject, public Lesson
{
    Q_OBJECT

public:
    /**
     * Constructs the lesson.
     * @param workspace Workspace for the lesson.
     */
    GPRunLesson(QMdiArea *workspace);

    /** Loads the lesson. */
    void load();

    /** Unloads the lesson. */
    void unload();

private:
    QMdiSubWindow *stepWindow; /**< Lesson step window. */
    GenerationWindow *generationWindow; /**< Generation window for the current generation. */
    GenerationWindow *newGenerationWindow; /**< Generation window for the new generation. */
    LawnmowerScenario *scenario; /**< The scenario being used. */
    QVector<Individual *> individuals; /**< Individuals used for the lesson. */

    struct NewIndividual
    {
        enum OperationType {CROSSOVER, MUTATION, REPRODUCTION};

        NewIndividual(Individual *individual, Individual *parent);
        NewIndividual(Individual *individual, Individual *parent, int point);
        NewIndividual(Individual *individual1, Individual *individual2, Individual *parent1, Individual *parent2, int point1, int point2);

        OperationType operationType;
        Individual *individual1, *individual2;
        Individual *parent1, *parent2;
        int point1, point2;
    };
    QVector<NewIndividual *> generation1, generation2;

    void doRun(QVector<NewIndividual *> generation, int newGenNumber);

    class Step2 : public LessonStep
    {
    public:
        Step2(QString title, QString description, Lesson *lesson, QMdiArea *workspace) :
            LessonStep(title, description, lesson, workspace) { }

        void load();
    };

    class Step3 : public LessonStep
    {
    public:
        Step3(QString title, QString description, Lesson *lesson, QMdiArea *workspace) :
            LessonStep(title, description, lesson, workspace) { }

        void load();
    };
};

#endif // GPRUNLESSON_H
