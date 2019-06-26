#ifndef CURVE_H
#define CURVE_H


#include <QtQuick/QQuickItem>
#include <QTimer>

class Curve : public QQuickItem
{
    Q_OBJECT

public:
    Curve(QQuickItem *parent = 0);
    ~Curve();

    Q_INVOKABLE void draw(QVector<double> x, QVector<double> y);
    Q_INVOKABLE void drawPoint(int duration);

    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

    QVector<double> m_xLineCoords;
    QVector<double> m_yLineCoords;

    QTimer timer;

private slots:
    void timerExpired();

private:
    int m_count;
    int m_timeElapsed;
    int m_duration;
};

#endif // CURVE_H
