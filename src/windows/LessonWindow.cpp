#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QList>
#include <QMessageBox>
#include "../common.h"
#include "../lessons/IntroductionLesson.h"

#include "LessonWindow.h"

LessonWindow::LessonWindow(QVector<Lesson *> lessons, QMdiArea *workspace) :
    QMainWindow(workspace)
{
    this->workspace = workspace;
    this->lessons = lessons;

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    this->setWindowTitle("Lessons");

    QHBoxLayout *horizontalContainer = new QHBoxLayout(central);

    tblLessons = new QTableWidget(central);
    tblLessons->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    tblLessons->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tblLessons->setSelectionMode(QAbstractItemView::SingleSelection);
    tblLessons->setSelectionBehavior(QAbstractItemView::SelectRows);
    tblLessons->setSortingEnabled(false);
    tblLessons->horizontalHeader()->setStretchLastSection(true);
    tblLessons->verticalHeader()->setVisible(false);
    tblLessons->horizontalHeader()->setVisible(false);
    tblLessons->setRowCount(lessons.size());
    tblLessons->setColumnCount(1);
    tblLessons->setMinimumSize(200, 300);
    QFont tblFont = tblLessons->font();
    tblFont.setPixelSize(12);
    tblLessons->setFont(tblFont);
    horizontalContainer->addWidget(tblLessons);

    for (int i = 0; i < lessons.size(); i++)
    {
        Lesson *lesson = lessons.at(i);
        tblLessons->setItem(i, 0, new QTableWidgetItem("Lesson " + QString::number(i+1) + ": " + lesson->getTitle()));
    }

    connect(tblLessons, SIGNAL(cellClicked(int,int)), this, SLOT(cellSelected(int,int)));
    connect(tblLessons, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(loadSelectedLesson()));

    QVBoxLayout *verticalContainer = new QVBoxLayout();
    horizontalContainer->addLayout(verticalContainer);

    lblPreviewImage = new QLabel(central);
    lblPreviewImage->setMinimumSize(300, 300);
    lblPreviewImage->setStyleSheet("background-color: #CCC");
    QImage image(":/resources/welcome.png");
    lblPreviewImage->setPixmap(QPixmap::fromImage(image));
    verticalContainer->addWidget(lblPreviewImage);

    lblDescription = new QLabel(central);
    lblDescription->setText("<b>Welcome</b><br/>Please select a lesson.");
    lblDescription->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    lblDescription->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    lblDescription->setWordWrap(true);
    QFont lblFont = lblDescription->font();
    lblFont.setPixelSize(14);
    lblDescription->setFont(lblFont);
    verticalContainer->addWidget(lblDescription);

    QHBoxLayout *buttonContainer = new QHBoxLayout();
    verticalContainer->addLayout(buttonContainer);

    QPushButton *btnGo = new QPushButton("Go", central);
    connect(btnGo, SIGNAL(clicked()), this, SLOT(loadSelectedLesson()));
    buttonContainer->addWidget(btnGo);

    QPushButton *btnQuit = new QPushButton("Quit", central);
    connect(btnQuit, SIGNAL(clicked()), workspace->parentWidget()->parentWidget(), SLOT(close()));
    buttonContainer->addWidget(btnQuit);
}

void LessonWindow::cellSelected(int row, int col)
{
    Q_UNUSED(col);

    Lesson *lesson = lessons.at(row);

    lblDescription->setText("<b>" + lesson->getTitle() + "</b><br/>" + lesson->getDescription());

    QImage image(lesson->getImageRes());
    if (!image.isNull())
        lblPreviewImage->setPixmap(QPixmap::fromImage(image));
}

void LessonWindow::loadSelectedLesson()
{
    QList<QTableWidgetItem *> selected = tblLessons->selectedItems();

    if (selected.empty())
    {
        QMessageBox msgBox;
        msgBox.setText("Please select a lesson.");
        msgBox.exec();
        return;
    }

    Lesson *lesson = lessons.at(selected[0]->row());
    this->parentWidget()->close();
    lesson->load();
    lesson->loadFirstStep();
}
