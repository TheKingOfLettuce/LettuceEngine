#pragma once
#include "LettuceEngine/MessageSystem/MessageBase.h"

class UpdateMessage : public MessageBase {
    public:
        UpdateMessage(float delta);
        float GetTimeDelta();
    private:
        float _timeDelta;
};

class RenderMessage : public MessageBase {

};