#ifndef ANTLESSON_H
#define ANTLESSON_H

#include <QObject>
#include "Lesson.h"
#include "LessonStep.h"
#include "../gp/Generation.h"
#include "../scenarios/ant/AntScenario.h"
#include "../windows/GenerationWindow.h"
#include "../windows/GPRunWindow.h"
#include "../windows/GraphWindow.h"

/**
 * Introduces the artifical ant problem.
 * @author David Bennett
 */
class AntLesson : public QObject, public Lesson
{
    Q_OBJECT

public:
    /**
     * Constructs the lesson.
     * @param workspace Workspace for the lesson.
     */
    AntLesson(QMdiArea *workspace);

    /** Loads the lesson. */
    void load();

    /** Unloads the lesson. */
    void unload();

private slots:
    /** Updates the GUI when a run has finished. */
    void runFinished();

    /**
     * Updates the GUI when a generation has finished.
     * @param generation Copy of the finished generation.
     * @param number Number of the finished generation in the scenario.
     */
    void generationComplete(QSharedPointer<Generation> generation, int number);

    /** Called when a new run is started. */
    void newRun();

private:
    QMdiSubWindow *stepWindow; /**< Lesson step window. */
    GenerationWindow *generationWindow; /**< Generation window. */
    GPRunWindow *runWindow; /**< GP run window. */
    GraphWindow *graphWindow; /**< Graph window. */
    AntScenario *scenario; /**< The scenario being used. */

    class FinalStep : public LessonStep
    {
    public:
        FinalStep(QString title, QString description, Lesson *lesson, QMdiArea *workspace) :
            LessonStep(title, description, lesson, workspace) { }

        void load();
    };
};

#endif // ANTLESSON_H
