#ifndef CURVEINTERFACE_H
#define CURVEINTERFACE_H

#include <QColor>
#include "function.h"
#include "point.h"
#include <QVector>

class CurveInterface
{

public:
    CurveInterface();
    ~CurveInterface();

    void setColor(const QColor &color);
    QColor color() const;

protected:
    QColor m_color;
    Function *m_function;
    QVector<Point> m_points;
    void calcCoords(int width, int height);
};

#endif // CURVEINTERFACE_H
