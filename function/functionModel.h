#ifndef FUNCTIONMODEL_H
#define FUNCTIONMODEL_H

class IFunctionModel;

#include "point.h"


#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)
#include "parsers/exprtk/exprtk.hpp"
typedef exprtk::symbol_table<double> symbol_table_t;
typedef exprtk::expression<double>     expression_t;
typedef exprtk::parser<double>             parser_t;
#else
#include "parsers/fparser/fparser.hh"
double powint(const double* p);
#endif

int mygcd(int a, int b);


/*
 * calculate - Calculates function. Updates the graph
 *
 * x - Returns the x value at point i
 *
 * y - Returns the y value at point i if derivative is zero
 *   - Returns y' value if derivative order is one
 *   - Returns y'' value if derivative order is two
 *
 * isValidAt - Returns true if the function is valid at point i
 * validExpression - Returns true if the expression of the function is valid
 * size - Returns the size of the function points
 * setDerivativeMode - Sets the derivative mode and updates the graph
 * derivative - Returns the value of derivative at point i,
 *            - Returns the vasue of second derivative if derivative mode is two
 *
 * Needed by audionotes:
 * minValue - Returns the minimum value of y, y' or y'' depending on derivative order
 * maxValue - Returns the maximum value of y, y' or y'' depending on derivative order
 *
 * Needed by dragHandler, functionZoomer, pinchHandler to round new values:
 * expression - Returns the function expression.
 * minX - Returns function minX
 * maxX - Returns function maxX
 * minY - Returns function minY
 * maxY - Returns function maxY
 *
 * Needed by pointsInterest:
 * updateFirstDerivative - Calculates first derivative points,
 *                       - Needs to be public for functionDescription
 * y_0 - Returns the value of the function at point i
 * y_1 - Returns the value of the first derivative at point i
 * derivativeMode - Derivative mode getter
 * */

class FunctionModel
{
public:
    FunctionModel(IFunctionModel &iface);

    void calculate(QString expression, QString minX, QString maxX, QString minY, QString maxY);

    double x(int i) const;
    double y(int i) const;
    bool isValidAt(int i) const;
    bool validExpression() const;
    int size() const;

    void setDerivativeMode(int mode);
    double derivative(int i);

    double minValue() const;
    double maxValue() const;
    QString expression() const;
    double minX() const;
    double maxX() const;
    double minY() const;
    double maxY() const;

    void updateFirstDerivative();
    double y_0(int i) const;
    double y_1(int i) const;
    int derivativeMode() const;

private:
    void replaceConstants();
    bool check();

    void calculatePoints();
    void calculateFirstDerivative();
    void calculateSecondDerivative();
    void calculateDerivativeMaxima();

    IFunctionModel &iface;

    QString m_expression;
    QString m_minXString;
    QString m_maxXString;
    QString m_minYString;
    QString m_maxYString;
    QString m_pointsString;

    QString m_errorString;

    double m_minX;
    double m_maxX;
    double m_minY;
    double m_maxY;
    double m_minValue;
    double m_maxValue;
    double m_minDerivValue;
    double m_maxDerivValue;
    bool m_validExpression;

#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)
    symbol_table_t symbol_table;
    double m_x;
    expression_t parser_expression;
#else
    FunctionParser m_fparser;
#endif        
    Points m_points;
    Points m_derivPoints;
    Points m_deriv2Points;
    int m_derivativeMode = 0;
};

#endif // FUNCTIONMODEL_H
