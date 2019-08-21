#ifndef PARSER_H
#define PARSER_H

#include "./atmsp-1.0.4/atmsp.h"
#include <QThread>
#include <QString>
#include <QList>

class Parser : public QThread
{
    Q_OBJECT

public:
    Parser();
    ~Parser();
    void run();
    void setFunctionString(QString arg1);
    QString functionString();
    void setXStart(double arg1);
    double xStart();
    void setXEnd(double arg1);
    double xEnd();
    void setYStart(double arg1);
    double yStart();
    void setYEnd(double arg1);
    double yEnd();
    void setH(double arg1);
    double h();
    QList<double> yPoints();
    QList<double> xPoints();

    Q_PROPERTY(QString functionString READ functionString WRITE setFunctionString)
    Q_PROPERTY(double xStart READ xStart WRITE setXStart)
    Q_PROPERTY(double xEnd READ xEnd WRITE setXEnd)
    Q_PROPERTY(double yStart READ yStart WRITE setYStart)
    Q_PROPERTY(double yEnd READ yEnd WRITE setYEnd)
    Q_PROPERTY(double h READ h WRITE setH)
    Q_PROPERTY(QList<double> yPoints READ yPoints)
    Q_PROPERTY(QList<double> xPoints READ xPoints)

signals:
    void calculationFinished();

public slots:
    void receiveGraphSignal();

private:
    ATMSP<double> atmspParser;
    ATMSB<double> byteCode;
    std::string m_functionString;
    double m_xStart;
    double m_xEnd;
    double m_yStart;
    double m_yEnd;
    double m_h;
    QList<double> m_YPoints;
    QList<double> m_XPoints;

};

#endif // PARSER_H
