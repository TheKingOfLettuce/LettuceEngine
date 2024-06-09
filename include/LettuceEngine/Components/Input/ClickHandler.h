#pragma once

#include "LettuceEngine/Components/Component.h"
#include "LettuceEngine/Input/InputEnums.h"
#include "LettuceEngine/Utils/Callbacks/CallbackWithArg.h"

struct ClickData {
    LettuceEngine::MouseButtons MouseButton;
    LettuceEngine::Math::Vector2 MousePosition;
};

class ClickHandler : public Component {
    public:
        CallbackWithArg<ClickData> OnClick;

        ClickHandler();
        ~ClickHandler();
        void HandleClick(LettuceEngine::MouseButtons mouseButton, LettuceEngine::Math::Vector2 mousePosition);

    private:
        bool _continousCallback;
};