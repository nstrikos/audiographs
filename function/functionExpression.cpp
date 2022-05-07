#include "function/functionExpression.h"
#include <constants.h>

FunctionExpression::FunctionExpression()
{
    m_audio = new Audio();

    m_audioNotes = new AudioNotes(functionModel);

    m_parameters = &Parameters::getInstance();

    m_textToSpeech = &TextToSpeech::getInstance();

    m_currentPoint = new CurrentPoint(functionModel);

    m_pointsInterest = new PointsInterest(functionModel);

    m_dragHandler = new DragHandler(functionModel);

    m_zoomer = new FunctionZoomer(functionModel);

    m_pinchHandler = new PinchHandler(functionModel);
}

FunctionExpression::~FunctionExpression()
{
    delete m_audio;
    delete m_audioNotes;
    delete m_currentPoint;
    delete m_pointsInterest;
    delete m_dragHandler;
    delete m_zoomer;
    delete m_pinchHandler;
}
