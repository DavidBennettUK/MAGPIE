#ifndef LAWNVIEWMULTIWIDGET_H
#define LAWNVIEWMULTIWIDGET_H

#include "LawnViewWidget.h"
#include "../scenarios/lawnmowerMulti/LawnmowerMulti.h"

/**
 * View for the lawnmower problem with obstacles.
 * @see LawnViewWidget
 * @author David Bennett
 */
class LawnViewMultiWidget : public LawnViewWidget
{
public:
    /**
     * Constructs the widget.
     * @param parent The parent widget.
     */
    LawnViewMultiWidget(QWidget *parent = 0) : LawnViewWidget(parent) { }

protected:
    /** Draws the stats text. */
    virtual void drawText();

    /** Draws the lawn. */
    void drawLawn();
};

#endif // LAWNVIEWMULTIWIDGET_H
