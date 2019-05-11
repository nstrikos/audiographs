#ifndef FUNCTION_H
#define FUNCTION_H

#include <QObject>
#include <QVector>
#include <qmath.h>
#include "fparser/fparser.hh"

class FunctionInput
{
public:
    QString expression;
    QString minimum;
    QString maximum;
    QString numPoints;
};

class Point{
public:
    double x;
    double y;
    bool isValid;
};

class Function : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVector<double> xCoords READ xCoords())
    Q_PROPERTY(QVector<double> yCoords READ yCoords())
    Q_PROPERTY(QVector<double> xLineCoords READ xLineCoords())
    Q_PROPERTY(QVector<double> yLineCoords READ yLineCoords())
    Q_PROPERTY(double minY READ minY())
    Q_PROPERTY(double maxY READ maxY())
    
public:

    Q_INVOKABLE double x(int point);
    Q_INVOKABLE double y(int point);
    Q_INVOKABLE bool isValid(int point);
    Q_INVOKABLE double xLine(int point);
    Q_INVOKABLE double yLine(int point);
    Q_INVOKABLE bool isValidLine(int point);
    Q_INVOKABLE int size();
    Q_INVOKABLE int lineSize();
    Q_INVOKABLE void calcScrCoords(int width, int height);

    QVector<double> xCoords() const;
    QVector<double> yCoords() const;
    QVector<double> xLineCoords() const;
    QVector<double> yLineCoords() const;

    double minY() const;
    double maxY() const;

public slots:
    void calculate(FunctionInput functionInput);
    void calculate(QString expression, QString min, QString max, QString numPoints);
    
signals:
    void update();
    void error(QString err);

private:
    void performCalculation();
    void replaceConstants();
    bool check();
    void calculatePoints();
    QVector<Point> m_points;
    QVector<Point> m_linePoints;
    QString m_expression;
    QString m_minString;
    QString m_maxString;
    QString m_pointsString;
    double m_min;
    double m_max;
    double m_minY;
    double m_maxY;
    int m_numPoints;
    FunctionParser m_fparser;
#ifndef Q_OS_ANDROID
    const int LINE_POINTS = 10000;
#else
    const int LINE_POINTS = 1000;
#endif
    QVector<double> m_xCoords;
    QVector<double> m_yCoords;
    QVector<double> m_xLineCoords;
    QVector<double> m_yLineCoords;
};

#endif // FUNCTION_H
