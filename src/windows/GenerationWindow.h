#ifndef GENERATIONWINDOW_H
#define GENERATIONWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QTableWidget>
#include <QHash>
#include <QVector>
#include "../gp/Generation.h"
#include "../gp/Individual.h"

/**
 * Shows a table of individuals in a generation.
 * @author David Bennett
 */
class GenerationWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    /**
     * Constructs the window.
     * @param workspace Parent for this window.
     */
    explicit GenerationWindow(QMdiArea *workspace);

    /**
     * Set the generation of individuals to display.
     * @param generation Pointer to the generation to display.
     * @param number Number of the generation in the scenario.
     */
    void setGeneration(Generation *generation, int number = -1);

    /**
     * @return Get a pointer to the generation being displayed.
     */
    Generation *getGeneration() { return generation; }

    /**
     * Set the number of the current generation in the scenario.
     * @param number Number of the current generation.
     */
    void setGenerationNumber(int number);

    /**
     * Highlight the given individual in the list of individuals.
     * @param individual Pointer to the individual to select.
     */
    void selectIndividual(Individual *individual);

public slots:
    /**< Open a solution player window for the selected individual. */
    void playIndividual();

    /**< Open a tree viewer window for the selected individual. */
    void viewTree();

    /**
     * Add an individual to the list of individuals.
     * @param individual A pointer to the individual to add.
     */
    void addIndividual(Individual *individual);

    /** Clear the table of individuals. */
    void clear();

    /** Close all player and tree windows opened from this window. */
    void closeViewWindows();

private slots:
    /**
     * Called when a player window opened by this window has been closed.
     * @param object The window that was closed.
     */
    void playerWindowClosed(QObject *object);

    /**
     * Called when a tree window opened by this window has been closed.
     * @param object The window that was closed.
     */
    void treeWindowClosed(QObject *object);

private:
    QMdiArea *workspace; /**< The workspace for this window. */
    QTableWidget *tblPopulation; /**< The list of individuals. */
    Generation *generation; /**< Pointer to the generation being displayed. */
    int generationNumber; /**< Number of the generation being displayed in the scenario. */
    QHash<int, QMdiSubWindow *> playerWindows; /**< Map of individual ids to player windows. */
    QVector<QMdiSubWindow *> playerWindowList; /**< List of player windows. */
    QHash<int, QMdiSubWindow *> treeWindows; /**< Map of individual ids to tree windows. */
    QVector<QMdiSubWindow *> treeWindowList; /**< List of tree windows. */
};

#endif // GENERATIONWINDOW_H
