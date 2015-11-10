#ifndef CROSSOVERWIDGET_H
#define CROSSOVERWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QPointF>
#include "../gp/Node.h"
#include "../DrawNode.h"
#include "../DrawTreeBuilder.h"
#include "../gp/Crossover.h"

/**
 * Displays a crossover operation graphically.
 * @author David Bennett
 */
class CrossoverWidget : public QGLWidget
{
    Q_OBJECT

public:
    /**
     * Constructs the widget.
     * @param parent The parent widget.
     */
    CrossoverWidget(QWidget *parent = 0);

    /** Destructs the widget. */
    ~CrossoverWidget();

    /**
     * Set the trees for the widget to display.
     * @param parent1 The first parent.
     * @param parent2 The second parent.
     * @param child1 The first child.
     * @param child2 The second child
     * @param crossoverResult The result of the crossover operation.
     */
    void setTrees(Node *parent1, Node *parent2, Node *child1, Node *child2, CrossoverResult crossoverResult);

signals:
    /** Called when the animation has finished. */
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
     * @param highlight True if the lines should be red, false if black.
     */
    void drawLine(DrawNode *node, int depth, bool highlight = false);

    /**
     * Recursively draw the nodes shapes.
     * @param node The root node to start drawing from.
     * @param depth The current depth of the node.
     * @param highlight True if the node should be highlighted red.
     */
    void drawNode(DrawNode *node, int depth, bool highlight = false);

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

protected slots:
    /** Starts both the crossover animations. */
    void startAnimation();

    /** Starts the top left to bottom right crossover animation. */
    void crossoverAnimation1();

    /** Starts the top right to bottom left crossover animation. */
    void crossoverAnimation2();

private:
    Node *parent1; /**< Reference to the first parent tree. */
    Node *parent2; /**< Reference to the second parent tree. */
    Node *child1; /**< Reference to the first child tree. */
    Node *child2; /**< Reference to the second chid tree. */
    Node *crossover1; /**< The first crossover subtree. */
    Node *crossover2; /**< The second crossover subtree. */
    CrossoverResult crossoverResult; /**< The result of the crossover operation. */

    QFont *nodeFont; /**< The font to use for drawing node labels. */
    DrawTreeBuilder *drawTreeBuilder; /**< The draw tree builder. */
    DrawNode *drawParent1; /**< The first parent draw tree. */
    DrawNode *drawParent2; /**< The second parent draw tree. */
    DrawNode *drawChild1; /**< The first child draw tree. */
    DrawNode *drawChild2; /**< The second child draw tree. */
    DrawNode *drawCrossover1; /**< The first subtree draw tree. */
    DrawNode *drawCrossover2; /**< The second subtree draw tree. */
    QTimer startTimer; /**< Delay until the animation starts. */
    QTimer animationTimer1; /**< Controls the animation of the first subtree. */
    QTimer animationTimer2; /**< Controls the anmiation of the second subtree. */
    QTimer endTimer; /**< Delay until the animation is marked as finished. */
    QPointF startPoint1; /**< The position for the first crossover subtree to start at. */
    QPointF endPoint1; /**< The position for the first crossover subtree to start at. */
    QPointF currentPosition1; /**< The position the first crossover subtree is currently at. */
    QPointF startPoint2; /**< The position for the second crossover subtree to start at. */
    QPointF endPoint2; /**< The position for the second crossover subtree to end at. */
    QPointF currentPosition2; /**< The position the second crossover subtree is currently at. */
    bool showChildren; /**< True if the child trees should be displayed. */

    float zoom; /**< The amount of zoom applied to the trees. */

    float LINE_THICKNESS; /**< The thickness of lines connecting each node. */
    float NODE_WIDTH; /**< The width of each node. */
    float NODE_HEIGHT; /**< The height of each node. */
    float LABEL_SIZE; /**< The label size for each node. */
    float MAX_WIDTH; /**< The maximum width for each tree. */
    float MAX_HEIGHT; /**< The maximum height for each tree. */
    float CROSSOVER_SPEED; /**< The speed the trees will move from starting to finishing positions. */
};

#endif // CROSSOVERWIDGET_H
