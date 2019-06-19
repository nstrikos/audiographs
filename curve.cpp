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

        if (m_xLineCoords.size() > 0) {


            float x = m_xLineCoords.at(i);//i;//pos.x() * itemSize.width();
            float y = m_yLineCoords.at(i);//i;//pos.y() * itemSize.height();

            vertices[i].set(x, y);
        }
        else {
            vertices[i].set(0, 0);
        }
    }
    node->markDirty(QSGNode::DirtyGeometry);
    return node;
}
