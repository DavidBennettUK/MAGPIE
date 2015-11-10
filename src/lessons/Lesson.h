#ifndef LESSON_H
#define LESSON_H

#include <QString>
#include <QVector>
#include <QMdiArea>
#include "LessonStep.h"

class LessonStep;

/**
 * Base class for all lessons.
 * @author David Bennett
 */
class Lesson
{
public:
    /**
     * Constructs the lesson.
     * @param workspace The workspace the lesson takes place in.
     */
    Lesson(QMdiArea *workspace);

    /** Destructs the lesson and all of its steps. */
    virtual ~Lesson();

    /**
     * @return The title of the lesson.
     */
    QString getTitle() { return title; }

    /**
     * @return The description of the lesson.
     */
    QString getDescription() { return description; }

    /**
     * @return The preview image of the lesson.
     */
    QString getImageRes() { return imageRes; }

    /** Called when the lesson needs to be loaded. */
    virtual void load() = 0;

    /** Called when the lesson has ended. */
    virtual void unload();

    /** Load the first step of the lesson. */
    void loadFirstStep();

    /**
     * Append a step to the end of the lesson.
     * @param step The step to add.
     */
    void addStep(LessonStep *step);

    /**
     * Load the next step.
     * @return Pointer to the next lesson step.
     */
    LessonStep *nextStep();

    /**
     * Load the previous step.
     * @return Pointer to the previous lesson step.
     */
    LessonStep *previousStep();

    /**
     * @return The current lesson step.
     */
    LessonStep *getCurrentStep();

    /**
     * @return True if the current lesson step has another step.
     */
    bool hasNextStep() { return currentStep < steps.size() - 1; }

    /**
     * @return True if the current step has a previous step.
     */
    bool hasPreviousStep() { return currentStep > 0; }

protected:
    QMdiArea *workspace; /**< The workspace. */
    QVector<LessonStep *> steps; /**< The steps of the lesson. */
    int currentStep; /**< The index of the current step. */
    int lastStepDone; /**< The index of the last completed step. */
    QString title; /**< The title of the lesson. */
    QString description; /**< The description of the lesson. */
    QString imageRes; /**< The preview image of the lesson. */
};

#endif // LESSON_H
