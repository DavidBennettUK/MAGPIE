#include "Lesson.h"
#include "../common.h"

using std::min;
using std::max;

Lesson::Lesson(QMdiArea *workspace)
{
    this->title = "Unknown";
    this->description = "No description";
    this->workspace = workspace;
    currentStep = 0;
    lastStepDone = -1;
}

Lesson::~Lesson()
{
    unload();
}

void Lesson::unload()
{
    foreach (LessonStep *step, steps)
        safeDelete(step);
    steps.clear();

    currentStep = 0;
    lastStepDone = -1;
}

void Lesson::loadFirstStep()
{
    steps[0]->load();
}

void Lesson::addStep(LessonStep *step)
{
    steps << step;
}

LessonStep *Lesson::nextStep()
{
    Q_ASSERT(steps.size() > 0);

    if (lastStepDone < steps.count() - 1)
    {
        if (currentStep > lastStepDone)
        {
            steps[currentStep]->next();
            lastStepDone = currentStep;
            steps[currentStep + 1]->load();
        }

        currentStep++;

        if (currentStep == steps.count() - 1)
            lastStepDone = currentStep;
    }
    else
    {
        if (hasNextStep())
            currentStep++;
    }

   return steps[currentStep];
}

LessonStep *Lesson::previousStep()
{
    Q_ASSERT(currentStep >= 0 && steps.size() > 0);

    if (currentStep < 0)
        return NULL;

    currentStep = max(currentStep - 1, 0);

    return steps[currentStep];
}

LessonStep *Lesson::getCurrentStep()
{
    Q_ASSERT(currentStep >= 0 && steps.size() > 0);

    return steps[currentStep];
}
