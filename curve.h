#ifndef CURVE_H
#define CURVE_H

#include <QtQuick/QQuickItem>
#include "curveabstract.h"
#include "point.h"

class Curve : public QQuickItem, public CurveAbstract
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    Curve(QQuickItem *parent = 0);
    ~Curve();

    Q_INVOKABLE void draw(Function *function);

    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
};

#endif // CURVE_H
