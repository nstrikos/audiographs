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

class FunctionModel
{
public:
    FunctionModel(IFunctionModel &iface);
    void calculate(QString expression, QString minX, QString maxX, QString minY, QString maxY);

    QString expression() const;
    double minX() const;
    double maxX() const;
    double minY() const;
    double maxY() const;
    double x(int i);
    double y(int i);
    double minValue() const;
    double maxValue() const;
    bool isValid(int i);
    bool validExpression() const;
    int size();
    void setDerivativeMode(int mode);
    double derivative(int i);

    //Needed to calculate maxima by PointsInterest
    void refreshDerivative(); //Calculate first order derivative without drawing
    double y_0(int i); //The value of the function at point i
    double y_1(int i); //The value of the first derivative at point i
    int derivativeMode() const; //Derivative mode getter

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

    //QVector<Point> m_points;
    //array<Point,10000>m_points;
    Points m_points;
    Points m_derivPoints;
    Points m_firstDerivPoints;
    int m_derivativeMode = 0;
};

#endif // FUNCTIONMODEL_H
