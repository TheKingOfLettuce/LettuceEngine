#include "LettuceEngine/MessageSystem/Messages/GameLoopMessages.h"

UpdateMessage::UpdateMessage(float delta) {
    _timeDelta = delta;
}

float UpdateMessage::GetTimeDelta() {
    return _timeDelta;
}