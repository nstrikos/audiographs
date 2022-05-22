#include "pointInterest.h"

#include <QDebug>

#include "math.h"

PointsInterest::PointsInterest(FunctionModel &functionModel) : m_model(functionModel)
{
    m_funcDescription = nullptr;
    m_pointInterest = 0;
    m_forward = true;
    m_isUpdated = false;
    m_timer.setTimerType(Qt::PreciseTimer);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(timerExpired()));

    m_parameters = &Parameters::getInstance();
    requestHandler = &RequestHandler::getInstance();
    requestHandler->add(this, request_calculate);
    requestHandler->add(this, request_new_point);
    requestHandler->add(this, request_zoom);
    requestHandler->add(this, request_start_drag);
    requestHandler->add(this, request_next_point_interest);
    requestHandler->add(this, request_previous_point_interest);
    requestHandler->add(this, request_next_fast);
    requestHandler->add(this, request_previous_fast);
    requestHandler->add(this, request_stop_sound);
    requestHandler->add(this, request_calculate_derivative);
    requestHandler->add(this, request_calculate_second_derivative);
    requestHandler->add(this, request_normal_mode);
    setPointRequest = nullptr;
    incPointRequest = nullptr;
    decPointRequest = nullptr;
    interestingPointFinishedRequest = nullptr;
    updateTextRequest = nullptr;
    setNoteRequest = nullptr;
    stopNotesRequest = nullptr;
    sayTextRequest = nullptr;
}

PointsInterest::~PointsInterest()
{
    if (m_funcDescription != nullptr)
        delete m_funcDescription;
    if (setPointRequest != nullptr)
        delete setPointRequest;
    if (incPointRequest != nullptr)
        delete incPointRequest;
    if (decPointRequest != nullptr)
        delete decPointRequest;
    if (interestingPointFinishedRequest != nullptr)
        delete interestingPointFinishedRequest;
    if (updateTextRequest != nullptr)
        delete updateTextRequest;
    if (setNoteRequest != nullptr)
        delete setNoteRequest;
    if (stopNotesRequest != nullptr)
        delete stopNotesRequest;
    if (sayTextRequest != nullptr)
        delete sayTextRequest;
}

void PointsInterest::accept(Request *request)
{
    if (m_log)
        qDebug() << "PointsInterest used id: " << request->id << " type: " << request->description;
    switch(request->type) {
    case request_calculate:
    case request_start_drag:
    case request_zoom:
        setUpdated(0);
        break;
    case request_new_point : m_curPoint = (static_cast<NewPointRequest*>(request)->point);
        break;
    case request_next_point_interest: nextPoint();
        break;
    case request_previous_point_interest: previousPoint();
        break;
    case request_next_fast: nextPointFast();
        break;
    case request_previous_fast: previousPointFast();
        break;
    case request_stop_sound : stop();
        break;
    case request_calculate_derivative:
        setUpdated(1);
        break;
    case request_calculate_second_derivative:
        setUpdated(2);
        m_derivativeMode = 2;
        break;
    case request_normal_mode:
        setUpdated(0);
        break;
    default:
        break;
    }
}

void PointsInterest::nextPoint()
{
    if (m_model.size() == 0)
        return;

    m_forward = true;
    start();
}

void PointsInterest::previousPoint()
{
    if (m_model.size() == 0)
        return;

    m_forward = false;
    start();
}

void PointsInterest::nextPointFast()
{
    if (m_model.size() == 0)
        return;

    if (m_funcDescription == nullptr)
        m_funcDescription = new FunctionDescription(m_model);


    if (m_isUpdated == false) {
        m_points.clear();
        m_points = m_funcDescription->points(m_derivativeMode);
        m_isUpdated = true;
    }

    m_forward = true;
    m_pointInterest = getNextPointInterest();

    sendNewPoint(m_points[m_pointInterest].x);

    QString label = currentPointLabel();
    sayText(label);
    updateLabel(label);
}

void PointsInterest::previousPointFast()
{

    if (m_model.size() == 0)
        return;
    if (m_funcDescription == nullptr)
        m_funcDescription = new FunctionDescription(m_model);


    if (m_isUpdated == false) {
        m_points.clear();
        m_points = m_funcDescription->points(m_derivativeMode);
        m_isUpdated = true;
    }

    m_forward = false;
    m_pointInterest = getNextPointInterest();

    sendNewPoint(m_points[m_pointInterest].x);

    QString label = currentPointLabel();
    sayText(label);
    updateLabel(label);
}

void PointsInterest::start()
{
    if (m_funcDescription == nullptr)
        m_funcDescription = new FunctionDescription(m_model);


    if (m_isUpdated == false) {
        m_points.clear();
        m_points = m_funcDescription->points(m_derivativeMode);
        m_isUpdated = true;
    }

    m_pointInterest = getNextPointInterest();

    m_step = getStep();

    m_timer.setInterval(m_timerInterVal);
    m_timer.start();
}

int PointsInterest::getNextPointInterest()
{
    int point = 0;
    if (m_forward == true) {
        for (int i = 0; i < m_points.size(); i++) {
            if (m_points.at(i).x < m_curPoint) {
                continue;
            } else if ((m_points.at(i).x == m_curPoint)) {
                point = i + 1;
                break;
            }
            else {
                point = i;
                break;
            }
        }
    } else {
        for (int i = m_points.size() - 1; i >= 0; i--) {
            if (m_points.at(i).x > m_curPoint) {
                continue;
            } else if (m_points.at(i).x == m_curPoint) {
                point = i - 1;
                break;
            }
            else {
                point = i;
                break;
            }
        }
    }

    if (point >= m_points.size())
        point = m_points.size() - 1;

    if (point < 0)
        point = 0;

    return point;
}

int PointsInterest::getStep()
{
    long long int i = m_parameters->duration() * 1000;

    long int diff;

    long int d;

    long int min;
    int step;

    int n = 1;

    int size = m_model.size();
    d = size / n * m_timerInterVal;
    diff = abs(i - d);
    min = diff;
    step = n;

    n = 2;

    d = size / n * m_timerInterVal;
    diff = abs(i-d);

    if (diff < min) {
        min = diff;
        step = n;
    }

    n = 4;

    d = size / n * m_timerInterVal;
    diff = abs(i-d);

    if (diff < min) {
        min = diff;
        step = n;
    }

    n = 5;
    d = size / n * m_timerInterVal;
    diff = abs(i-d);

    if (diff < min) {
        min = diff;
        step = n;
    }

    n = 10;

    d = size / n * m_timerInterVal;
    diff = abs(i-d);

    if (diff < min) {
        min = diff;
        step = n;
    }

    n = 20;

    d = size / n * m_timerInterVal;
    diff = abs(i-d);

    if (diff < min) {
        min = diff;
        step = n;
    }

    n = 25;

    d = size / n * m_timerInterVal;
    diff = abs(i-d);

    if (diff < min) {
        step = n;
    }

    return step;
}

void PointsInterest::stop()
{
    if (m_timer.isActive()) {
        m_timer.stop();
        if (stopNotesRequest == nullptr)
            stopNotesRequest = new StopNotesRequest();
        stopNotesRequest->sender = "PointsInterest";
        requestHandler->handleRequest(stopNotesRequest);
    }
}

void PointsInterest::setUpdated(int mode)
{
    m_isUpdated = false;
    m_derivativeMode = mode;
}

void PointsInterest::finished()
{
    if (interestingPointFinishedRequest == nullptr)
        interestingPointFinishedRequest = new InterestingPointFinishedRequest();
    interestingPointFinishedRequest->sender = "PointsInterest";
    requestHandler->handleRequest(interestingPointFinishedRequest);
}

void PointsInterest::updateLabel(QString text)
{
    if (updateTextRequest == nullptr)
        updateTextRequest = new UpdateTextRequest();
    updateTextRequest->sender = "PointsInterest";
    updateTextRequest->text = text;
    requestHandler->handleRequest(updateTextRequest);
}

void PointsInterest::sendNoteRequest(int fmin, int fmax, bool useNotes, bool useNegativeNotes)
{
    if (setNoteRequest == nullptr)
        setNoteRequest = new SetNoteRequest();
    setNoteRequest->sender = "PointsInterest";
    setNoteRequest->fmin = fmin;
    setNoteRequest->fmax = fmax;
    setNoteRequest->useNotes = useNotes;
    setNoteRequest->useNegativeNotes = useNegativeNotes;
    requestHandler->handleRequest(setNoteRequest);
}

void PointsInterest::sayText(QString text)
{
    if (sayTextRequest == nullptr)
        sayTextRequest = new SayTextRequest();
    sayTextRequest->sender = "PointsInterest";
    sayTextRequest->text = text;
    requestHandler->handleRequest(sayTextRequest);
}

void PointsInterest::timerExpired()
{
    Parameters *parameters = &Parameters::getInstance();

    if (m_forward) {

        if (incPointRequest == nullptr)
            incPointRequest = new IncPointRequest();
        incPointRequest->sender = "PointsInterest";
        incPointRequest->step = m_step;
        requestHandler->handleRequest(incPointRequest);


        if (m_curPoint >= m_points[m_pointInterest].x) {
            sendNewPoint(m_points[m_pointInterest].x);
            m_timer.stop();
            QString label = currentPointLabel();
            sayText(label);
            updateLabel(label);
            finished();
        } else {
            sendNoteRequest(parameters->minFreq(), parameters->maxFreq(), parameters->useNotes(), m_parameters->useNegativeNotes());
        }
    } else {

        if (decPointRequest == nullptr)
            decPointRequest = new DecPointRequest();
        decPointRequest->sender = "PointsInterest";
        decPointRequest->step = m_step;
        requestHandler->handleRequest(decPointRequest);


        if (m_curPoint <= m_points[m_pointInterest].x) {
            sendNewPoint(m_points[m_pointInterest].x);
            m_timer.stop();
            QString label = currentPointLabel();
            sayText(label);
            updateLabel(label);
            finished();
        } else {
            sendNoteRequest( parameters->minFreq(), parameters->maxFreq(), parameters->useNotes(), m_parameters->useNegativeNotes());
        }
    }
}

void PointsInterest::sendNewPoint(int point)
{
    if (setPointRequest == nullptr)
        setPointRequest = new SetPointRequest();
    setPointRequest->sender = "PointsInterest";
    setPointRequest->point = point;
    requestHandler->handleRequest(setPointRequest);
}

QString PointsInterest::currentPointLabel()
{
    return m_points[m_pointInterest].label;
}
