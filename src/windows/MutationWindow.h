#ifndef MUTATIONWINDOW_H
#define MUTATIONWINDOW_H

#include <QMainWindow>
#include "../gp/Node.h"
#include "../widgets/MutationWidget.h"

/**
 * Shows a visualisation of mutation.
 * @author David Bennett
 */
class MutationWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * Constructs the window.
     * @param parent Parent for this window.
     */
    explicit MutationWindow(QWidget *parent = 0);

    /** Delete the trees belonging to this window. */
    ~MutationWindow();

    /**
     * Set the trees to display.
     * The window takes ownership of these trees.
     * @param parent The parent tree.
     * @param child The child tree.
     * @param mutationPoint The index of the mutation point using depth-first numbering.
     */
    void setTrees(Node *parent, Node *child, int mutationPoint);
    
signals:
    /** Emitted when the animation has finished. */
    void finished();

private:
    Node *parent; /**< The parent tree. */
    Node *child; /**< The child tree. */
    int mutationPoint; /**< The mutation point. */
    MutationWidget *glMutation; /**< The mutation animation widget. */
};

#endif // MUTATIONWINDOW_H
