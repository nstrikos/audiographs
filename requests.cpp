#include "requests.h"
#include <QDebug>

void RequestHandler::add(RequestReceiver *getter, request_type type)
{
    if (type < 100) {

        if (!receivers[type].contains(getter))
            receivers[type].append(getter);
    }
}

void RequestHandler::handleRequest(Request *request)
{
    int type = request->type;

    request->id = request_id;
    request_id++;
    if (request_id > 1000)
        request_id = 0;

    if (type < 100) {
        QVector<RequestReceiver*> tmp_vector = receivers[type];
        for (int i = 0; i < tmp_vector.size(); i++) {
            if (m_log)
                qDebug() << (i+1) << "of" << tmp_vector.size() << " id: " << request->id << " Sender: " << request->sender << " request: " << request->type;
            tmp_vector.at(i)->accept(request);
        }
    }
}

void RequestHandler::setLog(bool log)
{
    m_log = log;
    qDebug() << "Request handler set log " << m_log;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < receivers[i].size(); j++)
            receivers[i].at(j)->setLog(log);
    }
}

bool RequestHandler::log() const
{
    return m_log;
}

void RequestReceiver::setLog(bool log)
{
    m_log = log;
}

CalculateRequest::CalculateRequest()
{
    type = request_calculate;
}

UpdateRequest::UpdateRequest()
{
    type = request_update;
}

ErrorRequest::ErrorRequest()
{
    type = request_error;
}

NewInputValuesRequest::NewInputValuesRequest()
{
    type = request_new_values;
}

StartDragRequest::StartDragRequest()
{
    type = request_start_drag;
}

DragRequest::DragRequest()
{
    type = request_drag;
}

StartPinchRequest::StartPinchRequest()
{
    type = request_start_pinch;
}

PinchRequest::PinchRequest()
{
    type = request_pinch;
}

ZoomRequest::ZoomRequest()
{
    type = request_zoom;
}

UpdateDerivativeRequest::UpdateDerivativeRequest()
{
    type = request_update_derivative;
}

PlaySoundRequest::PlaySoundRequest()
{
    type = request_play_sound;
}

StopSoundRequest::StopSoundRequest()
{
    type = request_stop_sound;
}

AudioFinishedRequest::AudioFinishedRequest()
{
    type = request_audio_finished;
}

DrawPointRequest::DrawPointRequest()
{
    type = request_draw_point;
}

PreviousPointRequest::PreviousPointRequest()
{
    type = request_previous_point;
}

NextPointRequest::NextPointRequest()
{
    type = request_next_point;
}

SayXRequest::SayXRequest()
{
    type = request_sayX;
}

SayYRequest::SayYRequest()
{
    type = request_sayY;
}

GetXRequest::GetXRequest()
{
    type = request_getX;
}

GetYRequest::GetYRequest()
{
    type = request_getY;
}

UpdateTextRequest::UpdateTextRequest()
{
    type = request_update_text;
}

SayDerivativeRequest::SayDerivativeRequest()
{
    type = request_say_derivative;
}

GetDerivativeRequest::GetDerivativeRequest()
{
    type = request_get_derivative;
}

IncStepRequest::IncStepRequest()
{
    type = request_inc_step;
}

DecStepRequest::DecStepRequest()
{
    type = request_dec_step;
}

InterestingPointFinishedRequest::InterestingPointFinishedRequest()
{
    type = request_interesting_point_finished;
}

PreviousPointInterestRequest::PreviousPointInterestRequest()
{
    type = request_previous_point_interest;
}

NextPointInterestRequest::NextPointInterestRequest()
{
    type = request_next_point_interest;
}

PreviousFastRequest::PreviousFastRequest()
{
    type = request_previous_fast;
}

NextFastRequest::NextFastRequest()
{
    type = request_next_fast;
}

FirstPointRequest::FirstPointRequest()
{
    type = request_first_point;
}

LastPointRequest::LastPointRequest()
{
    type = request_last_point;
}

SetDerivativeRequest::SetDerivativeRequest()
{
    type = request_set_derivative;
}

SayTextRequest::SayTextRequest()
{
    type = request_say_text;
}

NewPointRequest::NewPointRequest()
{
    type = request_new_point;
}

SetPointRequest::SetPointRequest()
{
    type = request_set_point;
}

IncPointRequest::IncPointRequest()
{
    type = request_inc_point;
}

DecPointRequest::DecPointRequest()
{
    type = request_dec_point;
}

SetNoteRequest::SetNoteRequest()
{
    type = request_set_note;
}

StopNotesRequest::StopNotesRequest()
{
    type = request_stop_notes;
}

AudioStartRequest::AudioStartRequest()
{
    type = request_audio_start;
}

NotesStartRequest::NotesStartRequest()
{
    type = request_notes_start;
}

CalculateDerivativeRequest::CalculateDerivativeRequest()
{
    type = request_calculate_derivative;
}

CalculateSecondDerivativeRequest::CalculateSecondDerivativeRequest()
{
    type = request_calculate_second_derivative;
}
