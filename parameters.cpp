#include "parameters.h"

Parameters::Parameters()
{
    read();
}

Parameters::~Parameters()
{
    write();
}

bool Parameters::showPoints() const
{
    return m_showPoints;
}

void Parameters::setShowPoints(bool showPoints)
{
    m_showPoints = showPoints;
}

bool Parameters::showLine() const
{
    return m_showLine;
}

void Parameters::setShowLine(bool showLine)
{
    m_showLine = showLine;
}

QColor Parameters::pointColor() const
{
    return m_pointColor;
}

void Parameters::setPointColor(const QColor &pointColor)
{
    m_pointColor = pointColor;
}

int Parameters::pointSize() const
{
    return m_pointSize;
}

void Parameters::setPointSize(int pointSize)
{
    m_pointSize = pointSize;
}

QColor Parameters::lineColor() const
{
    return m_lineColor;
}

void Parameters::setLineColor(const QColor &lineColor)
{
    m_lineColor = lineColor;
}

int Parameters::lineWidth() const
{
    return m_lineWidth;
}

void Parameters::setLineWidth(int lineWidth)
{
    m_lineWidth = lineWidth;
}

QColor Parameters::backgroundColor() const
{
    return m_backgroundColor;
}

void Parameters::setBackgroundColor(const QColor &backgroundColor)
{
    m_backgroundColor = backgroundColor;
}

QColor Parameters::highlightColor() const
{
    return m_highlightColor;
}

void Parameters::setHighlightColor(const QColor &highlightColor)
{
    m_highlightColor = highlightColor;
}

int Parameters::highlightSize() const
{
    return m_highlightSize;
}

void Parameters::setHighlightSize(int highlightSize)
{
    m_highlightSize = highlightSize;
}

void Parameters::read()
{
    QSettings settings("audiographs", "audiographs");

    QColor pointColor = settings.value(POINTCOLOR, "").value<QColor>();
    if (!pointColor.isValid())
        pointColor = Qt::blue;

    int pointSize = settings.value("pointSize", 5).toInt();

    QColor lineColor = settings.value("lineColor", "").value<QColor>();
    if (!lineColor.isValid())
        lineColor = Qt::red;

    int lineWidth = settings.value("lineWidth", 1).toInt();

    QColor backgroundColor = settings.value("backgroundColor", "").value<QColor>();
    if (!backgroundColor.isValid())
        backgroundColor = Qt::white;

    QColor highlightColor = settings.value("highlightColor", "").value<QColor>();
    if (!highlightColor.isValid())
        highlightColor = "#00ddff";

    int highlightSize = settings.value("highlightSize", 20).toInt();

    QColor axesColor = settings.value("axesColor", "").value<QColor>();
    if (!axesColor.isValid())
        axesColor = "#000000";

    int axesSize = settings.value("axesSize", 4).toInt();

    bool showPoints = settings.value("showPoints", true).toBool();

    bool showLine = settings.value("showLine", true).toBool();

    bool showAxes = settings.value("showAxes", true).toBool();

    double volume = settings.value("volume", 1.0).toDouble();
    double rate = settings.value("rate", 0.5).toDouble();
    double pitch = settings.value("pitch", 0.5).toDouble();

    int duration = settings.value("duration", 10).toInt();
    int minFreq = settings.value("minFreq", 200).toInt();
    int maxFreq = settings.value("maxFreq", 2000).toInt();

    setPointColor(pointColor);
    setPointSize(pointSize);
    setLineColor(lineColor);
    setLineWidth(lineWidth);
    setBackgroundColor(backgroundColor);
    setHighlightColor(highlightColor);
    setHighlightSize(highlightSize);
    setAxesColor(axesColor);
    setAxesSize(axesSize);
    setShowPoints(showPoints);
    setShowLine(showLine);
    setShowAxes(showAxes);
    setVolume(volume);
    setRate(rate);
    setPitch(pitch);
    setDuration(duration);
    setMinFreq(minFreq);
    setMaxFreq(maxFreq);
}

void Parameters::write()
{
    QSettings settings("audiographs", "audiographs");

    settings.setValue(POINTCOLOR, m_pointColor);
    settings.setValue("pointSize", m_pointSize);
    settings.setValue("lineColor", m_lineColor);
    settings.setValue("lineWidth", m_lineWidth);
    settings.setValue("backgroundColor", m_backgroundColor);
    settings.setValue("highlightColor", m_highlightColor);
    settings.setValue("highlightSize", m_highlightSize);
    settings.setValue("axesColor", m_axesColor);
    settings.setValue("axesSize", m_axesSize);
    settings.setValue("showPoints", m_showPoints);
    settings.setValue("showLine", m_showLine);
    settings.setValue("showAxes", m_showAxes);
    settings.setValue("volume", m_volume);
    settings.setValue("rate", m_rate);
    settings.setValue("pitch", m_pitch);
    settings.setValue("duration", m_duration);
    settings.setValue("minFreq", m_minFreq);
    settings.setValue("maxFreq", m_maxFreq);
}

void Parameters::reset()
{
    setPointColor(Qt::blue);
    setPointSize(5);
    setLineColor(Qt::red);
    setLineWidth(1);
    setBackgroundColor(Qt::white);
    setHighlightColor("#00ddff");
    setHighlightSize(20);
    setAxesColor(Qt::black);
    setAxesSize(4);
    setShowPoints(true);
    setShowLine(true);
    setShowAxes(true);
}

void Parameters::resetAudio()
{
    setDuration(10);
    setMinFreq(200);
    setMaxFreq(2000);
}

QColor Parameters::axesColor() const
{
    return m_axesColor;
}

void Parameters::setAxesColor(const QColor &axesColor)
{
    m_axesColor = axesColor;
}

bool Parameters::showAxes() const
{
    return m_showAxes;
}

void Parameters::setShowAxes(bool showAxes)
{
    m_showAxes = showAxes;
}

int Parameters::axesSize() const
{
    return m_axesSize;
}

void Parameters::setAxesSize(int axesSize)
{
    m_axesSize = axesSize;
}

double Parameters::volume() const
{
    return m_volume;
}

void Parameters::setVolume(double volume)
{
    m_volume = volume;
}

double Parameters::rate() const
{
    return m_rate;
}

void Parameters::setRate(double rate)
{
    m_rate = rate;
}

double Parameters::pitch() const
{
    return m_pitch;
}

void Parameters::setPitch(double pitch)
{
    m_pitch = pitch;
}

int Parameters::duration() const
{
    return m_duration;
}

void Parameters::setDuration(int duration)
{
    m_duration = duration;
}

int Parameters::minFreq() const
{
    return m_minFreq;
}

void Parameters::setMinFreq(int minFreq)
{
    m_minFreq = minFreq;
}

int Parameters::maxFreq() const
{
    return m_maxFreq;
}

void Parameters::setMaxFreq(int maxFreq)
{
    m_maxFreq = maxFreq;
}
