#include "audionotes.h"
#include "math.h"
#include "constants.h"

#include <QDebug>

AudioNotes::AudioNotes(FunctionModel &model) : m_model(model)
{
    m_timer.setTimerType(Qt::PreciseTimer);
    m_timer.setInterval(INTERVAL_MILLISECONDS);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(timerExpired()));
    m_audioPoints = new AudioPoints();

    audioFinishedRequest = nullptr;

    requestHandler = &RequestHandler::getInstance();
    requestHandler->add(this, request_notes_start);
    requestHandler->add(this, request_set_note);
    requestHandler->add(this, request_stop_sound);
    requestHandler->add(this, request_stop_notes);
    requestHandler->add(this, request_new_point);
}

AudioNotes::~AudioNotes()
{
    delete m_audioPoints;
    if (audioFinishedRequest != nullptr)
        delete audioFinishedRequest;
}

void AudioNotes::accept(Request *request)
{
    if (m_log)
        qDebug() << "Audionotes used id: " << request->id << " type: " << request->description;

    if (request->type == request_notes_start) {
        int fmin = static_cast<NotesStartRequest*>(request)->fmin;
        int fmax = static_cast<NotesStartRequest*>(request)->fmax;
        int duration = static_cast<NotesStartRequest*>(request)->duration;
        bool useNegativeNotes = static_cast<NotesStartRequest*>(request)->useNegativeNotes;
        startNotes(fmin, fmax, duration, useNegativeNotes);
    }
    else if (request->type == request_set_note) {
        int fmin = static_cast<SetNoteRequest*>(request)->fmin;
        int fmax = static_cast<SetNoteRequest*>(request)->fmax;
        bool useNotes = static_cast<SetNoteRequest*>(request)->useNotes;
        bool useNegativeNotes = static_cast<SetNoteRequest*>(request)->useNegativeNotes;
        setNote(fmin, fmax, useNotes, useNegativeNotes);
    } else if (request->type == request_stop_notes) {
        stopNotes();
    } else if (request->type == request_stop_sound) {
        stopNotes();
    } else if (request->type == request_new_point) {
        setPoint(static_cast<NewPointRequest*>(request)->point);
    }
}

void AudioNotes::startNotes(int fmin,
                            int fmax,
                            int duration,
                            bool useNegativeNotes)
{
    m_fmin = fmin;
    m_fmax = fmax;
    m_duration = duration * 1000;
    m_useNegativeNotes = useNegativeNotes;
    m_timeElapsed = 0;
    m_timer.start();
}

void AudioNotes::setPoint(int point)
{
    m_currentPoint = point;

    if (m_currentPoint < 0)
        m_currentPoint = 0;
    if (m_currentPoint >= LINE_POINTS)
        m_currentPoint = LINE_POINTS - 1;
}

void AudioNotes::setNote(int fmin, int fmax, bool useNotes, bool useNegativeNotes)
{
    m_fmin = fmin;
    m_fmax = fmax;

    double min = m_model.minValue();
    double max = m_model.maxValue();

    if (max > 1 * m_model.maxY())
        max = 1 * m_model.maxY();
    if (min < 1 * m_model.minY())
        min = 1 * m_model.minY();


    double ratio = (double) m_currentPoint / LINE_POINTS;

    double a;
    double b;
    double l;
    double freq;
    bool n = true;
    if ( abs(max - min) > 1e-8) {
        m_fmin = 110;
        m_fmax = 880;
        a =  (m_fmax-m_fmin)/(max - min);
        b = m_fmax - a * max;
        l = m_model.y(m_currentPoint);

        if (useNegativeNotes) {
            if (!std::signbit(l))
                n = true;
            else
                n = false;
        } else {
            n = true;
        }
        freq = a * l + b;

        if (freq > m_fmax)
            freq = m_fmax;
        if (freq < m_fmin)
            freq = m_fmin;

        if (m_model.isValid(m_currentPoint))
            m_audioPoints->setFreq(freq, useNotes, n, ratio);
        else
            m_audioPoints->setFreq(0, useNotes, n, ratio);
    } else {
        m_audioPoints->setFreq((m_fmax - m_fmin) / 2, useNotes, n, ratio);
    }
}

void AudioNotes::stopNotes()
{
    m_timer.stop();
    m_audioPoints->stopAudio();
}

void AudioNotes::timerExpired()
{
    m_timeElapsed += m_timer.interval();
    if (m_timeElapsed > m_duration) {
        stopNotes();

        if (audioFinishedRequest == nullptr)
            audioFinishedRequest = new AudioFinishedRequest();
        audioFinishedRequest->sender = "Audionotes";
        requestHandler->handleRequest(audioFinishedRequest);

        return;
    }

    double cx = (double) m_timeElapsed / m_duration;
    int i = round(cx * LINE_POINTS);
    if (i >= LINE_POINTS)
        i = LINE_POINTS - 1;
    if (i < 0)
        i = 0;

    double min = m_model.minValue();
    double max = m_model.maxValue();

    if (max > 1 * m_model.maxY())
        max = 1 * m_model.maxY();
    if (min < 1 * m_model.minY())
        min = 1 * m_model.minY();

    double a;
    double b;
    double l;
    double freq;
    bool n = true;
    if ( abs(max - min) > 1e-8) {
        m_fmin = 110;
        m_fmax = 880;
        a =  (m_fmax-m_fmin)/(max - min);
        b = m_fmax - a * max;
        l = m_model.y(i);

        if (m_useNegativeNotes) {
            if (!std::signbit(l))
                n = true;
            else
                n = false;
        } else {
            n = true;
        }
        freq = a * l + b;
        if (freq < m_fmin)
            freq = m_fmin;
        if (freq > m_fmax)
            freq = m_fmax;

        if (m_model.isValid(i))
            m_audioPoints->setFreq(freq, true, n, cx);
        else
            m_audioPoints->setFreq(0, true, n, cx);
    } else {
        m_audioPoints->setFreq((m_fmax + m_fmin) / 2, true, n, cx);
    }
}
