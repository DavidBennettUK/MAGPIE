#ifndef LESSONWINDOW_H
#define LESSONWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QMdiArea>
#include <QVector>
#include <QLabel>
#include "../lessons/Lesson.h"

/**
 * Displays a list of the available lessons, allowing the user
 * to select and load them.
 * @author David Bennett
 */
class LessonWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * Constructs the window.
     * @param lessons The available lessons.
     * @param workspace Parent for this window.
     */
    explicit LessonWindow(QVector<Lesson *> lessons, QMdiArea *workspace);

protected slots:
    /**
     * Shows a preview image and description for the selected lesson.
     * @param row Row number.
     * @param col Column number, will always be 0 as there is only one row.
     */
    void cellSelected(int row, int col);

    /** Loads the currently selected lesson. */
    void loadSelectedLesson();

private:
    QMdiArea *workspace; /**< Workspace for the window. */
    QLabel *lblDescription; /**< The description for the currently selected lesson. */
    QLabel *lblPreviewImage; /**< Preview image for the currently selecetd lession. */
    QTableWidget *tblLessons; /**< List of available lessons. */
    QVector<Lesson *> lessons; /**< List of lesson objects. */
};

#endif // LESSONWINDOW_H
