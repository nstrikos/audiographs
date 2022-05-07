#ifndef FUNCTIONEXPRESSION_H
#define FUNCTIONEXPRESSION_H

#include <QObject>

#include "function/functionModel.h"
#include "generator/audio.h"
#include "audionotes/audionotes.h"
#include "parameters.h"
#include "currentPoint.h"
#include "texttospeech.h"
#include "pointInterest/pointInterest.h"

#include "functionHandling/dragHandler.h"
#include "functionHandling/functionZoomer.h"
#include "functionHandling/pinchHandler.h"

class FunctionExpression
{
public:
    FunctionExpression();
    ~FunctionExpression();

private:
    FunctionModel functionModel;
    Audio *m_audio;
    AudioNotes *m_audioNotes;
    Parameters *m_parameters;
    CurrentPoint *m_currentPoint;
    TextToSpeech *m_textToSpeech;
    PointsInterest *m_pointsInterest;
    DragHandler *m_dragHandler;
    FunctionZoomer *m_zoomer;
    PinchHandler *m_pinchHandler;
};

#endif // FUNCTIONEXPRESSION_H
