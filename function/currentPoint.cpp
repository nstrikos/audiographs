#include "currentPoint.h"

#include "constants.h"
#include "functionModel.h"
#include <QDebug>

CurrentPoint::CurrentPoint(FunctionModel &model) : m_model(model)
{
    requestHandler = &RequestHandler::getInstance();
    requestHandler->add(this, request_calculate);
    requestHandler->add(this, request_start_drag);
    requestHandler->add(this, request_zoom);
    requestHandler->add(this, request_start_pinch);
    requestHandler->add(this, request_stop_sound);
    requestHandler->add(this, request_first_point);
    requestHandler->add(this, request_next_point);
    requestHandler->add(this, request_previous_point);
    requestHandler->add(this, request_dec_step);
    requestHandler->add(this, request_inc_step);
    requestHandler->add(this, request_set_point);
    requestHandler->add(this, request_inc_point);
    requestHandler->add(this, request_dec_point);
    requestHandler->add(this, request_last_point);
    requestHandler->add(this, request_audio_start);
    requestHandler->add(this, request_notes_start);
    requestHandler->add(this, request_sayX);
    requestHandler->add(this, request_sayY);
    requestHandler->add(this, request_getX);
    requestHandler->add(this, request_getY);
    requestHandler->add(this, request_update_derivative);
    requestHandler->add(this, request_calculate_second_derivative);
    requestHandler->add(this, request_normal_mode);
    requestHandler->add(this, request_say_derivative);
    requestHandler->add(this, request_get_derivative);

    parameters = &Parameters::getInstance();

    sayTextRequest = nullptr;
    updateTextRequest = nullptr;
    newPointRequest = nullptr;
    drawPointRequest = nullptr;

    timer.setTimerType(Qt::PreciseTimer);
    timer.setInterval(INTERVAL_MILLISECONDS);

    connect(&timer, &QTimer::timeout, this, &CurrentPoint::timerExpired);

    m_point = 0;
    m_step = 10;
}

CurrentPoint::~CurrentPoint()
{
    if (sayTextRequest != nullptr)
        delete sayTextRequest;
    if (updateTextRequest != nullptr)
        delete updateTextRequest;
    if (newPointRequest != nullptr)
        delete newPointRequest;
    if (drawPointRequest != nullptr)
        delete drawPointRequest;
}

void CurrentPoint::accept(Request *request)
{
    if (m_log)
        qDebug() << "CurrentPoint accepted id: " << request->id << " type: " << request->type;
    switch(request->type) {
    case request_calculate :
    case request_start_drag:
    case request_zoom:
    case request_start_pinch:
        reset();
        break;
    case request_audio_start:
    case request_notes_start:
        startMoving();
        break;
    case request_stop_sound:
        stop();
        break;
    case request_first_point:
        reset();
        break;
    case request_next_point:
        next();
        break;
    case request_previous_point:
        previous();
        break;
    case request_dec_step:
        decStep();
        break;
    case request_inc_step:
        incStep();
        break;
    case request_set_point:
        setPoint(static_cast<SetPointRequest*>(request)->point);
        break;
    case request_inc_point:
        incPoint(static_cast<IncPointRequest*>(request)->step);
        break;
    case request_dec_point:
        decPoint(static_cast<DecPointRequest*>(request)->step);
        break;
    case request_last_point:
        endPoint();
        break;
    case request_sayX:
        sayX();
        break;
    case request_sayY:
        sayY();
        break;
    case request_getX:
        getX();
        break;
    case request_getY:
        getY();
        break;
    case request_update_derivative:
    case request_normal_mode:
        drawPoint();
        break;
    case request_say_derivative:
        sayDerivative();
        break;
    case request_get_derivative:
        getDerivative();
        break;
    default:
        break;
    }
}

void CurrentPoint::startMoving()
{
    m_duration = parameters->duration() * 1000;
    setPoint(0);
    m_timeElapsed = 0;
    timer.start();
}

void CurrentPoint::timerExpired()
{
    m_timeElapsed += timer.interval();
    if (m_timeElapsed >= m_duration) {
        timer.stop();
        setPoint(0);
        return;
    }

    double cx = (double) m_timeElapsed / m_duration;
    m_point = round(cx * LINE_POINTS);
    if (m_point >= LINE_POINTS)
        setPoint(LINE_POINTS - 1);
    else if (m_point < 0)
        setPoint(0);
    else
        setPoint(m_point);
}

void CurrentPoint::setPoint(int point)
{
    if (point < 0)
        return;

    if (point >= m_model.size())
        return;

    m_point = point;


    if (newPointRequest == nullptr)
        newPointRequest = new NewPointRequest();
    newPointRequest->sender = "Currentpoint";
    newPointRequest->point = m_point;
    requestHandler->handleRequest(newPointRequest);

    drawPoint();
}

void CurrentPoint::incPoint(int step)
{
    m_point += step;

    if (m_point >= LINE_POINTS)
        m_point = LINE_POINTS - 1;

    setPoint(m_point);
}

void CurrentPoint::decPoint(int step)
{
    m_point -= step;

    if (m_point <= 0)
        m_point = 0;

    setPoint(m_point);
}

void CurrentPoint::endPoint()
{
    timer.stop();

    if (m_model.size() > 0) {
        m_point = m_model.size() - 1;
        setPoint(m_point);
    }
}

void CurrentPoint::drawPoint()
{
    m_X = m_model.x(m_point);
    m_Y = m_model.y(m_point);

    if (drawPointRequest == nullptr)
        drawPointRequest = new DrawPointRequest();
    drawPointRequest->sender = "CurrentPoint";
    drawPointRequest->x = m_X;
    drawPointRequest->y = m_Y;
    requestHandler->handleRequest(drawPointRequest);
}

void CurrentPoint::sayX()
{
    double x = m_model.x(m_point);

    double Pow = pow(10.0, parameters->precisionDigits());
    x = round (x * Pow) / Pow;

    char c = 'f';
    QString value = QString::number(x, c, parameters->precisionDigits());
    sayText(value);
}

void CurrentPoint::sayY()
{
    if (m_model.isValid(m_point)) {
        double y = m_model.y(m_point);

        double Pow = pow(10.0, parameters->precisionDigits());
        y = round (y * Pow) / Pow;

        char c = 'f';
        QString value = QString::number(y, c, parameters->precisionDigits());
        sayText(value);
    } else {
        sayText(tr("Not defined"));
    }
}

void CurrentPoint::getX()
{
    double x = m_model.x(m_point);

    double Pow = pow(10.0, parameters->precisionDigits());
    x = round (x * Pow) / Pow;

    char c = 'f';
    QString value = QString::number(x, c, parameters->precisionDigits());
    updateText(value);
}

void CurrentPoint::getY()
{
    if (m_model.isValid(m_point)) {
        double y = m_model.y(m_point);

        double Pow = pow(10.0, parameters->precisionDigits());
        y = round (y * Pow) / Pow;

        char c = 'f';
        QString value = QString::number(y, c, parameters->precisionDigits());
        updateText(value);
    } else {
        updateText(tr("Not defined"));
    }
}

void CurrentPoint::sayDerivative()
{
    if (m_model.isValid(m_point)) {

        double y = m_model.derivative(m_point);

        double Pow = pow(10.0, parameters->precisionDigits());
        y = round (y * Pow) / Pow;

        char c = 'f';
        QString value = QString::number(y, c, parameters->precisionDigits());
        sayText(value);
    } else {
        sayText(tr("Not defined"));
    }
}

void CurrentPoint::getDerivative()
{
    if (m_model.isValid(m_point)) {

        double y = m_model.derivative(m_point);

        double Pow = pow(10.0, parameters->precisionDigits());
        y = round (y * Pow) / Pow;

        char c = 'f';
        QString value = QString::number(y, c, parameters->precisionDigits());
        updateText(value);
    } else {
        updateText(tr("Not defined"));
    }
}

void CurrentPoint::stop()
{
    timer.stop();
}

void CurrentPoint::reset()
{
    timer.stop();
    setPoint(0);
}

void CurrentPoint::next()
{
    m_point += m_step;
    if (m_point >= LINE_POINTS)
        m_point = LINE_POINTS - 1;

    setPoint(m_point);
}

void CurrentPoint::previous()
{
    m_point -= m_step;
    if (m_point < 0)
        m_point = 0;

    setPoint(m_point);
}

void CurrentPoint::decStep()
{
    m_step -= 10;
    m_step = round(m_step);
    if (m_step < 1)
        m_step = 1;

    double realStep = (double) m_step / m_model.size() * (m_model.maxX() - m_model.minX());
    QString text = tr("Step is ") + QString::number(realStep);

    updateText(text);
    sayText(text);
}

void CurrentPoint::incStep()
{
    if (m_step == 1)
        m_step = 0;

    m_step += 10;
    m_step = round(m_step);
    if (m_step > 100)
        m_step = 100;

    double realStep = (double) m_step / m_model.size() * (m_model.maxX() - m_model.minX());
    QString text = tr("Step is ") + QString::number(realStep);

    updateText(text);
    sayText(text);
}

void CurrentPoint::sayText(QString text)
{
    if (sayTextRequest == nullptr)
        sayTextRequest = new SayTextRequest();
    sayTextRequest->sender = "CurrentPoint";
    sayTextRequest->text = text;
    requestHandler->handleRequest(sayTextRequest);
}

void CurrentPoint::updateText(QString text)
{
    if (updateTextRequest == nullptr)
        updateTextRequest = new UpdateTextRequest();
    updateTextRequest->sender = "CurrentPoint";
    updateTextRequest->text = text;
    requestHandler->handleRequest(updateTextRequest);
}
