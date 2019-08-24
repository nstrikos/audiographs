#ifndef CURVEMOVINGPOINT_H
#define CURVEMOVINGPOINT_H


#include <QtQuick/QQuickItem>
#include "curveinterface.h"
#include <QTimer>

//#include "function.h"
//#include "test.h"
//#include "audiopoints.h"

class CurveMovingPoint : public QQuickItem, public CurveInterface
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(bool slowPoint READ slowPoint() WRITE setSlowPoint)

public:
    CurveMovingPoint(QQuickItem *parent = 0);
    ~CurveMovingPoint();

    Q_INVOKABLE void drawPoint(Function *function, int duration);
    Q_INVOKABLE void stopPoint();



//    Q_PROPERTY(double f0 READ f0 WRITE setF0)
//    Q_PROPERTY(double f1 READ f1 WRITE setF1)
//    Q_PROPERTY(double f2 READ f2 WRITE setF2)
//    Q_PROPERTY(double f3 READ f3 WRITE setF3)
//    Q_PROPERTY(double f4 READ f4 WRITE setF4)
//    Q_PROPERTY(double f5 READ f5 WRITE setF5)
//    Q_PROPERTY(double f6 READ f6 WRITE setF6)
//    Q_PROPERTY(double f7 READ f7 WRITE setF7)
//    Q_PROPERTY(double f8 READ f8 WRITE setF8)
//    Q_PROPERTY(double f9 READ f9 WRITE setF9)
//    Q_PROPERTY(double f10 READ f10 WRITE setF10)

//    double f0() const;
//    void setF0(double f0);

//    double f1() const;
//    void setF1(double f1);

//    double f2() const;
//    void setF2(double f2);

//    double f3() const;
//    void setF3(double f3);

//    double f4() const;
//    void setF4(double f4);

//    double f5() const;
//    void setF5(double f5);

//    double f6() const;
//    void setF6(double f6);

//    double f7() const;
//    void setF7(double f7);

//    double f8() const;
//    void setF8(double f8);

//    double f9() const;
//    void setF9(double f9);

//    double f10() const;
//    void setF10(double f10);

    Q_INVOKABLE void setMouseX(Function *function, int mouseX);
    Q_INVOKABLE void clearMouse();

    double slowPoint() const;
    void setSlowPoint(double useSlowPoint);

private slots:
    void timerExpired();

private:
    //    int m_count;
    int m_timeElapsed;
    int m_duration;
//    Function *m_function;
//    void setFrequency(int d, bool useNotes);


//    QVector<double> m_xLineCoords;
//    QVector<double> m_yLineCoords;

    double m_X;
    double m_Y;
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
    QTimer timer;



    int m_mouseX;

//    AudioPoints m_audioPoints;
//    Test m_test;
//    double m_fmin;
//    double m_fmax;

//    double m_f0 = 1.0;
//    double m_f1 = 0.0;
//    double m_f2 = 0.0;
//    double m_f3 = 0.0;
//    double m_f4 = 0.0;
//    double m_f5 = 0.0;
//    double m_f6 = 0.0;
//    double m_f7 = 0.0;
//    double m_f8 = 0.0;
//    double m_f9 = 0.0;
//    double m_f10 = 0.0;

    double m_slowPoint;
};

#endif // CURVEMOVINGPOINT_H
