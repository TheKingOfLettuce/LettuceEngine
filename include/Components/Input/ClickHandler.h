#pragma once

#include "Components/Component.h"
#include "Input/InputEnums.h"
#include "Utils/Callbacks/CallbackWithArg.h"

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