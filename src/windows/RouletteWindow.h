#ifndef ROULETTEWINDOW_H
#define ROULETTEWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include "../widgets/RouletteWidget.h"
#include "../gp/Individual.h"
#include "../gp/Generation.h"
#include "../windows/GenerationWindow.h"

/**
 * Shows an animation representing roulette selection.
 * @author David Bennett
 */
class RouletteWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * Constructs the window.
     * @param workspace The workspace for the window.
     * @param winner The winner of the selection.
     * @param generation The generation where the individual was selected from.
     * @param generationWindow Pointer to the generation window.
     */
    explicit RouletteWindow(QMdiArea *workspace, Individual *winner, Generation *generation, GenerationWindow *generationWindow);

signals:
    /** Emitted when the animation has finished. */
    void finished();

private slots:
    /** Selects the winning individual in the generation window. */
    void showWinner();

    /** Replay the animation .*/
    void replay();

private:
    Generation *generation; /**< Pointer to the generation. */
    Individual *winner; /**< Pointer to the window. */

    QMdiArea *workspace; /**< The workspace for the window. */
    RouletteWidget *glRoulette; /**< The widget showing the roulette animation. */
    GenerationWindow *generationWindow; /**< Pointer to the generation window. */
};

#endif // ROULETTEWINDOW_H
