#include "GraphWidget.h"

GraphWidget::GraphWidget(QWidget *parent) :
    QCustomPlot(parent)
{
    legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(8);
    legend->setFont(legendFont);
    legend->setSelectedFont(legendFont);
    legend->setPositionStyle(QCPLegend::psBottomRight);
    legend->setBrush(QBrush(QColor(255,255,255,0)));
    legend->setSelectable(QCPLegend::spItems);
    legend->setMargin(0,0,0,0);
    legend->setPadding(240,0,0,10);
    legend->setAutoSize(true);
    legend->setSelectedTextColor(legend->textColor());
    legend->setSelectedBorderPen(QPen(QColor(0,0,0,0)));
    legend->setSelectedIconBorderPen(QPen(QColor(0,0,0,0)));
    legend->setBorderPen(QPen(QColor(0,0,0,0)));
    legend->setIconSize(10,10);
    legend->setIconTextPadding(5);

    setRangeDrag(Qt::Horizontal);
    setRangeZoom(Qt::Horizontal);
    setInteractions(QCustomPlot::iRangeDrag | QCustomPlot::iRangeZoom | QCustomPlot::iSelectLegend);

    connect(this, SIGNAL(legendClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendItemClickEx(QCPLegend*,QCPAbstractLegendItem*)));
    connect(this, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisDoubleClickEx(QCPAxis*,QCPAxis::SelectablePart)));
}

void GraphWidget::legendItemClickEx(QCPLegend *legend, QCPAbstractLegendItem *item)
{
    Q_UNUSED(legend);

    if (item)
    {
        QCPPlottableLegendItem *plotItem = qobject_cast<QCPPlottableLegendItem*>(item);
        plotItem->plottable()->setVisible(!plotItem->plottable()->visible());
    }
}

void GraphWidget::axisDoubleClickEx(QCPAxis *axis, QCPAxis::SelectablePart part)
{
    if (part == QCPAxis::spAxisLabel)
    {
        if (axis == xAxis)
        {
            for (int i = 0; i < graphCount(); i++)
            {
                graph(i)->rescaleKeyAxis(i != 0);
            }
        }
        else if (axis == yAxis)
        {
            for (int i = 0; i < graphCount(); i++)
            {
                graph(i)->rescaleValueAxis(i != 0);
            }
        }
    }
}

