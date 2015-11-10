#ifndef TREELESSON_H
#define TREELESSON_H

#include "Lesson.h"
#include "LessonStep.h"
#include "../scenarios/lawnmower/Lawnmower.h"

/**
 * Introduces program tree representation.
 * @author David Bennett
 */
class TreeLesson : public Lesson
{
public:
    /**
     * Constructs the lesson.
     * @param workspace Workspace for the lesson.
     */
    TreeLesson(QMdiArea *workspace);

    /** Loads the lesson. */
    void load();

    /** Unloads the lesson. */
    void unload();

private:
    Lawnmower *individual; /**< Individual to show the tree of. */
    QMdiSubWindow *stepWindow; /**< Lesson step window. */
    QMdiSubWindow *treeWindow; /**< Tree window. */
    QMdiSubWindow *playerWindow; /**< Player window. */

    class Step1 : public LessonStep
    {
    public:
        Step1(QString title, QString description, Lesson *lesson, QMdiArea *workspace) :
            LessonStep(title, description, lesson, workspace) { }

        void load();
    };

    class Step5 : public LessonStep
    {
    public:
        Step5(QString title, QString description, Lesson *lesson, QMdiArea *workspace) :
            LessonStep(title, description, lesson, workspace) { }

        void load();
    };
};

#endif // TREELESSON_H
