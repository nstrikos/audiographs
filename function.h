#ifndef FUNCTION_H
#define FUNCTION_H

#include <QObject>
#include <QVector>
#include <qmath.h>
#include "fparser/fparser.hh"
#include "constants.h"

class Function : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double min READ min)
    Q_PROPERTY(double max READ max)
    Q_PROPERTY(double minY READ minY)
    Q_PROPERTY(double maxY READ maxY)

public:

    double min() const;
    double max() const;
    double minY() const;
    double maxY() const;
    QVector<double> *xCoords();
    QVector<double> *yCoords();
    QVector<double> *xLineCoords();
    QVector<double> *yLineCoords();

    double maxValue() const;
    double minValue() const;
    double Y(int i) const;
public slots:
    void calculate(QString expression,
                   QString min,
                   QString max,
                   QString minY,
                   QString maxY,
                   QString numPoints,
                   int width,
                   int height);
    
signals:
    void update();
    void error(QString err);

private:
    void performCalculation();
    void replaceConstants();
    bool check();
    void calculatePoints();
    void calcScrCoords();
    QString m_expression;
    QString m_minString;
    QString m_maxString;
    QString m_minYString;
    QString m_maxYString;
    QString m_pointsString;
    int m_width;
    int m_height;
    double m_min;
    double m_max;
    double m_minY;
    double m_maxY;
    double m_maxValue;
    double m_minValue;
    int m_numPoints;
    FunctionParser m_fparser;

    const int MIN_POINTS = 1;
    const int MAX_POINTS = 10000;

    QVector<double> m_xValues;
    QVector<double> m_yValues;
    QVector<bool> m_isValid;

    QVector<double> m_xLineValues;
    QVector<double> m_yLineValues;
    QVector<bool> m_isLineValid;

    QVector<double> m_xCoords;
    QVector<double> m_yCoords;
    QVector<double> m_xLineCoords;
    QVector<double> m_yLineCoords;
};

#endif // FUNCTION_H
