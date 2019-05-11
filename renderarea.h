#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include "parameters.h"
#include "function.h"
#include <math.h>

#include <QDebug>


class RenderArea : public QWidget
{
    Q_OBJECT

public:

    RenderArea(QWidget *parent = nullptr);
    ~RenderArea() override;
    void updateGraph(Function *function);
    void setParameters(Parameters *parameters);
    void startPoints(QString secondsString);
    void previousPoint();
    void nextPoint();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void calcCoordinates();
    void calcMinMax();
    void draw();
    void initialize(QPainter &painter);
    void drawLine(QPainter &painter);
    void drawPoints(QPainter &painter);
    void drawCurrentPoint(QPainter &painter);
    void drawGrid(QPainter &painter);
    void drawAxes(QPainter &painter);
    double interval(double diff);
    void findVerticalGridLines(double x0, double x1, double dl);
    void drawVerticalLines(QPainter &painter);
    void findHorizontalGridLines(double y0, double y1, double dl);
    void drawHorizontalLines(QPainter &painter);

    Parameters *m_params;
    Function *m_function;
    QVector <QPoint> m_points;
    QVector <QPoint> m_linePoints;
    QVector<int> m_xGridCoords;
    QVector<int> m_yGridCoords;
    QVector<double> m_xGridValues;
    QVector<double> m_yGridValues;
    double m_yMin;
    double m_yMax;
    double m_xMin;
    double m_xMax;

    int m_currentPoint;
    bool m_showHighlightPoint = false;
    QTimer *m_timer;
    unsigned int m_timerCount;
    unsigned int m_seconds;
    double m_secondsElapsed;

private slots:
    void timerExpired();
};

#endif // RENDERAREA_H
