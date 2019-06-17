#include "curve.h"

#include <QtQuick/qsgnode.h>
#include <QtQuick/qsgflatcolormaterial.h>

#include <cmath>

Curve::Curve(QQuickItem *parent)
    : QQuickItem(parent)
{
    setFlag(ItemHasContents, true);
}

Curve::~Curve()
{

}

void Curve::draw(QVector<double> x, QVector<double> y)
{
    m_xLineCoords = x;
    m_yLineCoords = y;
    update();
}

QSGNode *Curve::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGGeometryNode *node = nullptr;
    QSGGeometry *geometry = nullptr;

    if (!oldNode) {
        node = new QSGGeometryNode;
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 10000);
        geometry->setLineWidth(10);
#ifdef Q_OS_ANDROID
        geometry->setDrawingMode(QSGGeometry::DrawLineStrip);
#else
        geometry->setDrawingMode(QSGGeometry::DrawLineStrip);
#endif
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);
        QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
        material->setColor(QColor(255, 0, 0));
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
    } else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry->allocate(10000);
    }



    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();
    for (int i = 0; i < 10000; i++) {
        //        qreal t = i / qreal(m_segmentCount - 1);
        //        qreal invt = 1 - t;

        //        QPointF pos = invt * invt * invt * m_p1
        //                    + 3 * invt * invt * t * m_p2
        //                    + 3 * invt * t * t * m_p3
        //                    + t * t * t * m_p4;

        if (m_xLineCoords.size() > 0) {


            float x = m_xLineCoords.at(i);//i;//pos.x() * itemSize.width();
            float y = m_yLineCoords.at(i);//i;//pos.y() * itemSize.height();

            vertices[i].set(x, y);
        }
//        else {
//            vertices[i].set(0, 0);
//        }
    }
    node->markDirty(QSGNode::DirtyGeometry);
    return node;
}

BezierCurve::BezierCurve(QQuickItem *parent)
    : QQuickItem(parent)
    , m_p1(0, 0)
    , m_p2(1, 0)
    , m_p3(0, 1)
    , m_p4(1, 1)
    , m_segmentCount(500)
{
    setFlag(ItemHasContents, true);
}
//! [1]

//! [2]
BezierCurve::~BezierCurve()
{
}
//! [2]

//! [3]
void BezierCurve::setP1(const QPointF &p)
{
    if (p == m_p1)
        return;

    m_p1 = p;
    emit p1Changed(p);
    update();
}
//! [3]

void BezierCurve::setP2(const QPointF &p)
{
    if (p == m_p2)
        return;

    m_p2 = p;
    emit p2Changed(p);
    update();
}

void BezierCurve::setP3(const QPointF &p)
{
    if (p == m_p3)
        return;

    m_p3 = p;
    emit p3Changed(p);
    update();
}

void BezierCurve::setP4(const QPointF &p)
{
    if (p == m_p4)
        return;

    m_p4 = p;
    emit p4Changed(p);
    update();
}

void BezierCurve::setSegmentCount(int count)
{
    if (m_segmentCount == count)
        return;

    m_segmentCount = count;
    emit segmentCountChanged(count);
    update();
}

//! [4]
QSGNode *BezierCurve::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGGeometryNode *node = nullptr;
    QSGGeometry *geometry = nullptr;

    if (!oldNode) {
        node = new QSGGeometryNode;
//! [4] //! [5]
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), m_segmentCount);
        geometry->setLineWidth(2);
        geometry->setDrawingMode(QSGGeometry::DrawLineStrip);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);
//! [5] //! [6]
        QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
        material->setColor(QColor(255, 0, 0));
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
//! [6] //! [7]
    } else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry->allocate(m_segmentCount);
    }
//! [7]

//! [8]
    QSizeF itemSize = size();
    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();
    for (int i = 0; i < m_segmentCount; ++i) {
        qreal t = i / qreal(m_segmentCount - 1);
        qreal invt = 1 - t;

        QPointF pos = invt * invt * invt * m_p1
                    + 3 * invt * invt * t * m_p2
                    + 3 * invt * t * t * m_p3
                    + t * t * t * m_p4;

        float x = i;//pos.x() * itemSize.width();
        float y = sin(x);//pos.y() * itemSize.height();

//        qDebug() << x;

        vertices[i].set(x, y);
    }
    node->markDirty(QSGNode::DirtyGeometry);
//! [8]


//! [9]
    return node;
}
