#ifndef MUTATIONWIDGET_H
#define MUTATIONWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include "../gp/Node.h"
#include "../DrawNode.h"
#include "../DrawTreeBuilder.h"

/**
 * Displays a mutation operation graphically.
 * @author David Bennett
 */
class MutationWidget : public QGLWidget
{
    Q_OBJECT

public:
    /**
     * Constructs the widget.
     * @param parent The parent widget.
     */
    explicit MutationWidget(QWidget *parent = 0);

    /** Destructs the widget. */
    ~MutationWidget();
    
    /**
     * Sets the trees to display.
     * @param parent The parent tree.
     * @param child The child tree.
     * @param mutationPoint The point of mutation on the parent, using depth-first numbering.
     */
    void setTrees(Node *parent, Node *child, int mutationPoint);

signals:
    /** Emitted when the animation has finished. */
    void finished();

protected:
    /** Clears the canvas to grey. */
    void initializeGL();

    /** Draws the animation */
    void paintGL();

    /** Called when the widget is resized. */
    void resizeGL(int width, int height);

    /**
     * Recursively draw the tree lines connecting nodes.
     * @param node The root node to start drawing from.
     * @param depth The current depth of the node.
     */
    void drawLine(DrawNode *node, int depth);

    /**
     * Recursively draw the nodes shapes.
     * @param node The root node to start drawing from.
     * @param depth The current depth of the node.
     */
    void drawNode(DrawNode *node, int depth);

    /**
     * Recursively draw the node text labels.
     * @param node The root node to start drawing from.
     * @param depth The current depth of the node.
     */
    void drawLabel(DrawNode *node, int depth);

    /**
     * Calculate the amount of zoom that needs to be applied for the given
     * tree to fit in the maximum width and height.
     * @param tree The tree to calculate zoom for.
     * @return The amount of zoom needed.
     */
    float calculateZoom(DrawNode *tree);

private:
    Node *parent; /**< The parent tree. */
    Node *child; /**< The child tree. */
    Node *mutation; /**< The mutation node. */
    int mutationPoint; /** The mutation point, using depth-first numbering. */
    QFont *nodeFont; /**< The font to use for drawing node labels. */
    DrawTreeBuilder *drawTreeBuilder; /**< The draw tree builder. */
    DrawNode *drawParent; /**< The parent draw tree. */
    DrawNode *drawChild; /**< The child draw tree. */
    QTimer startTimer; /**< Delay until the animation starts. */

    float zoom; /**< The amount of zoom applied to the trees. */

    float LINE_THICKNESS; /**< The thickness of lines connecting each node. */
    float NODE_WIDTH; /**< The width of each node. */
    float NODE_HEIGHT; /**< The height of each node. */
    float LABEL_SIZE; /**< The label size for each node. */
    float MAX_WIDTH; /**< The maximum width for each tree. */
    float MAX_HEIGHT; /**< The maximum height for each tree. */
};

#endif // MUTATIONWIDGET_H
