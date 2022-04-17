#ifndef REQUESTS_H
#define REQUESTS_H

#include "function/point.h"
#include <QVector>
#include <QString>

enum request_type
{
    request_calculate = 0,
    request_update = 1,
    request_error = 2,
    request_new_values = 3,
    request_start_drag = 4,
    request_drag = 5,
    request_start_pinch = 6,
    request_pinch = 7,
    request_zoom = 8,
    request_update_derivative = 9,
    request_play_sound = 10,
    request_stop_sound = 11,
    request_audio_finished = 12,
    request_draw_point = 13,
    request_previous_point = 14,
    request_next_point = 15,
    request_sayX = 16,
    request_sayY = 17,
    request_getX = 18,
    request_getY = 19,
    request_update_text = 20,
    request_say_derivative = 21,
    request_get_derivative = 22,
    request_inc_step = 23,
    request_dec_step = 24,
    request_interesting_point_finished = 25,
    request_previous_point_interest = 26,
    request_next_point_interest = 27,
    request_previous_fast = 28,
    request_next_fast = 29,
    request_first_point = 30,
    request_last_point = 31,
    request_set_derivative = 32,
    request_say_text = 33,
    request_new_point = 34,
    request_set_point = 35,
    request_inc_point = 36,
    request_dec_point = 37,
    request_set_note = 38,
    request_stop_notes = 39,
    request_audio_start = 40,
    request_notes_start = 41
};

class Request
{
public:
    request_type type;
    QString sender;
    int id;
};

class RequestReceiver
{
public:
    virtual void accept(Request *request) = 0;
    void setLog(bool log);

protected:
    bool m_log = false;
};

class RequestHandler
{
public:
    static RequestHandler& getInstance()
    {
        static RequestHandler instance;
        return instance;
    }

    void add(RequestReceiver *getter, request_type type);
    void handleRequest(Request *request);
    void setLog(bool log);

    bool log() const;

private:
    RequestHandler() { }
    RequestHandler(RequestHandler const&);     // Don't Implement
    void operator=(RequestHandler const&); // Don't implement
    QVector<RequestReceiver*> receivers[100];
    int request_id = 0;
private:
    bool m_log = false;
};

class CalculateRequest : public Request
{
public:
    CalculateRequest();
    QString expression;
    QString minX;
    QString maxX;
    QString minY;
    QString maxY;
};

class UpdateRequest : public Request
{
public:
    UpdateRequest();
    Points *points;
    double minX;
    double maxX;
    double minY;
    double maxY;
};

class ErrorRequest : public Request
{
public:
    ErrorRequest();
    QString error;
};

class NewInputValuesRequest : public Request
{
public:
    NewInputValuesRequest();
    double minX;
    double maxX;
    double minY;
    double maxY;
};

class StartDragRequest : public Request
{
public:
    StartDragRequest();
    int x;
    int y;
};

class DragRequest : public Request
{
public:
    DragRequest();
    int diffX;
    int diffY;
    int width;
    int height;
};

class StartPinchRequest : public Request
{
public:
    StartPinchRequest();
};

class PinchRequest : public Request
{
public:
    PinchRequest();
    double scale;
};

class ZoomRequest : public Request
{
public:
    ZoomRequest();
    int delta;
};

class UpdateDerivativeRequest : public Request
{
public:
    UpdateDerivativeRequest();
    Points *points;
    double minX;
    double maxX;
    double minY;
    double maxY;
};

class PlaySoundRequest : public Request
{
public:
    PlaySoundRequest();
};

class StopSoundRequest : public Request
{
public:
    StopSoundRequest();
};

class AudioFinishedRequest : public Request
{
public:
    AudioFinishedRequest();
};

class DrawPointRequest : public Request
{
public:
    DrawPointRequest();
    double x;
    double y;
};

class PreviousPointRequest : public Request
{
public:
    PreviousPointRequest();
};

class NextPointRequest : public Request
{
public:
    NextPointRequest();
};

class SayXRequest : public Request
{
public:
    SayXRequest();
};

class SayYRequest : public Request
{
public:
    SayYRequest();
};

class GetXRequest : public Request
{
public:
    GetXRequest();
};

class GetYRequest : public Request
{
public:
    GetYRequest();
};

class UpdateTextRequest : public Request
{
public:
    UpdateTextRequest();
    QString text;
};

class SayDerivativeRequest : public Request
{
public:
    SayDerivativeRequest();
};

class GetDerivativeRequest : public Request
{
public:
    GetDerivativeRequest();
};

class IncStepRequest : public Request
{
public:
    IncStepRequest();
};

class DecStepRequest : public Request
{
public:
    DecStepRequest();
};

class InterestingPointFinishedRequest : public Request
{
public:
    InterestingPointFinishedRequest();
};

class PreviousPointInterestRequest : public Request
{
public:
    PreviousPointInterestRequest();
};

class NextPointInterestRequest : public Request
{
public:
    NextPointInterestRequest();
};

class PreviousFastRequest : public Request
{
public:
    PreviousFastRequest();
};

class NextFastRequest : public Request
{
public:
    NextFastRequest();
};

class FirstPointRequest : public Request
{
public:
    FirstPointRequest();
};

class LastPointRequest : public Request
{
public:
    LastPointRequest();
};

class SetDerivativeRequest : public Request
{
public:
    SetDerivativeRequest();
    int mode;
};

class SayTextRequest : public Request
{
public:
    SayTextRequest();
    QString text;
};

class NewPointRequest : public Request
{
public:
    NewPointRequest();
    int point;
};

class SetPointRequest : public Request
{
public:
    SetPointRequest();
    int point;
};

class IncPointRequest : public Request
{
public:
    IncPointRequest();
    int step;
};

class DecPointRequest : public Request
{
public:
    DecPointRequest();
    int step;
};

class SetNoteRequest : public Request
{
public:
    SetNoteRequest();
    int fmin;
    int fmax;
    bool useNotes;
    int mode;
    bool useNegativeNotes;
};

class StopNotesRequest : public Request
{
public:
    StopNotesRequest();
};

class AudioStartRequest : public Request
{
public:
    AudioStartRequest();
    QString expression;
    double start;
    double end;
    double minY;
    double maxY;
    int seconds;
    double fmin;
    double fmax;
    int mode;
};

class NotesStartRequest : public Request
{
public:
    NotesStartRequest();
    int fmin;
    int fmax;
    int duration;
    int mode;
    bool useNegativeNotes;
};

#endif // REQUESTS_H
