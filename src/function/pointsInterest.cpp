#include "pointsInterest.h"
#include "../ifaces/IPointsInterest.h"

#include "math.h"

PointsInterest::PointsInterest(IPointsInterest &iface,
                               FunctionModel &functionModel,
                               AudioNotes &audioNotes,
                               CurrentPoint &currentPoint):
    iface(iface),
    m_model(functionModel),
    m_audioNotes(audioNotes),
    m_currentPoint(currentPoint)
{
    iface.addPointsInterest(this);

    m_funcDescription = nullptr;
    m_pointInterest = 0;
    m_forward = true;
    m_isUpdated = false;

    m_timer.setTimerType(Qt::PreciseTimer);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(timerExpired()));
    m_step = 1;
    m_timerInterVal = 40;
    stepCandidates.append(1);
    stepCandidates.append(2);
    stepCandidates.append(3);
    stepCandidates.append(4);
    stepCandidates.append(5);
    stepCandidates.append(10);
    stepCandidates.append(15);
    stepCandidates.append(20);
    stepCandidates.append(25);

    m_parameters = &Parameters::getInstance();
    m_textToSpeech = &TextToSpeech::getInstance();
}

PointsInterest::~PointsInterest()
{
    m_timer.stop();
    m_audioNotes.stopNotes();
    if (m_funcDescription != nullptr)
        delete m_funcDescription;
}

void PointsInterest::init()
{
    m_interestingPoints.clear();

    if (m_funcDescription == nullptr)
        m_funcDescription = new FunctionDescription(m_model);

    m_interestingPoints = m_funcDescription->points(m_parameters->stopAtZero());
    m_isUpdated = true;
}

void PointsInterest::nextPoint()
{
    m_forward = true;
    start();
}

void PointsInterest::previousPoint()
{
    m_forward = false;
    start();
}

void PointsInterest::start()
{
    if (m_isUpdated == false)
        init();

    m_pointInterest = getNextPointInterest();
    setStep();

    m_timer.setInterval(m_timerInterVal);
    m_timer.start();
}

int PointsInterest::getNextPointInterest()
{
    int point = 0;
    if (m_forward == true) {
        for (int i = 0; i < m_interestingPoints.size(); i++) {
            if (m_interestingPoints.at(i).x < m_currentPoint.point()) {
                continue;
            } else if (m_interestingPoints.at(i).x == m_currentPoint.point()) {
                point = i + 1;
                break;
            }
            else {
                point = i;
                break;
            }
        }
    } else {
        for (int i = m_interestingPoints.size() - 1; i >= 0; i--) {
            if (m_interestingPoints.at(i).x > m_currentPoint.point()) {
                continue;
            } else if (m_interestingPoints.at(i).x == m_currentPoint.point()) {
                point = i - 1;
                break;
            }
            else {
                point = i;
                break;
            }
        }
    }

    if (point >= m_interestingPoints.size())
        point = m_interestingPoints.size() - 1;

    if (point < 0)
        point = 0;

    return point;
}

void PointsInterest::nextPointFast()
{
    if (m_isUpdated == false)
        init();

    m_forward = true;
    m_pointInterest = getNextPointInterest();
    m_currentPoint.setPoint(m_interestingPoints[m_pointInterest].x);
    QString label = currentPointLabel();
    m_textToSpeech->speak(label);
    iface.updateLabel(label);
}

void PointsInterest::previousPointFast()
{
    if (m_isUpdated == false)
        init();

    m_forward = false;
    m_pointInterest = getNextPointInterest();
    m_currentPoint.setPoint(m_interestingPoints[m_pointInterest].x);
    QString label = currentPointLabel();
    m_textToSpeech->speak(label);
    iface.updateLabel(label);
}

void PointsInterest::setStep()
{
    //Try to find the best step to fit the duration
    //Current point waits at every point for m_timerInterval
    //So the total time is size / n * m_timerInterval
    //size - model size
    //n - step
    //Duration selected by user is m_parameters->duration * 1000
    //The best step is the step that minimizes the difference abs(duration - time)
    //For simplicity we set step candidates 0,1,2,3,4,5,10,15,20,25


    long long int duration = m_parameters->duration() * 1000;
    long int diff;
    long int time;
    long int minDiff;
    int step;
    int size = m_model.size();

    minDiff = 120000; //maximum possible value;

    for (int i = 0; i < stepCandidates.size(); i++) {
        int n = stepCandidates.at(i);
        time = size / n * m_timerInterVal;
        diff = abs(duration - time);
        if (diff < minDiff) {
            minDiff = diff;
            step = n;
            m_step = step;
        }
    }
}

int PointsInterest::util(int i, int size, int n, int timerInterval)
{
    int d = size / n  * timerInterval;
    return abs(i - d);
}

void PointsInterest::stop()
{
    m_timer.stop();
    m_audioNotes.stopNotes();
}

void PointsInterest::notUpdated()
{
    m_isUpdated = false;
}

void PointsInterest::timerExpired()
{
    Parameters *parameters = &Parameters::getInstance();

    if (m_forward) {
        m_currentPoint.incPoint(m_step);
        if (m_currentPoint.point() >= m_interestingPoints[m_pointInterest].x)
            update();
        else
            m_audioNotes.setNote(m_currentPoint.point(), parameters->minFreq(), parameters->maxFreq(), m_parameters->useNegativeNotes());
    } else {
        m_currentPoint.decPoint(m_step);
        if (m_currentPoint.point() <= m_interestingPoints[m_pointInterest].x)
            update();
        else
            m_audioNotes.setNote(m_currentPoint.point(), parameters->minFreq(), parameters->maxFreq(), m_parameters->useNegativeNotes());
    }
}

void PointsInterest::update()
{
    m_currentPoint.setPoint(m_interestingPoints[m_pointInterest].x);
    m_timer.stop();
    QString label = currentPointLabel();
    m_textToSpeech->speak(label);
    iface.updateLabel(label);
    iface.interestingPointsfinished();
}

QString PointsInterest::currentPointLabel()
{
    return m_interestingPoints[m_pointInterest].label;
}
