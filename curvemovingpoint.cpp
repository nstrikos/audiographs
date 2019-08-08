#include "curvemovingpoint.h"

#include "curve.h"

#include <QtQuick/qsgnode.h>
#include <QtQuick/qsgflatcolormaterial.h>

#include <cmath>

CurveMovingPoint::CurveMovingPoint(QQuickItem *parent)
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

CurveMovingPoint::~CurveMovingPoint()
{

}

void CurveMovingPoint::drawPoint(Function *function, int duration)
{
    m_function = function;
    m_duration = duration * 1000;
    m_count = 0;
    m_timeElapsed = 0;
    timer.start();
}

QSGNode *CurveMovingPoint::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGGeometryNode *node = nullptr;
    QSGGeometry *geometry = nullptr;

    if (!oldNode) {
        node = new QSGGeometryNode;

        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), POINT_SEGMENTS);
        geometry->setLineWidth(LINE_WIDTH);
        geometry->setDrawingMode(QSGGeometry::DrawTriangleFan);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);
        QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
        material->setColor(m_color);
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);

    } else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry->allocate(POINT_SEGMENTS);
    }

    QSGGeometry::Point2D *lineVertices = geometry->vertexDataAsPoint2D();

    if (m_function != nullptr) {

            int r = 10;
            for(int ii = 0; ii < POINT_SEGMENTS; ii++) {
                float theta = 2.0f * 3.1415926f * float(ii) / float(POINT_SEGMENTS);//get the current angle

                float x = r * cos(theta);
                float y = r * sin(theta);

                lineVertices[ii].set(x + m_X, y + m_Y);//output vertex
            }
    } else {
        for (int i = 0; i < POINT_SEGMENTS; i++) {
            lineVertices[i].set(-10, -10);
        }
    }

    node->markDirty(QSGNode::DirtyGeometry);
    return node;
}

void CurveMovingPoint::timerExpired()
{
    m_count++;
    m_timeElapsed += timer.interval();
    if (m_timeElapsed >= m_duration) {
        stopPoint();
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

        m_X = xLineCoords->at(x);
        m_Y = yLineCoords->at(x);

        double min = m_function->minValue();
        double max = m_function->maxValue();
        double fmin = 200;
        double fmax = 2000;
        double a;
        double b;
        double l;
        double f;
        if (max != min) {
            a =  (fmax-fmin)/(max - min);
            b = fmax - a * max;
            l = m_function->Y(x);
            f = a * l + b;
            double freq = f;
            m_audioPoints.setFreq(freq);
        }
        else {
            m_audioPoints.setFreq((fmax - fmin) / 2);
        }
        update();
    }
}

void CurveMovingPoint::stopPoint()
{
    m_count = 0;
    m_duration = 0;
    timer.stop();
    m_X = -10;
    m_Y = -10;
    m_audioPoints.stopAudio();
    update();
}

QColor CurveMovingPoint::color() const
{
    return m_color;
}

void CurveMovingPoint::setColor(const QColor &color)
{
    m_color = color;
}

