#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include "../lib/qcustomplot.h"

/**
 * Base class for graphs.
 * @author David Bennett
 */
class GraphWidget : public QCustomPlot
{
    Q_OBJECT

public:
    /**
     * Constructs the graph widget.
     * @param parent The parent of the widget.
     */
    GraphWidget(QWidget *parent = NULL);

private slots:
    /**
     * Hides the appropriate plot line when the legend item is clicked.
     * @param legend The legend.
     * @param item The item that has been clicked.
     */
    void legendItemClickEx(QCPLegend *legend, QCPAbstractLegendItem *item);

    /**
     * Scales the graph to fit when the x-axis is double clicked.
     * @param axis The axis that has been double clicked.
     * @param part What part has been double clicked.
     */
    void axisDoubleClickEx(QCPAxis *axis, QCPAxis::SelectablePart part);
};

#endif // GRAPHWIDGET_H
