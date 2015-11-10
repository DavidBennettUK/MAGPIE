#ifndef CROSSOVERWINDOW_H
#define CROSSOVERWINDOW_H

#include <QMainWindow>
#include "../widgets/CrossoverWidget.h"
#include "../gp/Node.h"
#include "../gp/Crossover.h"

/**
 * Shows an animation of crossover.
 * @author David Bennett
 */
class CrossoverWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * Constructs the window.
     * @param parent Parent for this window.
     */
    explicit CrossoverWindow(QWidget *parent = 0);

    /** Destructs the window, deleting all trees. */
    ~CrossoverWindow();

    /**
     * Set the trees to be displayed and set the animation.
     * The window will take ownership of the trees, deleting them when the window
     * is destroyed.
     * @param parent1 The left parent.
     * @param parent2 The right parent.
     * @param child1 The left child.
     * @param child2 The right child.
     * @param crossoverResult Result of the crossover operation.
     */
    void setTrees(Node *parent1, Node *parent2, Node *child1, Node *child2, CrossoverResult crossoverResult);

signals:
    /** Emitted when the animation has finished. */
    void finished();

private slots:
    /** Resets the animation from the start. */
    void reset();

private:
    Node *parent1; /*< The left parent. */
    Node *parent2; /*< The right parent. */
    Node *child1; /*< The left child. */
    Node *child2; /*< The right child. */
    CrossoverResult crossoverResult; /*< The result of the crossover operation. */
    CrossoverWidget *glCrossover; /*< GL widget showing the crossover animation. */
};

#endif // CROSSOVERWINDOW_H
