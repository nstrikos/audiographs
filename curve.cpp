#include "curve.h"

#include <QtQuick/qsgnode.h>
#include <QtQuick/qsgflatcolormaterial.h>

#include <cmath>

Curve::Curve(QQuickItem *parent)
    : QQuickItem(parent)
{
    setFlag(ItemHasContents, true);

    timer.setTimerType(Qt::PreciseTimer);
    timer.setInterval(50);
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerExpired()));
    m_count = 0;
    m_duration = 0;
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

void Curve::drawPoint(int duration)
{
    m_duration = duration * 1000;
    m_count = 0;
    m_timeElapsed = 0;
    timer.start();
    update();
}

QSGNode *Curve::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGGeometryNode *node = nullptr;
    QSGGeometry *geometry = nullptr;

    QSGGeometryNode *node2 = nullptr;
    QSGGeometry *geometry2 = nullptr;

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

        node2 = new QSGGeometryNode;
        geometry2 = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 10000);
        geometry2->setLineWidth(1);

        geometry2->setDrawingMode(QSGGeometry::DrawTriangleFan);

        node2->setGeometry(geometry2);
        QSGFlatColorMaterial *material2 = new QSGFlatColorMaterial;
        material2->setColor(QColor(0, 0, 255));
        node2->setMaterial(material2);
        node2->setFlag(QSGNode::OwnsMaterial);
        node->appendChildNode(node2);


    } else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry->allocate(10000);
        node2 = static_cast<QSGGeometryNode *>(oldNode->childAtIndex(0));
        geometry2 = node2->geometry();
        geometry2->allocate(64);
    }

    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();
    QSGGeometry::Point2D *vertices2 = geometry2->vertexDataAsPoint2D();

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

    if (m_xLineCoords.size() > 0) {

        int num_segments = 64;
        int cx = (double) m_timeElapsed / m_duration * width();
        int x = round(cx * m_xLineCoords.size() / width());
        if (x >= m_yLineCoords.size())
            x = m_yLineCoords.size() - 1;
        if (x < 0)
            x = 0;
        int cy = m_yLineCoords[x];
        int r = 20;
        for(int ii = 0; ii < num_segments; ii++)
        {
            float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

            float x = r * cos(theta);//calculate the x component
            float y = r * sin(theta);//calculate the y component

            if (m_count > 0) {
                vertices2[ii].set(x + cx, y + cy);//output vertex
            }
            else {
                vertices2[ii].set(0, 0);
            }

        }
    }

    node->markDirty(QSGNode::DirtyGeometry);
    node2->markDirty(QSGNode::DirtyGeometry);
    return node;
}

void Curve::timerExpired()
{
    m_count++;
    m_timeElapsed += timer.interval();
    if (m_timeElapsed >= m_duration) {
        m_count = 0;
        m_duration = 0;
        timer.stop();
    }
    update();
}
