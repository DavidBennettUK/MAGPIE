#include <QMdiSubWindow>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QTimer>
#include "WorkspaceWindow.h"
#include "LessonWindow.h"
#include "../common.h"
#include "../lessons/IntroductionLesson.h"
#include "../lessons/TreeLesson.h"
#include "../lessons/SelectionLesson.h"
#include "../lessons/OperatorsLesson.h"
#include "../lessons/GPRunLesson.h"
#include "../lessons/ExperimentLesson.h"
#include "../lessons/MultiObjectiveLesson.h"
#include "../lessons/AntLesson.h"

WorkspaceWindow::WorkspaceWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    this->setWindowTitle("MAGPIE");

    QIcon icon(":/resources/icon_trans.ico");
    setWindowIcon(icon);

    lessonSelectAction = new QAction("Select Lesson", this);
    connect(lessonSelectAction, SIGNAL(triggered()), this, SLOT(lessonSelect()));
    quitAction = new QAction("Quit", this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    QMenu *fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(lessonSelectAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

    aboutAction = new QAction("About", this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAboutScreen()));

    QMenu *helpMenu = menuBar()->addMenu("Help");
    helpMenu->addAction(aboutAction);

    QHBoxLayout *horizontalContainer = new QHBoxLayout(central);

    workspace = new QMdiArea(central);
    workspace->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    workspace->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    horizontalContainer->addWidget(workspace);

    // Hides title bar icons for all sub windows
    QPixmap blankIcon(16,16);
    blankIcon.fill(Qt::transparent);
    workspace->setWindowIcon(QIcon(blankIcon));

    lessons.append(new IntroductionLesson(workspace));
    lessons.append(new TreeLesson(workspace));
    lessons.append(new SelectionLesson(workspace));
    lessons.append(new OperatorsLesson(workspace));
    lessons.append(new GPRunLesson(workspace));
    lessons.append(new ExperimentLesson(workspace));
    lessons.append(new MultiObjectiveLesson(workspace));
    lessons.append(new AntLesson(workspace));
}

WorkspaceWindow::~WorkspaceWindow()
{
    foreach (Lesson *lesson, lessons)
    {
        // TODO only need to call unload on current lesson
        lesson->unload();
        safeDelete(lesson);
    }
    lessons.clear();
}

void WorkspaceWindow::lessonSelect()
{
    // TODO only need to call unload on current lesson
    foreach (Lesson *lesson, lessons)
        lesson->unload();
    workspace->closeAllSubWindows();

    LessonWindow *lessonWindow = new LessonWindow(lessons, workspace);
    QMdiSubWindow *mdi = workspace->addSubWindow(lessonWindow, Qt::WindowTitleHint);
    mdi->resize(809, 530);
    mdi->move(workspace->geometry().width() / 2 - mdi->frameGeometry().width() / 2,
              workspace->geometry().height() / 2 - mdi->frameGeometry().height() / 2);
    mdi->show();
}

void WorkspaceWindow::showAboutScreen()
{
    QPixmap imgSplash(":/resources/splash.png");
    splash = new QSplashScreen(imgSplash);
    splash->show();
}
