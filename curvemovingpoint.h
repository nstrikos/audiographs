#ifndef CURVEMOVINGPOINT_H
#define CURVEMOVINGPOINT_H


#include <QtQuick/QQuickItem>
#include <QTimer>
#include "function.h"
#include "audiopoints.h"

class CurveMovingPoint : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    CurveMovingPoint(QQuickItem *parent = 0);
    ~CurveMovingPoint();

    Q_INVOKABLE void drawPoint(Function *function, int duration);
    Q_INVOKABLE void stopPoint();

    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

    QTimer timer;

    void setColor(const QColor &color);
    QColor color() const;

private slots:
    void timerExpired();

private:
    int m_count;
    int m_timeElapsed;
    int m_duration;
    Function *m_function;

    QColor m_color;

    double m_X;
    double m_Y;

    AudioPoints m_audioPoints;
};

#endif // CURVEMOVINGPOINT_H
