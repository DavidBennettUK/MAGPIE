#ifndef PARAMETER_H
#define PARAMETER_H

#include "../common.h"

/**
 * Interface for all parameters.
 * This is needed to store all parameters in a single collection,
 * as {@link Parameter} is templated.
 * @author David Bennett
 */
class IParameter
{
public:
    virtual ~IParameter() { }
    virtual QString getName() const = 0;
};

/**
 * Represents a parameter.
 */
template <class T>
class Parameter : public IParameter
{
public:
    /**
     * Constructs the parameter.
     * @param name The full name of the parameter.
     * @param value A pointer to the value the parameter represents.
     */
    Parameter(QString name, T value) : name(name), value(value) { }

    /** Deletes the value of the parameter. */
    ~Parameter() { safeDelete(value); }

    /**
     * @return The full name of the parameter.
     */
    QString getName() const { return name; }

    /**
     * @return The value of the parameter.
     */
    T getValue() const { return value; }

private:
    QString name; /**< The full name of the parameter. */
    T value; /**< The value of the parameter. */
};

#endif // PARAMETER_H
