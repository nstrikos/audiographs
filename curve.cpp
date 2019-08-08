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
    m_function = nullptr;
}

Curve::~Curve()
{

}

void Curve::drawPoint(int duration)
{
    m_duration = duration * 1000;
    m_count = 0;
    m_timeElapsed = 0;
    timer.start();
    update();
}

void Curve::draw(Function *function)
{
    m_function = function;
    update();
}

QSGNode *Curve::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGGeometryNode *node = nullptr;
    QSGGeometry *geometry = nullptr;

#ifdef Q_OS_ANDROID
    QVector<QSGGeometryNode*> nodeVector;
    QVector<QSGGeometry*> geometryVector;
#endif

    if (!oldNode) {
        node = new QSGGeometryNode;

#ifndef Q_OS_ANDROID
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), LINE_POINTS);
#else
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 1);
#endif

        geometry->setLineWidth(LINE_WIDTH);
        geometry->setDrawingMode(QSGGeometry::DrawPoints);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);
        QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
        material->setColor(m_color);
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);

#ifdef Q_OS_ANDROID
        for (int i = 0; i < LINE_POINTS; i++) {
            QSGGeometryNode *tmpNode = new QSGGeometryNode;
            QSGGeometry *tmpGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 16);
            tmpGeometry->setDrawingMode(QSGGeometry::DrawTriangleFan);
            tmpNode->setGeometry(tmpGeometry);
            QSGFlatColorMaterial *tmpMaterial = new QSGFlatColorMaterial;
            tmpMaterial->setColor(DEFAULT_LINE_COLOR);
            tmpNode->setMaterial(tmpMaterial);
            tmpNode->setFlag(QSGNode::OwnsMaterial);
            node->appendChildNode(tmpNode);
        }
#endif

    } else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
#ifndef Q_OS_ANDROID
        geometry->allocate(LINE_POINTS);
#else
        geometry->allocate(1);
#endif

#ifdef Q_OS_ANDROID
        for (int i = 0; i < LINE_POINTS; i++) {
            QSGGeometryNode *tmpNode = static_cast<QSGGeometryNode *>(oldNode->childAtIndex(i));
            nodeVector.append(tmpNode);
            QSGGeometry *tmpGeometry = tmpNode->geometry();
            tmpGeometry->allocate(POINT_SEGMENTS);
            tmpGeometry->setDrawingMode(QSGGeometry::DrawTriangleFan);
            geometryVector.append(tmpGeometry);
        }
#endif
    }

    QSGGeometry::Point2D *lineVertices = geometry->vertexDataAsPoint2D();

#ifndef Q_OS_ANDROID
    if (m_function != nullptr) {
        QVector<double> *xLineCoords = m_function->xLineCoords();
        QVector<double> *yLineCoords = m_function->yLineCoords();
        for (int i = 0; i < LINE_POINTS; i++) {

            float x = xLineCoords->at(i);
            float y = yLineCoords->at(i);

            lineVertices[i].set(x, y);
        }
    } else {
        for (int i = 0; i < LINE_POINTS; i++) {
            lineVertices[i].set(-10, -10);
        }
    }
#else
    lineVertices[0].set(-10, -10);
#endif

#ifdef Q_OS_ANDROID
    if (m_function != nullptr) {
        QVector<double> *xLineCoords = m_function->xLineCoords();
        QVector<double> *yLineCoords = m_function->yLineCoords();

        if (geometryVector.size() > 0) {
            if (xLineCoords->size() > 0) {
                for (int i = 0; i < LINE_POINTS; i++) {
                    QSGGeometryNode *tmpNode = nodeVector.at(i);
                    QSGGeometry::Point2D *vertices = geometryVector.at(i)->vertexDataAsPoint2D();

                    int cx;
                    int cy;
                    cx = xLineCoords->at(i);
                    cy = yLineCoords->at(i);

                    int r = 5;
                    for(int ii = 0; ii < POINT_SEGMENTS; ii++) {
                        float theta = 2.0f * 3.1415926f * float(ii) / float(POINT_SEGMENTS);//get the current angle

                        float x = r * cos(theta);
                        float y = r * sin(theta);

                        vertices[ii].set(x + cx, y + cy);//output vertex
                    }
                    tmpNode->markDirty(QSGNode::DirtyGeometry);
                }
            }
        }
    }
#endif

    node->markDirty(QSGNode::DirtyGeometry);
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
        emit stopPoint();
        return;
    }

    if (m_function != nullptr) {
        QVector<double> *xLineCoords = m_function->xLineCoords();
        QVector<double> *yLineCoords = m_function->yLineCoords();

        double cx = (double) m_timeElapsed / m_duration;
        int x = round(cx * xLineCoords->size());
        if (x >= xLineCoords->size())
            x = xLineCoords->size() - 1;
        if (x < 0)
            x = 0;

        emit movePoint(xLineCoords->at(x), yLineCoords->at(x), m_previousX, m_previousY);
        m_previousX = xLineCoords->at(x);
        m_previousY = yLineCoords->at(x);
    }
}

QColor Curve::color() const
{
    return m_color;
}

void Curve::setColor(const QColor &color)
{
    m_color = color;
}
