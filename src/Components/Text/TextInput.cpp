#include "LettuceEngine/Components/Text/TextInput.h"
#include "LettuceEngine/Logging/Log.h"
#include "LettuceEngine/Input/InputSystem.h"
#include "LettuceEngine/Drawing/BasicDrawing.h"
#include <string>

using LettuceEngine::Math::Vector2;
using LettuceEngine::CollisionSystem::AABB;
using LettuceEngine::InputSystem;
using LettuceEngine::MouseButtons;
using LettuceEngine::KeyCodes;

TextInput::TextInput() : TextArea() {
    _collider = new Collider2D();
    _onClick = new ClickHandler();
    _canEdit = false;
    _displayCursor = true;
    _cursorFlag = false;
    _currentCursorTime = 0;
    _frameDelayButton = 5;
}

TextInput::~TextInput() {}

void TextInput::SetArea(AABB area) {
    TextArea::SetArea(area);
    _collider->SetBox(area);
}

void TextInput::Init(LettuceObject* lettuce) {
    TextArea::Init(lettuce);
    lettuce->AddComponent(_onClick);
    lettuce->AddComponent(_collider);
    _onClick->OnClick.AddCallback(&TextInput::TextAreaClicked, this);
}

void TextInput::Update(UpdateMessage* msg) {
    if (!_canEdit) return;
    // if a mouse click happened but not on this
    if (InputSystem::IsMouseButtonPressed(MouseButtons::MOUSE_BUTTON_LEFT) && !InputSystem::WasClicked(_onClick)) {
        TextAreaNotClicked();
        return;
    }

    if (_currentFrameDealy >= _frameDelayButton) {
        _currentFrameDealy = 0;
        if (InputSystem::IsKeyDown(KeyCodes::KEY_BACKSPACE)) {
            PopText();
        }
        if (InputSystem::IsKeyDown(KeyCodes::KEY_ENTER)) {
            AppendText("\n");
        }
    }

    std::string textToAdd = std::string();
    for (char c : InputSystem::GetCharsPressed()) {
        textToAdd += c;
    }
    if (textToAdd.size() != 0)
        AppendText(textToAdd);

    _currentFrameDealy++;

    _currentCursorTime += msg->GetTimeDelta();
    if (_currentCursorTime >= .75f) {
        _currentCursorTime = 0;
        _cursorFlag = !_cursorFlag;
    }
}

void TextInput::Render(RenderMessage* message) {
    TextArea::Render(message);
    if (!_displayCursor || !_cursorFlag) return;
    if (_lines.size() == 0) return;

    AABB lineBox = _lines[_lines.size()-1].CurrentBox;
    Vector2 drawPos = lineBox.GetMaxExtents();
    drawPos.Y = lineBox.GetMinExtents().Y;
    drawPos += _lettuce->Position();
    BasicDrawing::DrawText("_", drawPos, _currentSize, _currentSpacing, _color);
}

void TextInput::TextAreaClicked(ClickData data) {
    _canEdit = true;
    Log::Debug("Text area clicked, can now edit");
}

void TextInput::TextAreaNotClicked() {
    _canEdit = false;
    _cursorFlag = false;
    _currentCursorTime = 0;
    Log::Debug("Text area not clicked, editing turned off");
}