#ifndef FUNCTION_H
#define FUNCTION_H

#include <QObject>
#include <QVector>
#include <point.h>
#include <qmath.h>
#include "fparser/fparser.hh"
#include "constants.h"

class Function : public QObject
{
    Q_OBJECT

public:
    ~Function();
    Q_INVOKABLE void calculate(QString expression,
                               QString minX,
                               QString maxX,
                               QString minY,
                               QString maxY,
                               QString numPoints);

    double x(int i) const;
    double y(int i) const;
    int lineSize() const;
    double maxValue() const;
    double minValue() const;

    Q_INVOKABLE double minX() const;
    Q_INVOKABLE double maxX() const;
    Q_INVOKABLE double minY() const;
    Q_INVOKABLE double maxY() const;

signals:
    void update();
    void error(QString err);

private:
    void performCalculation();
    void replaceConstants();
    bool check();
    void calculatePoints();
    QString m_expression;
    QString m_minXString;
    QString m_maxXString;
    QString m_minYString;
    QString m_maxYString;
    QString m_pointsString;
    double m_minX;
    double m_maxX;
    double m_minY;
    double m_maxY;
    double m_maxValue;
    double m_minValue;
    int m_numPoints;
    FunctionParser m_fparser;

    QVector<Point> m_linePoints;
    QVector<Point> m_points;
};

#endif // FUNCTION_H
