#ifndef TREEWINDOW_H
#define TREEWINDOW_H

#include <QMainWindow>
#include "../gp/Individual.h"
#include "../widgets/TreeViewWidget.h"

/**
 * Shows a program tree for an individual.
 * @author David Bennett
 */
class TreeWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    /**
     * Constructs the window.
     * The window takes ownership of the individual.
     * @param individual The individual to show.
     * @param parent The parent window.
     * @param id Id of the individual.
     * @param generation Generation number the individual is from.
     */
    explicit TreeWindow(Individual *individual, QWidget *parent = 0, int id = -1, int generation = -1);

    /** Detroys the window. */
    ~TreeWindow();

    /**
     * Sets the individual to view.
     * @param individual The individual to show.
     * @param id Id of the individual.
     * @param generation Generation number the individual is from.
     */
    void setIndividual(Individual *individual, int id = -1, int generation = -1);
    
private:
    Individual *individual; /**< Individual to show. */

    TreeViewWidget *glTree; /**< GL widget to show the tree. */
};

#endif // TREEWINDOW_H
