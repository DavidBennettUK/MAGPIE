#ifndef INTRODUCTIONLESSON_H
#define INTRODUCTIONLESSON_H

#include "Lesson.h"
#include "LessonStep.h"
#include "../gp/Individual.h"
#include "../windows/PlayerWindow.h"

/**
 * Introduces the lawnmower problem.
 * @author David Bennett
 */
class IntroductionLesson : public Lesson
{
public:
    /**
     * Constructs the lesson.
     * @param workspace Workspace for the lesson.
     */
    IntroductionLesson(QMdiArea *workspace);

    /** Loads the lesson. */
    void load();

    /** Unloads the lesson. */
    void unload();

private:
    QMdiSubWindow *stepWindow; /**< Lesson step window. */
    PlayerWindow *playerWindow; /**< Lawnmower player window. */

    class Step1 : public LessonStep
    {
    public:
        Step1(QString title, QString description, Lesson *lesson, QMdiArea *workspace) :
            LessonStep(title, description, lesson, workspace) { }

        void load();
    };

    class Step4 : public LessonStep
    {
    public:
        Step4(QString title, QString description, Lesson *lesson, QMdiArea *workspace) :
            LessonStep(title, description, lesson, workspace) { }

        void load();
    };
};

#endif // INTRODUCTIONLESSON_H
