#include "LettuceEngine/Input/InputSystem.h"
#include "Raylib/raylib.h"
#include "LettuceEngine/Engine.h"
#include <stdexcept>
#include "LettuceEngine/Logging/Log.h"
#include "LettuceEngine/MessageSystem/MessageBus.h"
#include "LettuceEngine/MessageSystem/MessageBase.h"

using LettuceEngine::KeyCodes;
using LettuceEngine::InputSystem;

std::vector<char> _charsPressed = std::vector<char>();
std::unordered_set<ClickHandler*> _clicks = std::unordered_set<ClickHandler*>();

void InputSystem::GatherInput() {
    _charsPressed.clear();
    if (!LettuceEngine::Engine::IsRunning()) {
        throw std::logic_error(std::string("Cannot gather input, engine does not exist or is not running."));
    }
    
    int raylibCode = ::GetCharPressed();
    while (raylibCode != 0) {
        char uniCode = (char)raylibCode;
        _charsPressed.push_back(uniCode);
        Log::Debug(std::string("Received keyboard key: ") + uniCode);
        raylibCode = ::GetCharPressed();
    }
}

void InputSystem::GatherClickables() {
    if (!IsMouseButtonPressed(MouseButtons::MOUSE_BUTTON_LEFT)) return;
    LettuceEngine::Math::Vector2 mousePosition = GetMousePosition();
    std::unordered_set<Collider2D*>* hits = Engine::CollisionSystem()->FindIntersections(mousePosition);
    _clicks.clear();
    for(Collider2D* hit : *hits) {
        if (!hit->Lettuce()->HasComponent<ClickHandler>()) continue;

        for (ClickHandler* click : hit->Lettuce()->GetComponents<ClickHandler>()) {
            _clicks.insert(click);
            click->HandleClick(MouseButtons::MOUSE_BUTTON_LEFT, mousePosition);
        }
    }
    delete hits;
}

bool InputSystem::WasClicked(ClickHandler* click) {
    return _clicks.find(click) != _clicks.end();
}

const std::vector<char> InputSystem::GetCharsPressed() {
    return _charsPressed;
}

bool InputSystem::IsKeyDown(KeyCodes key) {
    return ::IsKeyDown(key);
}

bool InputSystem::IsKeyUp(KeyCodes key) {
    return ::IsKeyUp(key);
}

bool InputSystem::IsKeyPressed(KeyCodes key) {
    return ::IsKeyPressed(key);
}

bool InputSystem::IsKeyReleased(KeyCodes key) {
    return ::IsKeyReleased(key);
}

bool InputSystem::IsMouseButtonDown(MouseButtons button) {
    return ::IsMouseButtonDown(button);
}

bool InputSystem::IsMouseButtonPressed(MouseButtons button) {
    return ::IsMouseButtonPressed(button);
}

LettuceEngine::Math::Vector2 InputSystem::GetMousePosition() {
    return LettuceEngine::Math::Vector2(::GetMouseX(), ::GetMouseY());
}