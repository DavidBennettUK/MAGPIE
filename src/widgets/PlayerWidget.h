#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QGLWidget>
#include "../gp/Individual.h"

/**
 * Base class for player widgets.
 * @author David Bennett
 */
class PlayerWidget : public QGLWidget
{
    Q_OBJECT

public:
    /**
     * Constructs the widget with an OpenGL context.
     * @param parent The parent widget.
     */
    PlayerWidget(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) { }
    virtual ~PlayerWidget() { }

    /**
     * Set the {@link Individual} to be drawn.
     * @param individual The {@link Individual} to be drawn.
     */
    virtual void setIndividual(Individual *individual) = 0;

    /** Draw the widget. */
    virtual void draw() = 0;
};

#endif // PLAYERWIDGET_H
