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

#include "requestHandler.h"

class FunctionExpression : public QObject, public RequestReceiver
{
    Q_OBJECT
public:
    explicit FunctionExpression(QObject *parent = nullptr);
    ~FunctionExpression();

    void accept(Request *request);

private slots:
    void newInputValues(double minX, double maxX, double minY, double maxY);
    void audioFinished();

private:
    FunctionModel functionModel;
    NewInputValuesRequest *newInputValuesRequest;
    AudioFinishedRequest *audioFinishedRequest;
    UpdateTextRequest *updateTextRequest;
    SetNoteRequest *setNoteRequest;
    AudioStartRequest *audioStartRequest;
    StopSoundRequest *stopSoundRequest;
    RequestHandler *requestHandler;
    Audio *m_audio;
    AudioNotes *m_audioNotes;
    Parameters *m_parameters;
    CurrentPoint *m_currentPoint;
    TextToSpeech *m_textToSpeech;
    PointsInterest *m_pointsInterest;
    DragHandler *m_dragHandler;
    FunctionZoomer *m_zoomer;
    PinchHandler *m_pinchHandler;

    void startPinch();
    void pinch(PinchRequest *request);
    void zoom(ZoomRequest *request);
    void updateText(QString text);
    void firstPoint();
    void lastPoint();
};

#endif // FUNCTIONEXPRESSION_H
