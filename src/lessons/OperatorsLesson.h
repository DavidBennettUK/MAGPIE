#ifndef OPERATORSLESSON_H
#define OPERATORSLESSON_H

#include <QMdiSubWindow>
#include "Lesson.h"
#include "LessonStep.h"
#include "../windows/GenerationWindow.h"
#include "../gp/Scenario.h"
#include "../gp/RouletteSelection.h"
#include "../gp/Individual.h"
#include "../gp/TreeFactory.h"

/**
 * Introduces genetic programming operators.
 * @author David Bennett
 */
class OperatorsLesson : public Lesson
{
public:
    /**
     * Constructs the lesson.
     * @param workspace Workspace for the lesson.
     */
    OperatorsLesson(QMdiArea *workspace);

    /** Loads the lesson. */
    void load();

    /** Unloads the lesson. */
    void unload();

private:
    Scenario *scenario; /**< Scenario being used. */
    QMdiSubWindow *stepWindow; /**< Lesson step window. */
    GenerationWindow *generationWindow; /**< Generation window. */
    Individual *individual1; /**< Individual used for mutation. */
    Individual *individual2; /**< Individual used for crossover. */
    Individual *individual3; /**< Individual used for crossover. */
    QMdiSubWindow *rouletteWindow1; /** First roulette window. */
    QMdiSubWindow *rouletteWindow2; /** Second roulette window. */

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
        Step3(QString title, QString description, Lesson *lesson, QMdiArea *workspace);

        void load();
        void next();

    private:
        QMdiSubWindow *mutationMDI;
    };

    class Step4 : public LessonStep
    {
    public:
        Step4(QString title, QString description, Lesson *lesson, QMdiArea *workspace) :
            LessonStep(title, description, lesson, workspace) { }

        void load();
    };

    class Step5 : public LessonStep
    {
    public:
        Step5(QString title, QString description, Lesson *lesson, QMdiArea *workspace);

        void load();
        void next();

    private:
        QMdiSubWindow *crossoverMDI;
    };
};

#endif // OPERATORSLESSON_H
