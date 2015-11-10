#ifndef ANTVIEWWIDGET_H
#define ANTVIEWWIDGET_H

#include "PlayerWidget.h"
#include "../scenarios/ant/Ant.h"

/**
 * View for the artifical ant problem.
 * @author David Bennett
 */
class AntViewWidget : public PlayerWidget
{
    Q_OBJECT

public:
    /**
     * Constructs the widget.
     * @param parent The parent widget.
     */
    AntViewWidget(QWidget *parent = 0);

    /** Destructs the widget. */
    ~AntViewWidget();

    /**
     * Set the {@link Ant} to draw.
     * This class only holds a reference to the {@link Ant}, so do not delete it
     * before the window is closed.
     * @param individual The {@link Ant} the draw.
     */
    void setIndividual(Individual *individual);

    /** Draws the the widget. */
    void draw();

protected:
    /** Draws the stats text. */
    virtual void drawText();

    /** Draws the pellets. */
    virtual void drawPellets();

    /** Draws the ant. */
    void drawAnt();

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
    Ant *ant; /**< Reference to the {@link Ant} to draw. */
    QFont *statsFont; /**< The font to draw the stats with. */
};

#endif // ANTVIEWWIDGET_H
