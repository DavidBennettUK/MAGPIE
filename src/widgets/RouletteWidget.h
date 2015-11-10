#ifndef ROULETTEWIDGET_H
#define ROULETTEWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include "../gp/Generation.h"
#include "../gp/Individual.h"

/**
 * A roulette wheel animation.
 * Segments are built from the {@link Individual}s in a {@link Generation}, based
 * on their {@link Fitness}.
 * @author David Bennett
 */
class RouletteWidget : public QGLWidget
{
    Q_OBJECT

public:
    /**
     * Constructs the widget.
     * Only keeps a reference to the {@link Individual}, so do not delete it before
     * the window is closed.
     * @param winner Reference to the winner of the selection.
     * @param generation Reference to the generation the winner was selected from.
     * @param parent The parent of the widget.
     */
    RouletteWidget(Individual *winner, Generation *generation, QWidget *parent = 0);

    /** Destructs the widget. */
    ~RouletteWidget();

    /** Play the animation from the start. */
    void reset();

protected:
    /** Clears the widget. */
    void initializeGL();

    /** Draws the roulette wheel. */
    void paintGL();

    /** Called when the widget is resized. */
    void resizeGL(int width, int height);

signals:
    /** Emitted when the animation has completed. */
    void finished();

protected slots:
    /** Called every frame to update the animation. */
    void updateAnimation();

private:
    Individual *winner; /**< The winner of the selection. */
    Generation *generation; /**< The generation the winner was selected from. */
    QFont *fitnessFont; /**< The font to use for drawing fitness labels. */
    float wheelRadius; /**< The radius of the roulette wheel. */
    float labelRadius; /**< The offset the labels are place from the centre. */
    float wheelRotation; /**< The amount in degrees of rotation the wheel is currently at. */
    float spinSpeed; /**< The current spin speed of the wheel. */
    float spinAcceleration; /**< The speed the wheel decelerates at. */
    float finalRotation; /**< The final rotation to end up at. */
    int numSpins; /**< The number of complete spins to make before ending the animation. */
    QTimer spinTimer; /**< The timer to update the animation every frame. */
};

#endif // ROULETTEWIDGET_H
