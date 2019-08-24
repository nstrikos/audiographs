#ifndef CURVE_H
#define CURVE_H

#include <QtQuick/QQuickItem>
#include "curveinterface.h"

class Curve : public QQuickItem, public CurveInterface
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    Curve(QQuickItem *parent = 0);
    ~Curve();

    Q_INVOKABLE void draw(Function *function);

private:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
};

#endif // CURVE_H
