#ifndef TREEVIEWWIDGET_H
#define TREEVIEWWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include "../gp/Individual.h"
#include "../DrawNode.h"
#include "../DrawTreeBuilder.h"

/**
 * Widget for drawing a tree.
 * @see DrawNode
 * @author David Bennett
 */
class TreeViewWidget : public QGLWidget
{
    Q_OBJECT

public:
    /**
     * Constructs the widget.
     * @param parent The parent of the widget.
     */
    TreeViewWidget(QWidget *parent = 0);

    /** Destructs the widget. */
    ~TreeViewWidget();

    /**
     * Sets the individual to view the tree for.
     * Takes ownership of the {@link Individual}, so pass in a clone if you don't want it
     * to be deleted.
     * @param individual
     */
    void setIndividual(Individual *individual);
    
protected:
    /** Clears the screen to grey. */
    void initializeGL();

    /** Draws the tree. */
    void paintGL();

    /** Called when the widget is resized. */
    void resizeGL(int width, int height);

    /** Starts dragging when left mouse button is down. */
    void mousePressEvent(QMouseEvent *event);

    /** End dragging when left mouse button is released. */
    void mouseReleaseEvent(QMouseEvent *event);

    /** Pans the tree when left mouse button is down and mouse is moved. */
    void mouseMoveEvent(QMouseEvent *event);

    /** Zoom in on scroll up and out on scroll down. */
    void wheelEvent(QWheelEvent *event);

    /** Fits the tree to the widget. */
    void mouseDoubleClickEvent(QMouseEvent *event);

    /**
     * Recursively draw the lines connecting nodes.
     * @param node The root node to start drawing from.
     * @param depth The current depth in the tree.
     */
    void drawLine(DrawNode *node, int depth);

    /**
     * Recursively draw the node shapes.
     * @param node The root node to start drawing from.
     * @param depth The current depth in the tree.
     */
    void drawNode(DrawNode *node, int depth);

    /**
     * Recursively draw the text node labels.
     * @param node The root node to start drawing from.
     * @param depth The current depth in the tree.
     */
    void drawLabel(DrawNode *node, int depth);

    /**
     * Find the amount of zoom needed to fit the tree view in the given
     * width and height.
     * @param width Width to fit to.
     * @param height Height to fit to.
     * @return Amount of zoom needed.
     */
    float findIdealZoom(int width, int height);

private:
    Individual *individual; /**< Copy of the {@link Individual} to draw the tree for. */
    DrawNode *tree; /**< The draw tree for the {@link Individual}. */
    int offsetX; /**< The x offset of the tree from panning. */
    int offsetY; /**< The y offset of the tree from panning. */
    int lastX; /**< The last x position of the mouse. */
    int lastY; /**< The last y position of the mouse. */
    float zoom; /**< Amount of zoom for the tree. */
    QFont *nodeFont; /**< The font to use for drawning node labels. */
    DrawTreeBuilder *drawTreeBuilder; /** Draw tree builder for building the draw tree. */

    float LINE_THICKNESS; /**< Thickness of the lines connecting nodes. */
    float NODE_WIDTH; /**< The width of each node. */
    float NODE_HEIGHT; /**< The height of each node. */
    float LABEL_SIZE; /**< The size of each node text label. */
    float ZOOM_MIN; /**< Minimum amount of zoom. */
    float ZOOM_MAX; /**< Maximum amount of zoom. */
    int MAX_HEIGHT; /**< Maximum height of the tree on initialisation. */
    int MAX_WIDTH; /**< Maximum width of the tree on initialisation. */
};

#endif // TREEVIEWWIDGET_H

