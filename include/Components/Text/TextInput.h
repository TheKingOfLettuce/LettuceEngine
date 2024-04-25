#pragma once
#include "Components/Text/TextArea.h"
#include "Components/Collision/Collider2D.h"
#include "Components/Input/ClickHandler.h"
#include <unordered_map>

class TextInput : public TextArea {
    public:
        TextInput();
        ~TextInput();

        void SetArea(LettuceEngine::CollisionSystem::AABB area) override;
        void Init(LettuceObject* lettuce) override;
        void Update(UpdateMessage* msg) override;
        void Render(RenderMessage* msg) override;

    protected:
        ClickHandler* _onClick;
        Collider2D* _collider;
        bool _canEdit;
        bool _displayCursor;
        size_t _frameDelayButton;
        size_t _currentFrameDealy;
        void TextAreaClicked(ClickData data);
        void TextAreaNotClicked();

    private:
        float _currentCursorTime;
        float _cursorFlag;

};