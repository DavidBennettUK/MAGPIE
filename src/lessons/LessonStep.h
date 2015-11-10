#ifndef LESSONSTEP_H
#define LESSONSTEP_H

#include <QObject>
#include <QMdiArea>
#include "../common.h"
#include "Lesson.h"

class Lesson;

/**
 * Represents one step of a lesson.
 * @author David Bennett
 */
class LessonStep : public QObject
{
    Q_OBJECT

public:
    /**
     * Constructs the lesson step.
     * @param title The title of the step.
     * @param description The step text.
     * @param lesson The lesson the step belongs to.
     * @param workspace The workspace.
     */
    LessonStep(QString title, QString description, Lesson *lesson, QMdiArea *workspace);
    virtual ~LessonStep() { }

    /** Called when the step needs to be loaded. */
    virtual void load() { }

    /** Called when the next step is about to be loaded. */
    virtual void next() { }

    /**
     * @return The title of the lesson step.
     */
    QString getTitle() { return title; }

    /**
     * @return The text of the lesson step.
     */
    QString getDescription() { return description; }

protected:
    QString title; /**< The title of the lesson step. */
    QString description; /**< The text of the lesson step. */
    Lesson *lesson; /**< The lesson this step belongs to. */
    QMdiArea *workspace; /**< The workspace. */
};

#endif // LESSONSTEP_H
