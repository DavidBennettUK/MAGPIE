#ifndef STEPWINDOW_H
#define STEPWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTextBrowser>
#include <QMdiArea>
#include "../lessons/Lesson.h"

/**
 * Allows for navigation through the steps of a lesson.
 * @author David Bennett
 */
class StepWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * Constructs the window.
     * @param lesson The losson to step through.
     * @param workspace Parent for this window.
     */
    explicit StepWindow(Lesson *lesson, QMdiArea *workspace = 0);

    QPushButton *btnNext; /** Next step button. */
    QPushButton *btnBack; /** Previous step button. */

private slots:
    /** Called when the next buton is pressed. */
    void next();
    /** Called when the back button is pressed. */
    void back();
    /** Called when the lesson select button is pressed. */
    void lessonSelect();

private:
    QMdiArea *workspace; /**< The workspace of the window. */
    QLabel *lblDescription; /**< The descriptive text for the current lesson step. */
    QString css; /**< The css to use for the label. */
    Lesson *lesson; /**< The lesson to step through. */
};

#endif // STEPWINDOW_H
