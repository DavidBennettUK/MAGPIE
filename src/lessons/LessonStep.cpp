#include "LessonStep.h"

LessonStep::LessonStep(QString title, QString description, Lesson *lesson, QMdiArea *workspace)
{
    this->title = title;
    this->description = description;
    this->lesson = lesson;
    this->workspace = workspace;
}
