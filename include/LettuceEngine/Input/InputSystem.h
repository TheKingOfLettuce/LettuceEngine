#pragma once
#include <vector>
#include "LettuceEngine/Math/Vector2.h"
#include "LettuceEngine/Components/Input/ClickHandler.h"
#include "LettuceEngine/Input/InputEnums.h"

namespace LettuceEngine {
    class InputSystem {
        public:
            static bool IsKeyPressed(KeyCodes key);
            static bool IsKeyDown(KeyCodes key);
            static bool IsKeyReleased(KeyCodes key);
            static bool IsKeyUp(KeyCodes key);

            static bool IsMouseButtonPressed(MouseButtons button);
            static bool IsMouseButtonDown(MouseButtons button);
            static bool IsMouseButtonReleased(MouseButtons button);
            static bool IsMouseButtonUp(MouseButtons button);
            static LettuceEngine::Math::Vector2 GetMousePosition();

            static const std::vector<char> GetCharsPressed();
            static bool WasClicked(ClickHandler* click);

            void GatherInput();
            void GatherClickables();
    };
}