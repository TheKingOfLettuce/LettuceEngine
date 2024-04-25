#include "Components/Input/ClickHandler.h"
#include "Logging/Log.h"

ClickHandler::ClickHandler() : Component() {
    _continousCallback = false;
    OnClick = CallbackWithArg<ClickData>();
}

ClickHandler::~ClickHandler() {}

void ClickHandler::HandleClick(LettuceEngine::MouseButtons button, LettuceEngine::Math::Vector2 position) {
    OnClick.Invoke(ClickData {button, position});
}