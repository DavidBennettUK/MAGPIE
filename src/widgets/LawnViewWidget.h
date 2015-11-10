#ifndef LAWNVIEWWIDGET_H
#define LAWNVIEWWIDGET_H

#include "PlayerWidget.h"
#include "../scenarios/lawnmower/Lawnmower.h"

/**
 * View for a lawnmower mowing a lawn.
 * @author David Bennett
 */
class LawnViewWidget : public PlayerWidget
{
    Q_OBJECT

public:
    /**
     * Constructs the widget.
     * @param parent The parent widget.
     */
    LawnViewWidget(QWidget *parent = 0);

    /** Destructs the widget. */
    ~LawnViewWidget();

    /**
     * Set the {@link Lawnmower} to draw.
     * This class only holds a reference to the {@link Lawnmower}, so do not delete it
     * before the window is closed.
     * @param individual The {@link Lawnmower} the draw.
     */
    void setIndividual(Individual *individual);

    /** Draws the the widget. */
    void draw();

protected:
    /** Draws the stats text. */
    virtual void drawText();

    /** Draws the lawn. */
    virtual void drawLawn();

    /** Draws the lawnmower. */
    void drawLawnMower();

    /** Draws the grid. */
    void drawGrid();

private:
    /** Clears the screen. */
    void initializeGL();

    /** Draws the lawn, lawnmower, grid and text stats. */
    void paintGL();

    /** Called when the widget is resized. */
    void resizeGL(int width, int height);

protected:
    Lawnmower *individual; /**< Reference to the {@link Lawnmower} to draw. */
    QFont *statsFont; /**< The font to draw the stats with. */
};

#endif // LAWNVIEWWIDGET_H
