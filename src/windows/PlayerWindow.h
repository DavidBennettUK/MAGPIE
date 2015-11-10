#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include "../gp/Individual.h"
#include "../widgets/PlayerWidget.h"

/**
 * Shows an animation for different problem solutions.
 * The animation shown depends on the problem.
 * @author David Bennett
 */
class PlayerWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    /**
     * Constructs the window.
     * @param parent Parent for this window.
     */
    explicit PlayerWindow(Individual *individual, QWidget *parent = 0, int id = -1, int generation = -1);

    /** Deletes the individual. */
    ~PlayerWindow();

    /**
     * Set the individual to play.
     * The window will take ownership of the individual.
     * @param individual The individual to display.
     * @param id The id of the individual.
     * @param generation The generation number the individual belongs to.
     */
    void setIndividual(Individual *individual, int id = -1, int generation = -1);
    
private:
    QTimer playTimer; /**< Timer for the animation. */
    Individual *individual; /**< Individual to display. */

    PlayerWidget *glPlayer; /**< The player widget displaying the animation. */
    QPushButton *btnPlay; /**< Play button. */
    QPushButton *btnStep; /**< Step button. */
    QPushButton *btnReset; /**< Reset button. */

private slots:
    /** Called when the step button is pressed. */
    void stepButton();
    /** Called when the play button is pressed. */
    void play();
    /** Called when the reset button is pressed. */
    void reset();

    /** Start the animation. */
    void start();
    /** Stop the animation. */
    void stop();
    /** Step through the animation. */
    void step();
};

#endif // PLAYERWINDOW_H
