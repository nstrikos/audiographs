#include "requests.h"
#include <QDebug>

CalculateRequest::CalculateRequest()
{
    type = request_calculate;
    description = "calculate request";
}

UpdateRequest::UpdateRequest()
{
    type = request_update;
    description = "update request";
}

ErrorRequest::ErrorRequest()
{
    type = request_error;
    description = "error request";
}

NewInputValuesRequest::NewInputValuesRequest()
{
    type = request_new_values;
    description = "new input values request";
}

StartDragRequest::StartDragRequest()
{
    type = request_start_drag;
    description = "start drag request";
}

DragRequest::DragRequest()
{
    type = request_drag;
    description = "drag request";
}

StartPinchRequest::StartPinchRequest()
{
    type = request_start_pinch;
    description = "start pinch request";
}

PinchRequest::PinchRequest()
{
    type = request_pinch;
    description = "pinch request";
}

ZoomRequest::ZoomRequest()
{
    type = request_zoom;
    description = "zoom";
}

UpdateDerivativeRequest::UpdateDerivativeRequest()
{
    type = request_update_derivative;
    description = "update derivative request";
}

PlaySoundRequest::PlaySoundRequest()
{
    type = request_play_sound;
    description = "play sound request";
}

StopSoundRequest::StopSoundRequest()
{
    type = request_stop_sound;
    description = "stop sound request";
}

AudioFinishedRequest::AudioFinishedRequest()
{
    type = request_audio_finished;
    description = "audio finished request";
}

DrawPointRequest::DrawPointRequest()
{
    type = request_draw_point;
    description = "draw point request";
}

PreviousPointRequest::PreviousPointRequest()
{
    type = request_previous_point;
    description = "previous point request";
}

NextPointRequest::NextPointRequest()
{
    type = request_next_point;
    description = "next point request";
}

SayXRequest::SayXRequest()
{
    type = request_sayX;
    description = "sayX request";
}

SayYRequest::SayYRequest()
{
    type = request_sayY;
    description = "sayY request";
}

GetXRequest::GetXRequest()
{
    type = request_getX;
    description = "getX request";
}

GetYRequest::GetYRequest()
{
    type = request_getY;
    description = "getY request";
}

UpdateTextRequest::UpdateTextRequest()
{
    type = request_update_text;
    description = "update text request";
}

SayDerivativeRequest::SayDerivativeRequest()
{
    type = request_say_derivative;
    description = "say derivative request";
}

GetDerivativeRequest::GetDerivativeRequest()
{
    type = request_get_derivative;
    description = "get derivative request";
}

IncStepRequest::IncStepRequest()
{
    type = request_inc_step;
    description = "inc step request";
}

DecStepRequest::DecStepRequest()
{
    type = request_dec_step;
    description = "dec step request";
}

InterestingPointFinishedRequest::InterestingPointFinishedRequest()
{
    type = request_interesting_point_finished;
    description = "interesting point finished request";
}

PreviousPointInterestRequest::PreviousPointInterestRequest()
{
    type = request_previous_point_interest;
    description = "previous point interest request";
}

NextPointInterestRequest::NextPointInterestRequest()
{
    type = request_next_point_interest;
    description = "next point interest request";
}

PreviousFastRequest::PreviousFastRequest()
{
    type = request_previous_fast;
    description = "previous fast request";
}

NextFastRequest::NextFastRequest()
{
    type = request_next_fast;
    description = "next fast request";
}

FirstPointRequest::FirstPointRequest()
{
    type = request_first_point;
    description = "first point request";
}

LastPointRequest::LastPointRequest()
{
    type = request_last_point;
    description = "last point request";
}

SetDerivativeRequest::SetDerivativeRequest()
{
    type = request_set_derivative;
    description = "set derivative request";
}

SayTextRequest::SayTextRequest()
{
    type = request_say_text;
    description = "say text request";
}

NewPointRequest::NewPointRequest()
{
    type = request_new_point;
    description = "new point request";
}

SetPointRequest::SetPointRequest()
{
    type = request_set_point;
    description = "set point request";
}

IncPointRequest::IncPointRequest()
{
    type = request_inc_point;
    description = "inc point request";
}

DecPointRequest::DecPointRequest()
{
    type = request_dec_point;
    description = "dec point request";
}

SetNoteRequest::SetNoteRequest()
{
    type = request_set_note;
    description = "set note request";
}

StopNotesRequest::StopNotesRequest()
{
    type = request_stop_notes;
    description = "stop notes request";
}

AudioStartRequest::AudioStartRequest()
{
    type = request_audio_start;
    description = "audio start request";
}

NotesStartRequest::NotesStartRequest()
{
    type = request_notes_start;
    description = "notes start request";
}

CalculateDerivativeRequest::CalculateDerivativeRequest()
{
    type = request_calculate_derivative;
    description = "calculate derivative request";
}

CalculateSecondDerivativeRequest::CalculateSecondDerivativeRequest()
{
    type = request_calculate_second_derivative;
    description = "calculate second derivative request";
}

NormalModeRequest::NormalModeRequest()
{
    type = request_normal_mode;
    description = "normal mode request";
}
