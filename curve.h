#ifndef CURVE_H
#define CURVE_H


#include <QtQuick/QQuickItem>

class Curve : public QQuickItem
{
    Q_OBJECT

public:
    Curve(QQuickItem *parent = 0);
    ~Curve();

    Q_INVOKABLE void draw(QVector<double> x, QVector<double> y);

    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

    QVector<double> m_xLineCoords;
    QVector<double> m_yLineCoords;
};

#endif // CURVE_H
