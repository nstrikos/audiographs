#ifndef FUNCTIONDISPLAYVIEW_H
#define FUNCTIONDISPLAYVIEW_H


#include <QtQuick/QQuickItem>
#include "functionDisplayViewInterface.h"
#include "requests.h"

class FunctionDisplayView : public QQuickItem, public FunctionDisplayViewInterface, public RequestReceiver
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth)
    Q_PROPERTY(bool derivative READ derivative  WRITE setDerivative)

public:
    FunctionDisplayView(QQuickItem *parent = nullptr);
    ~FunctionDisplayView () override;

    Q_INVOKABLE void updateView();
    virtual void accept(Request *request) override;

//    void drawDerivative(FunctionModel *model);

    void setColor(const QColor &color);
    QColor color() const;

    int lineWidth() const;
    void setLineWidth(int lineWidth);

    Q_INVOKABLE void setUpdate(bool update);

    void setDerivative(bool newDerivative);
    bool derivative();

public slots:
    void draw(Points *points,
              double xMin,
              double xMax,
              double yMin,
              double yMax);
    Q_INVOKABLE void clear();


private:
    RequestHandler *requestHandler;
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;
    QColor m_color;
    QColor m_newColor;
    int m_lineWidth;
    int m_factor;
    bool m_update;
    bool m_derivative;
};

#endif // FUNCTIONDISPLAYVIEW_H
