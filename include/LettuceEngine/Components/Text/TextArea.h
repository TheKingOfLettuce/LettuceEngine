#pragma once

#include "LettuceEngine/Components/Component.h"
#include <string>
#include "LettuceEngine/CollisionSystem/AABB.h"
#include "LettuceEngine/Math/Color.h"

typedef enum {
    LEFT, CENTER, RIGHT
} TextFormat;

struct TextLine {
    public:
        TextLine();

        std::string LineText;
        LettuceEngine::CollisionSystem::AABB CurrentBox;
        LettuceEngine::Math::Vector2 DrawPosition;
        bool HasNewLine;
        size_t Size();
};

class TextArea : public Component {
    public:
        TextArea();
        ~TextArea();

        void Render(RenderMessage* msg) override;
        void Enabled() override;

        // Basic Getters
        const std::string GetText() const;
        float GetSize() const;
        float GetSpacing() const;
        LettuceEngine::Math::Color GetColor() const;
        LettuceEngine::CollisionSystem::AABB GetArea() const;

        // Text Editing
        void SetText(std::string newText);
        void AppendText(std::string text);
        void PopText(unsigned int numChars = 1);

        // Basic Setters
        void SetSize(float newSize);
        void SetSpacing(float newSpacing);
        void SetColor(LettuceEngine::Math::Color newColor);
        void virtual SetArea(LettuceEngine::CollisionSystem::AABB newArea);
        void SetWordWrap(bool flag);
        void SetTextFormat(TextFormat newFormat);

    protected:
        std::string _text;
        float _currentSize;
        float _currentSpacing;
        LettuceEngine::CollisionSystem::AABB _boundingArea;
        LettuceEngine::Math::Color _color;
        std::vector<TextLine> _lines;
        bool _wordWrap;
        TextFormat _currentFormat;

        void CalculateLines();
        void CalculateLines(std::string text, bool forceLine = false);
        TextLine AddTextToLine(std::string text, TextLine line);
        std::vector<std::string> GatherWords(std::string text);
        void FormatLines();

        void SaveToJson(nlohmann::json& j) override;
        void LoadFromJson(const nlohmann::json& j) override;
};