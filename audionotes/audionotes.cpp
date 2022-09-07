#include "audionotes.h"
#include "math.h"
#include "constants.h"

#include "ifaces/IAudioNotes.h"

AudioNotes::AudioNotes(IAudioNotes &iface, FunctionModel &model) :
    iface(iface),
    m_model(model)
{
    iface.addAudionotes(this);

    m_timer.setTimerType(Qt::PreciseTimer);
    m_timer.setInterval(INTERVAL_MILLISECONDS);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(timerExpired()));

    m_audioPoints = new AudioPoints();
}

AudioNotes::~AudioNotes()
{
    delete m_audioPoints;
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

void AudioNotes::setNoteFromMouse(int mouseX, int width, int fmin, int fmax, bool useNotes)
{
    m_mouseX = mouseX;
    m_fmin = fmin;
    m_fmax = fmax;

    if (m_mouseX < 0)
        m_mouseX = 0;
    if (m_mouseX > width)
        m_mouseX = width;

    double ratio = (double) m_mouseX / width;

    int i = round((1.0 * m_mouseX / width) * LINE_POINTS);
    if (i < 0)
        i = 0;
    if (i >= LINE_POINTS)
        i = LINE_POINTS - 1;

    double min = m_model.minValue();
    double max = m_model.maxValue();

    if (max > m_model.maxY())
        max = m_model.maxY();
    if (min < m_model.minY())
        min = m_model.minY();

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
        if (!std::signbit(l))
            n = true;
        else
            n = false;
        freq = a * l + b;

        if (freq > m_fmax)
            freq = m_fmax;
        if (freq < m_fmin)
            freq = m_fmin;

        if (useNotes) {

            if (m_model.isValidAt(i))
                m_audioPoints->setFreq(freq, n, ratio);
            else
                m_audioPoints->setFreq(0, n, ratio);
        } else {
            m_audioPoints->setFreq((m_fmax - m_fmin) / 2, n, ratio);
        }
    }
}

void AudioNotes::setNote(int currentPoint, int fmin, int fmax, bool useNegativeNotes)
{
    m_fmin = fmin;
    m_fmax = fmax;
    m_currentPoint = currentPoint;

    if (m_currentPoint < 0)
        m_currentPoint = 0;
    if (m_currentPoint >= LINE_POINTS)
        m_currentPoint = LINE_POINTS - 1;

    double min = m_model.minValue();
    double max = m_model.maxValue();

    if (max > m_model.maxY())
        max = m_model.maxY();
    if (min < m_model.minY())
        min = m_model.minY();


    double ratio = (double) m_currentPoint / LINE_POINTS;


    //Frequency has a linear dependance to the value of the function
    //freq is the frequency
    //l is the value of the function
    //we need to calculate a and b and finally freq with freq = a * l + b
    //When l is min then freq is fmin
    //When l is max then freq is fmax
    //Solving the equations we get:
    //a = (m_fmax - m_fmin) / (max - min) and
    //b = m_fmax - a * max;

    double a;
    double b;
    double l;
    double freq;
    bool n = true;

    //We are not in a straight line
    if ( abs(max - min) > 1e-8) {
        a = (m_fmax - m_fmin) / (max - min);
        b = m_fmax - a * max;
        l = m_model.y(m_currentPoint);

        if (useNegativeNotes) {
            if (!std::signbit(l)) //The best way to see if l is positive or negative
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

        if (m_model.isValidAt(m_currentPoint))
            m_audioPoints->setFreq(freq, n, ratio);
        else
            m_audioPoints->setFreq(0, n, ratio); //Zero frequency when the function is not defined
    } else {
        //We are in a straight line
        m_audioPoints->setFreq((m_fmax - m_fmin) / 2, n, ratio);
    }
}

void AudioNotes::stopNotes()
{
    m_timer.stop();
    m_audioPoints->stopAudio();
}

void AudioNotes::timerExpired()
{
    //Calculate the time, calculate the position, set note depending on position
    m_timeElapsed += m_timer.interval();
    if (m_timeElapsed > m_duration) {
        stopNotes();
        iface.audioNotesFinished();
        return;
    }

    double cx = (double) m_timeElapsed / m_duration;
    m_currentPoint = round(cx * LINE_POINTS);
    setNote(m_currentPoint, m_fmin, m_fmax, m_useNegativeNotes);
}
