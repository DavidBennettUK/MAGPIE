#ifndef INTVALUE_H
#define INTVALUE_H

#include <QObject>

/**
 * Represents an integer value, within a valid rage.
 * @author David Bennett
 */
class IntValue : public QObject
{
    Q_OBJECT

public:
    /**
     * Constructs the value.
     * @param value The initial value.
     * @param min The minimum allowed value.
     * @param max The maximum allowed value.
     */
    IntValue(int value, int min, int max) : value(value), minVal(min), maxVal(max) { Q_ASSERT(min <= value && value <= max); }

    /**
     * @return The minimum allowed value.
     */
    int getMin() const { return minVal; }

    /**
     * @return The maximum allowed value.
     */
    int getMax() const { return maxVal; }

    /**
     * @return The current value.
     */
    int getValue() const { return value; }

public slots:
    /**
     * Sets the value.
     * @param value Must be in between min and max (inclusive).
     */
    void setValue(int value) { if (value >= minVal && value <= maxVal) this->value = value; }

private:
    int value; /**< The current value. */
    int minVal; /**< The minimum value allowed. */
    int maxVal; /**< The maximum value allowed. */
};

#endif // INTVALUE_H
