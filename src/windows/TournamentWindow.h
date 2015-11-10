#ifndef TOURNAMENTWINDOW_H
#define TOURNAMENTWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTimer>
#include <QLabel>
#include <QMdiArea>
#include "../gp/Individual.h"
#include "../windows/GenerationWindow.h"

/**
 * Shows an animation representing tournament selection.
 * @author David Bennett
 */
class TournamentWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * Constructs the window.
     * @param workspace Parent of the window.
     * @param winner Winner of the selection.
     * @param contestants The tournament contestants.
     * @param generationWindow Pointer to the generation window.
     */
    explicit TournamentWindow(QMdiArea *workspace, Individual *winner, QVector<Individual *> contestants, GenerationWindow *generationWindow);

    /** Destroy the window. */
    ~TournamentWindow();

protected slots:
    /** Called every tick of the timer. */
    void tick();
    /** Restart the animation. */
    void replay();
    /** Select the winner of the selection in the generation window. */
    void showWinner();

private:
    QMdiArea *workspace; /**< The workspace of the window. */
    GenerationWindow *generationWindow; /**< A pointer to the generation window. */
    Individual *winner; /**< Pointer to the winner. */
    QVector<Individual *> contestants; /**< Pointers to the tournament contestants. */
    QVector<QLabel *> contestantLabels; /**< Labels of the contestants. */
    QTimer *timer; /**< Animation timer. */
    int comparing; /**< The index of the individual currently being compared. */
    int highest; /**< The index of the individual with the highest fitness so far. */
};

#endif // TOURNAMENTWINDOW_H
