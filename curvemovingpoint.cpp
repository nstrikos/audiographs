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

void CurveMovingPoint::drawPoint(Function *function,
                                 QString expression,
                                 double start,
                                 double end,
                                 int duration,
                                 int fmin,
                                 int fmax,
                                 bool useNotes)
{
    m_function = function;
    m_duration = duration * 1000;
    m_fmin = (double) fmin;
    m_fmax = (double) fmax;
    m_useNotes = useNotes;
    m_count = 0;
    m_timeElapsed = 0;
    timer.start();

    if (!m_useNotes) {
        m_test.start(expression, start, end, duration, fmin, fmax);
    }
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

        if (m_useNotes)
            setFrequency(x, m_useNotes);
        update();
    }
}

void CurveMovingPoint::setFrequency(int d, bool useNotes)
{
    double min = m_function->minValue();
    double max = m_function->maxValue();
    double a;
    double b;
    double l;
    double freq;
    bool n = true;
    if (max != min) {
        a =  (m_fmax-m_fmin)/(max - min);
        b = m_fmax - a * max;
        l = m_function->Y(d);
        if (l >= 0)
            n = true;
        else
            n = false;
        freq = a * l + b;
        m_audioPoints.setFreq(freq, useNotes, n);
    }
    else {
        m_audioPoints.setFreq((m_fmax - m_fmin) / 2, useNotes, n);
    }
}

void CurveMovingPoint::setMouseX(Function *function, int mouseX, int fmin, int fmax, bool useNotes)
{
    m_function = function;
    m_mouseX = mouseX;
    m_fmin = fmin;
    m_fmax = fmax;
    m_useNotes = useNotes;
    if (m_mouseX < 0)
        m_mouseX = 0;
    if (m_mouseX > this->width())
        m_mouseX = this->width();

    QVector<double> *xLineCoords = m_function->xLineCoords();
    QVector<double> *yLineCoords = m_function->yLineCoords();

    int x = round((m_mouseX / this->width()) * xLineCoords->size());
    if (x < 0)
        x = 0;
    if (x >= xLineCoords->size())
        x = xLineCoords->size() - 1;

    m_X = xLineCoords->at(x);
    m_Y = yLineCoords->at(x);
    setFrequency(x, m_useNotes);
    update();
}

void CurveMovingPoint::clearMouse()
{
    stopPoint();
}

void CurveMovingPoint::stopPoint()
{
    m_count = 0;
    m_duration = 0;
    timer.stop();
    m_X = -10;
    m_Y = -10;
    m_audioPoints.stopAudio();
    m_test.stop();
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

double CurveMovingPoint::f10() const
{
    return m_f10;
}

void CurveMovingPoint::setF10(double f10)
{
    m_f10 = f10;
    m_audioPoints.setF10(f10);
}

double CurveMovingPoint::f9() const
{
    return m_f9;
}

void CurveMovingPoint::setF9(double f9)
{
    m_f9 = f9;
    m_audioPoints.setF9(f9);
}

double CurveMovingPoint::f8() const
{
    return m_f8;
}

void CurveMovingPoint::setF8(double f8)
{
    m_f8 = f8;
    m_audioPoints.setF8(f8);
}

double CurveMovingPoint::f7() const
{
    return m_f7;
}

void CurveMovingPoint::setF7(double f7)
{
    m_f7 = f7;
    m_audioPoints.setF7(f7);
}

double CurveMovingPoint::f6() const
{
    return m_f6;
}

void CurveMovingPoint::setF6(double f6)
{
    m_f6 = f6;
    m_audioPoints.setF6(f6);
}

double CurveMovingPoint::f5() const
{
    return m_f5;
}

void CurveMovingPoint::setF5(double f5)
{
    m_f5 = f5;
    m_audioPoints.setF5(f5);
}

double CurveMovingPoint::f4() const
{
    return m_f4;
}

void CurveMovingPoint::setF4(double f4)
{
    m_f4 = f4;
    m_audioPoints.setF4(f4);
}

double CurveMovingPoint::f3() const
{
    return m_f3;
}

void CurveMovingPoint::setF3(double f3)
{
    m_f3 = f3;
    m_audioPoints.setF3(f3);
}

double CurveMovingPoint::f2() const
{
    return m_f2;
}

void CurveMovingPoint::setF2(double f2)
{
    m_f2 = f2;
    m_audioPoints.setF2(f2);
}

double CurveMovingPoint::f1() const
{
    return m_f1;
}

void CurveMovingPoint::setF1(double f1)
{
    m_f1 = f1;
    m_audioPoints.setF1(f1);
}

double CurveMovingPoint::f0() const
{
    return m_f0;
}

void CurveMovingPoint::setF0(double f0)
{
    m_f0 = f0;
    m_audioPoints.setF0(f0);
}

