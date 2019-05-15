#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    m_params = nullptr;
    m_function = nullptr;

    m_currentPoint = -1;
    m_timer = nullptr;
    //m_currentPoint2 = -1;
}

RenderArea::~RenderArea()
{
    if (m_timer != nullptr)
        delete m_timer;
}

void RenderArea::setParameters(Parameters *parameters)
{
    m_params = parameters;
}

void RenderArea::updateGraph(Function *function)
{
    m_function = function;
    if (m_function->size() > 0) {
        m_xMin = m_function->x(0);
        m_xMax = m_function->x(m_function->size() - 1);

        calcCoordinates();
        update();
    }
}

void RenderArea::calcCoordinates()
{
    m_points.clear();
    m_linePoints.clear();
    int w = this->width();
    int h = this->height();

    calcMinMax();

    if (m_function != nullptr) {
        for (int i = 0; i < m_function->size(); i++) {
            if (m_function->isValid(i)) {
                int k = static_cast<int>( round(  w / (m_xMax - m_xMin) * (m_function->x(i) - m_xMin) ));
                int l = static_cast<int>( round( (h / (m_yMax - m_yMin) * (m_function->y(i) - m_yMin) ) ));
                l = h - l;
                m_points.append(QPoint(k, l));
            }
        }
    }

    if (m_function != nullptr) {
        for (int i = 0; i < m_function->lineSize(); i++) {
            int k = static_cast<int>( round(  w / (m_xMax - m_xMin) *
                                              (m_function->xLine(i) - m_xMin) ));
            int l = static_cast<int>( round( (h / (m_yMax - m_yMin) *
                                              (m_function->yLine(i) - m_yMin) ) ));
            l = h - l;
            m_linePoints.append(QPoint(k, l));
        }
    }
}

void RenderArea::calcMinMax()
{
    m_yMin = m_function->y(0);
    m_yMax = m_yMin;
    for (int i = 0; i < m_function->size(); i++) {
        if (std::isfinite(m_function->y(i))) {
            if (m_function->y(i) < m_yMin)
                m_yMin = m_function->y(i);
            if (m_function->y(i) > m_yMax)
                m_yMax = m_function->y(i);
        }
    }

    if ( abs(m_yMax - m_yMin) < 1e-10) {
        if (m_yMax >= 0) {
            m_yMax = 1.5 * m_yMin;
            m_yMin = 0.5 * m_yMin;
        } else {
            m_yMax = 0.5 * m_yMin;
            m_yMin = 1.5 * m_yMin;
        }
    }
    else {
        if (m_yMax > 100) m_yMax = 100;
        if (m_yMin < -100) m_yMin = -100;
    }
    //    m_yMax = 10;
    //    m_yMin = -10;
    //    for (int i = 0; i < m_xValues->length(); i++) {
    //        qDebug() << m_xValues->at(i);
    //    }
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (m_params != nullptr && m_function != nullptr) {
        draw();
    }
}

void RenderArea::draw()
{
    QPainter painter(this);
    initialize(painter);

    if (m_params->showAxes()) {
        if (m_function->size() > 0)
            drawGrid(painter);
    }

    if (m_params->showLine())
        drawLine(painter);

    if (m_params->showPoints())
        drawPoints(painter);

    if (m_currentPoint >= 0 && m_currentPoint < m_points.size()
            && !m_points.isEmpty() && m_showHighlightPoint == true) {
        drawCurrentPoint(painter);
    }


    //if (m_currentPoint2 != -1) {
    //QBrush brush3(m_params->highlightColor());
    //painter.setBrush(brush3);
    //painter.setPen(Qt::NoPen);

    //int center_x = m_linePoints.at(m_currentPoint2).x();
    //int center_y = m_linePoints.at(m_currentPoint2).y();
    //int radius = m_params->highlightSize();
    //QRectF rectangle(center_x - radius / 2, center_y - radius / 2, radius, radius );
    //painter.drawEllipse(rectangle);
    //}

    //QBrush brush4(Qt::NoBrush);
    //QPen pen4(brush4, 1);
    //painter.setPen(pen4);
    //painter.drawRect(QRect(0, 0, width() - 1, height() - 1));

    //    QFont font=painter.font() ;
    //    font.setPointSize (8);
    //    font.setWeight(QFont::DemiBold);
    //    painter.setFont(font);
    //    painter.drawText( QPoint(20,20), "text" );
}

void RenderArea::initialize(QPainter &painter)
{
    painter.setRenderHint(QPainter::Antialiasing, true);

    QBrush backgoundBrush(m_params->backgroundColor());
    painter.fillRect(this->rect(), backgoundBrush);
}

void RenderArea::drawLine(QPainter &painter)
{
    QBrush lineBrush(m_params->lineColor());
    QPen linePen(lineBrush, m_params->lineWidth());
    painter.setPen(linePen);

    double dy;
    for (int i = 0; i < m_linePoints.length() - 1; i++) {
        dy = (m_function->yLine(i+1) - m_function->yLine(i)) /
                (m_function->xLine(i+1) - m_function->xLine(i));
        if (abs(dy) < 10000 && m_function->isValidLine(i) && m_function->isValidLine(i+1))
            painter.drawLine(m_linePoints[i], m_linePoints[i+1]);
    }
}

void RenderArea::drawPoints(QPainter &painter)
{
    QBrush pointBrush(m_params->pointColor());
    QPen pointPen(pointBrush, m_params->pointSize());
    painter.setPen(pointPen);

    for (int i = 0; i < m_points.length(); i++) {
        int center_x = m_points.at(i).x();
        int center_y = m_points.at(i).y();
        int radius = m_params->pointSize();
        QRectF rectangle(center_x - radius / 2, center_y - radius / 2, radius, radius );
        painter.drawEllipse(rectangle);
    }
}

void RenderArea::drawCurrentPoint(QPainter &painter)
{
    QBrush brush3(m_params->highlightColor());
    painter.setBrush(brush3);
    painter.setPen(Qt::NoPen);
    int center_x = m_points.at(m_currentPoint).x();
    int center_y = m_points.at(m_currentPoint).y();
    int radius = m_params->highlightSize();
    QRectF rectangle(center_x - radius / 2, center_y - radius / 2, radius, radius );
    painter.drawEllipse(rectangle);
}

void RenderArea::drawGrid(QPainter &painter)
{

    QBrush brush(m_params->axesColor());
    QPen pen(brush, m_params->axesSize());
    painter.setPen(pen);

    drawAxes(painter);

    double xStart = m_function->x(0);
    double xEnd = m_function->x(m_function->size() - 1);
    double xInterval = interval(xEnd - xStart);

    QPen linePen(brush, 0.04 * m_params->axesSize());
    painter.setPen(linePen);

    findVerticalGridLines(xStart, xEnd, xInterval);
    drawVerticalLines(painter);

    double yStart = m_yMin;
    double yEnd = m_yMax;
    double yInterval = interval(yEnd - yStart);

    findHorizontalGridLines(yStart, yEnd, yInterval);
    drawHorizontalLines(painter);
}

void RenderArea::drawAxes(QPainter &painter)
{
    double x0 = m_function->x(0);
    double x1 = m_function->x(m_function->size() - 1);
    double y0 = m_yMin;
    double y1 = m_yMax;

    int xAxes =  round( this->width()  / (x1 - x0) * (0 - x0) );
    int yAxes = round( this->height() / (y1 - y0) * (0 - y0) );

    painter.drawLine(xAxes, 0, xAxes, this->height());
    painter.drawLine(0, this->height() - yAxes, this->width(), this->height() - yAxes);
}

double RenderArea::interval(double diff)
{
    double m;
    double times;
    double ival;
    double power = floor(log10(diff)) - 1;

    m = 10 * pow(10, power);
    times = diff / m;
    if (times <= 10)
        ival = m;

    m = 5 * pow(10, power);
    times = diff / m;
    if (times <= 10)
        ival = m;

    m = 4 * pow(10, power);
    times = diff / m;
    if (times <= 10)
        ival = m;

    m = 2 * pow(10, power);
    times = diff / m;
    if (times <= 10)
        ival = m;

    m = 1 * pow(10, power);
    times = diff / m;
    if (times <= 10)
        ival = m;

    return ival;
}

void RenderArea::findVerticalGridLines(double x0, double x1, double dl)
{
    m_xGridCoords.clear();
    m_xGridValues.clear();

    double point = x0;
    point = point / dl;
    point = floor(point);
    point = point * dl;
    //tempGrid.push(Math.round( strip( canvas.width / (xEnd - xStart) * (point - xStart) ) ))
    //xGrid.push(point)

    bool done = false;
    while (!done) {
        point += dl;
        int screenPoint = round( this->width() / (x1 - x0) * (point - x0) );
        m_xGridCoords.append(screenPoint);
        double value = round(point / dl) * dl;
        m_xGridValues.append(value);

        if (point > x1)
            done = true;
    }
}

void RenderArea::drawVerticalLines(QPainter &painter)
{
    QFont font=painter.font() ;
    font.setPointSize (m_params->axesSize() * 2);
    font.setWeight(QFont::DemiBold);
    painter.setFont(font);

    QFontMetrics fm(font);

    int i = 0;
    double x = 0;
    while ( i < m_xGridCoords.length()) {
        x = m_xGridCoords[i];
        painter.drawLine(x, 0, x, this->height());

        QString text = QString::number(m_xGridValues[i], 'g', 10);

        int pixelsWide = fm.width(text);
        int pixelsHigh = fm.height();

        int pos;
        if (x + pixelsWide / 2 > this->width() )
            pos = x - pixelsWide;
        else
            pos = x - pixelsWide / 2;

        painter.drawText( QPoint(pos, pixelsHigh), text);
        i++;
    }
}

void RenderArea::findHorizontalGridLines(double y0, double y1, double dl)
{
    m_yGridCoords.clear();
    m_yGridValues.clear();

    double point = y0;
    point = point / dl;
    point = floor(point);
    point = point * dl;
    m_yGridCoords.append(this->height() - round( this->height() / (y1 - y0) * (point - y0) ) );
    //int value = round (point / dl) * dl;
    m_yGridValues.append(point);

    bool done = false;
    while (!done) {
        point += dl;
        if (point > y1) {
            done = true;
        } else {
            int screenPoint = round( this->height() / (y1 - y0) * (point - y0) );
            screenPoint = this->height() - screenPoint;
            m_yGridCoords.append(screenPoint);
            double value = round (point / dl) * dl;
            m_yGridValues.append(value);
        }
    }
}

void RenderArea::drawHorizontalLines(QPainter &painter)
{
    QFont font=painter.font() ;
    font.setPointSize (m_params->axesSize() * 2);
    font.setWeight(QFont::DemiBold);
    painter.setFont(font);

    QFontMetrics fm(font);
    int pixelsHigh = fm.height();

    int i = 0;
    double y = 0;
    while ( i < m_yGridCoords.length()) {
        y = m_yGridCoords[i];
        painter.drawLine(0, y, this->width(), y);

        QString text = QString::number(m_yGridValues[i], 'g', 10);

        if (y - pixelsHigh > 0) {
            painter.drawText( QPoint(0, y), text);
        }
        i++;
    }
}

void RenderArea::previousPoint()
{
    if (m_function != nullptr && m_params != nullptr) {

        m_currentPoint--;
        m_showHighlightPoint = true;

        if (m_currentPoint < -1) {
            m_currentPoint = -1;
            m_showHighlightPoint = false;
        }
        update();
    }
}

void RenderArea::nextPoint()
{
    if (m_function != nullptr && m_params != nullptr) {

        m_currentPoint++;
        m_showHighlightPoint = true;

        if (m_currentPoint > m_function->size()) {
            m_currentPoint = m_function->size();
            m_showHighlightPoint = false;
        }
        update();
    }
}

void RenderArea::startPoints(QString secondsString)
{
    bool validSeconds;
    m_seconds =  secondsString.toInt(&validSeconds);
    if (validSeconds) {
        if (m_timer == nullptr) {
            m_timer = new QTimer;
            m_timer->setTimerType(Qt::PreciseTimer);
            connect(m_timer, SIGNAL(timeout()), this, SLOT(timerExpired()));
        }

        m_timer->stop();
        m_timerCount = 0;
        m_secondsElapsed = 0.0;
        m_currentPoint = -1;
        m_showHighlightPoint = true;
        m_timer->start(50);
    }
}

void RenderArea::timerExpired()
{
    m_timerCount++;
    m_secondsElapsed += 50/1000.0;

    int x = round(   ( (double) m_function->size()) / m_seconds * m_secondsElapsed);

    m_currentPoint = x;

    if (m_currentPoint > m_function->size() - 1) {
        m_currentPoint = -1;
        m_timer->stop();
        m_showHighlightPoint = false;
    }
    update();
}
