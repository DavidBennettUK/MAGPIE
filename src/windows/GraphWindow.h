#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "../gp/Generation.h"
#include "../widgets/GraphWidget.h"
#include "../gp/Scenario.h"

/**
 * Contains graphs used to display statistics for a GP run.
 * Features fitness and tree size graphs.
 * @author David Bennett
 */
class GraphWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * Constructs the window.
     * @param scenario Scenario to show graphs for.
     * @param parent Parent for this window.
     */
    explicit GraphWindow(Scenario *scenario, QWidget *parent = 0);
    
private slots:
    /**
     * Called when a generation is complete to update the graphs.
     * @param generation Copy of the generation that has completed.
     * @param number Number of the generation in the scenario.
     */
    void generationComplete(QSharedPointer<Generation> generation, int number);

    /** Replot the graph, scaling the axes to fit. */
    void updateGraph();

    /** Clear the graph plot lines. */
    void clear();

    /** Called when a run has finished to stop the update timer. */
    void runFinished();

    /**
     * Set the range for the x-axis.
     * @param range The maximum generation number to show.
     */
    void setRange(int range);

private:
    Scenario *scenario; /**< Pointer to the scenario. */
    GraphWidget *fitnessGraph; /**< The fitness graph. */
    GraphWidget *treeGraph; /**< The tree graph. */
    QTimer animationTimer; /**< Animation timer to update the graph. */
};

#endif // GRAPHWINDOW_H
