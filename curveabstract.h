#ifndef CURVEABSTRACT_H
#define CURVEABSTRACT_H

#include <QColor>
#include "function.h"

class CurveAbstract
{
//    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    CurveAbstract();
    ~CurveAbstract();

    void setColor(const QColor &color);
    QColor color() const;

protected:
    QColor m_color;
    Function *m_function;
    QVector<Point> m_points;
    void calcCoords(int width, int height);
};

#endif // CURVEABSTRACT_H
