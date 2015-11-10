#ifndef SELECTIONLESSON_H
#define SELECTIONLESSON_H

#include "Lesson.h"
#include "LessonStep.h"
#include "../gp/Scenario.h"
#include "../windows/GenerationWindow.h"

/**
 * Introduces selection methods.
 * @author David Bennett
 */
class SelectionLesson : public Lesson
{
public:
    /**
     * Constructs the lesson.
     * @param workspace Workspace for the lesson.
     */
    SelectionLesson(QMdiArea *workspace);

    /** Loads the lesson. */
    void load();

    /** Unloads the lesson. */
    void unload();

private:
    Scenario *scenario; /**< Scenario used for the lesson. */
    QMdiSubWindow *stepWindow; /**< Lesson step window. */
    GenerationWindow *generationWindow; /**< Generation window. */

    class Step3 : public LessonStep
    {
    public:
        Step3(QString title, QString description, Lesson *lesson, QMdiArea *workspace);

        void load();
        void next();

    private:
        QMdiSubWindow *rouletteWindow;
    };

    class Step4 : public LessonStep
    {
    public:
        Step4(QString title, QString description, Lesson *lesson, QMdiArea *workspace);

        void load();
        void next();

    private:
        QMdiSubWindow *tournamentWindow;
    };
};

#endif // SELECTIONLESSON_H
