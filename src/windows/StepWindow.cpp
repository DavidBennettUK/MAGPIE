#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "StepWindow.h"
#include "WorkspaceWindow.h"

using std::max;

StepWindow::StepWindow(Lesson *lesson, QMdiArea *workspace) :
    QMainWindow(workspace)
{
    this->workspace = workspace;
    this->lesson = lesson;

    this->setWindowTitle(lesson->getCurrentStep()->getTitle());

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout *verticalContainer = new QVBoxLayout(central);

    css = "<style>"
          "h4 { margin:0 }"
          "p { margin:0 0 7px 0; padding:0 } "
          "ul, li { margin:0; padding:0; margin-bottom:5px } "
          "li { margin-left:-1em }"
          ".keyword { color:blue; font-weight:bold }"
          ".thing { color:green; font-weight:bold }"
          ".important { color:red; font-weight:bold }"
          "</style>";

    lblDescription = new QLabel(central);
    lblDescription->setText(css + lesson->getCurrentStep()->getDescription());
    lblDescription->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    lblDescription->setWordWrap(true);
    QFont font = lblDescription->font();
    font.setPixelSize(14);
    lblDescription->setFont(font);
    verticalContainer->addWidget(lblDescription);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    verticalContainer->addLayout(buttonLayout);

    btnBack = new QPushButton("Back", central);
    btnBack->setEnabled(false);
    buttonLayout->addWidget(btnBack);
    connect(btnBack, SIGNAL(clicked()), this, SLOT(back()));

    QPushButton *btnLessonSelect = new QPushButton("Select Lesson");
    buttonLayout->addWidget(btnLessonSelect);
    connect(btnLessonSelect, SIGNAL(clicked()), this, SLOT(lessonSelect()));

    btnNext = new QPushButton("Next", central);
    btnNext->setEnabled(lesson->hasNextStep());
    buttonLayout->addWidget(btnNext);
    connect(btnNext, SIGNAL(clicked()), this, SLOT(next()));
}

void StepWindow::next()
{
    LessonStep *step = lesson->nextStep();

    this->setWindowTitle(step->getTitle());
    lblDescription->setText(css + step->getDescription());

    btnNext->setEnabled(lesson->hasNextStep());
    btnBack->setEnabled(lesson->hasPreviousStep());
}

void StepWindow::back()
{
    LessonStep *step = lesson->previousStep();

    this->setWindowTitle(step->getTitle());
    lblDescription->setText(css + step->getDescription());

    btnNext->setEnabled(lesson->hasNextStep());
    btnBack->setEnabled(lesson->hasPreviousStep());
}

void StepWindow::lessonSelect()
{
    WorkspaceWindow *workspaceWindow = (WorkspaceWindow *) workspace->parentWidget()->parentWidget();;
    workspaceWindow->lessonSelect();
}
