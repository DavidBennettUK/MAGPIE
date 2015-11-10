#ifndef WORKSPACEWINDOW_H
#define WORKSPACEWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMdiArea>
#include <QVector>
#include <QSplashScreen>
#include "../lessons/Lesson.h"

/**
 * The main workspace area.
 * The parent of all windows in the application.
 * @author David Bennett
 */
class WorkspaceWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    /**
     * Constructs the window.
     * @param parent Parent for this window.
     */
    explicit WorkspaceWindow(QWidget *parent = 0);

    /** Destroys the window and all lessons. */
    ~WorkspaceWindow();

public slots:
    /** Open the lesson selection window. */
    void lessonSelect();

private slots:
    /** Show the about screen. */
    void showAboutScreen();

private:
    QVector<Lesson *> lessons; /**< Lits of lesson objects. */
    QMdiArea *workspace; /**< The workspace for the window. */
    QAction *lessonSelectAction; /**< Lesson selection action for the menu bar. */
    QAction *quitAction; /**< Quit action fro the menu bar. */
    QAction *aboutAction; /**< About action for the menu bar. */
    QSplashScreen *splash; /**< The splash screen. */
};

#endif // WORKSPACEWINDOW_H
