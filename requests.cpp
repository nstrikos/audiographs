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

NormalModeRequest::NormalModeRequest()
{
    type = request_normal_mode;
}
