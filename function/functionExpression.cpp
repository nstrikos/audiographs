#include "function/functionExpression.h"
#include <constants.h>

FunctionExpression::FunctionExpression(QObject *parent) : QObject(parent)
{
    m_audio = new Audio();

    m_audioNotes = new AudioNotes(functionModel);

    m_parameters = &Parameters::getInstance();

    m_textToSpeech = &TextToSpeech::getInstance();

    m_currentPoint = new CurrentPoint(functionModel);    

    m_pointsInterest = new PointsInterest(functionModel);

    m_dragHandler = new DragHandler(functionModel);

    m_zoomer = new FunctionZoomer();
    connect(m_zoomer, &FunctionZoomer::newInputValues, this, &FunctionExpression::newInputValues);

    m_pinchHandler = new PinchHandler();
    connect(m_pinchHandler, &PinchHandler::newInputValues, this, &FunctionExpression::newInputValues);

    audioFinishedRequest = new AudioFinishedRequest();
    updateTextRequest = nullptr;
    setNoteRequest = nullptr;
    audioStartRequest = nullptr;
    stopSoundRequest = nullptr;

    requestHandler = &RequestHandler::getInstance();

    requestHandler->add(this, request_start_pinch);
    requestHandler->add(this, request_pinch);
    requestHandler->add(this, request_zoom);
    requestHandler->add(this, request_first_point);
    requestHandler->add(this, request_last_point);
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

    if (updateTextRequest != nullptr)
        delete updateTextRequest;

    if (setNoteRequest != nullptr)
        delete setNoteRequest;
    if (audioStartRequest != nullptr)
        delete audioStartRequest;
    if (stopSoundRequest != nullptr)
        delete stopSoundRequest;

    delete audioFinishedRequest;
}

void FunctionExpression::accept(Request *request)
{
    if (m_log)
        qDebug() << "FunctionExpression accepted id: " << request->id << " type: " << request->type;
    switch(request->type) {
    case request_start_pinch : startPinch();
        break;
    case request_pinch : pinch(static_cast<PinchRequest*>(request));
        break;
    case request_zoom : zoom(static_cast<ZoomRequest*>(request));
        break;
    case request_first_point: firstPoint();
        break;
    case request_last_point: lastPoint();
        break;
    default:
        break;
    }
}

void FunctionExpression::zoom(ZoomRequest *request)
{
    m_zoomer->zoom(functionModel, request->delta);
}

void FunctionExpression::startPinch()
{
    m_pinchHandler->startPinch(functionModel);
}

void FunctionExpression::pinch(PinchRequest *request)
{
    m_pinchHandler->pinch(functionModel, request->scale);
}

void FunctionExpression::updateText(QString text)
{
    if (updateTextRequest == nullptr)
        updateTextRequest = new UpdateTextRequest();
    updateTextRequest->sender = "FunctionExpression";
    updateTextRequest->text = text;
    requestHandler->handleRequest(updateTextRequest);
}

void FunctionExpression::firstPoint()
{
    if (m_parameters->selfVoice())
        m_textToSpeech->speak(tr("starting point"));
}

void FunctionExpression::lastPoint()
{
    if (m_parameters->selfVoice())
        m_textToSpeech->speak(tr("ending point"));
}

void FunctionExpression::newInputValues(double minX, double maxX, double minY, double maxY)
{
    newInputValuesRequest->sender = "FunctionExpression";
    newInputValuesRequest->minX = minX;
    newInputValuesRequest->maxX = maxX;
    newInputValuesRequest->minY = minY;
    newInputValuesRequest->maxY = maxY;
    requestHandler->handleRequest(newInputValuesRequest);
}

void FunctionExpression::audioFinished()
{
    audioFinishedRequest->sender = "FunctionExpression";
    requestHandler->handleRequest(audioFinishedRequest);
}
