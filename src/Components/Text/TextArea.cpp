#include "LettuceEngine/Components/Text/TextArea.h"
#include "LettuceEngine/Drawing/BasicDrawing.h"
#include "LettuceEngine/Logging/Log.h"
#include "LettuceEngine/Engine.h"

using LettuceEngine::CollisionSystem::AABB;
using LettuceEngine::Math::Color;
using LettuceEngine::Math::Vector2;

TextLine::TextLine() {
    LineText = "";
    CurrentBox = AABB();
    HasNewLine = false;
}

size_t TextLine::Size() {
    if (HasNewLine)
        return LineText.size() + 1;
    return LineText.size();
}

TextArea::TextArea() : Component() {
    _text = "";
    _currentSize = 12;
    _currentSpacing = 1;
    _boundingArea = AABB();
    _color = Color();
    _wordWrap = true;
    _currentFormat = TextFormat::LEFT;
    _lines = std::vector<TextLine>();
}

TextArea::~TextArea() {}

void TextArea::Render(RenderMessage* msg) {
    if (LettuceEngine::Engine::IsDebugView())
        BasicDrawing::DrawRectangleLines(_boundingArea.GetOffset() + _lettuce->Position(), Color(255, 255, 0, 255), _boundingArea.GetHalfSize());
    for (TextLine line : _lines) {
        if (line.LineText != "")
            BasicDrawing::DrawText(line.LineText, line.DrawPosition + _lettuce->Position(), _currentSize, _currentSpacing, _color);
        if (LettuceEngine::Engine::IsDebugView())
            BasicDrawing::DrawRectangleLines(line.CurrentBox.GetOffset() + _lettuce->Position(), Color(255, 255, 0, 255), line.CurrentBox.GetHalfSize());
    }
}

void TextArea::Enabled() {
    Component::Enabled();
    FormatLines();
}

void TextArea::SetSize(float newSize) {
    _currentSize = newSize;
    CalculateLines();
}

void TextArea::SetSpacing(float newSpacing) {
    _currentSpacing = newSpacing;
    CalculateLines();
}

void TextArea::SetColor(Color newColor) {
    _color = newColor;
}

void TextArea::SetArea(LettuceEngine::CollisionSystem::AABB newArea) {
    _boundingArea = newArea;
    CalculateLines();
}

void TextArea::SetWordWrap(bool value) {
    if (_wordWrap == value) return;
    _wordWrap = value;
    CalculateLines();
}

void TextArea::SetTextFormat(TextFormat newFormat) {
    if (_currentFormat == newFormat) return;
    _currentFormat = newFormat;
    FormatLines();
}

const std::string TextArea::GetText() const {
    return _text;
}

float TextArea::GetSize() const {
    return _currentSize;
}

float TextArea::GetSpacing() const {
    return _currentSpacing;
}

Color TextArea::GetColor() const {
    return _color;
}

LettuceEngine::CollisionSystem::AABB TextArea::GetArea() const {
    return _boundingArea;
}

void TextArea::SetText(std::string newText) {
    _text = newText;
    CalculateLines();
}

void TextArea::AppendText(std::string text) {
    _text += text;
    CalculateLines(text);
}

void TextArea::PopText(unsigned int numChars) {
    if (_text.size() == 0)
        return;
    if (_text.size() <= numChars) {
        _text = "";
        _lines.clear();
        return;
    }

    _text = _text.substr(0, _text.size()-numChars);

    unsigned int count = 0;
    TextLine currentLine = _lines[_lines.size()-1];
    while (currentLine.Size() < numChars-count) {
        // keep erasing lines if pop count is greater
        count += currentLine.Size();
        _lines.erase(_lines.begin() + _lines.size()-1);
        currentLine = _lines[_lines.size()-1];
    }

    if (count != numChars) {
        _lines.erase(_lines.begin() + _lines.size()-1);
        if (currentLine.Size() > numChars-count) {
            std::string bottomText = currentLine.LineText.substr(0, currentLine.LineText.size() - numChars-count);
            CalculateLines(bottomText, true);
            _lines[_lines.size()-1].HasNewLine = currentLine.HasNewLine;
            return;
        }
    }

    FormatLines();
}

std::vector<std::string> TextArea::GatherWords(std::string text) {
    std::vector<std::string> toReturn = std::vector<std::string>();

    std::string word = std::string();
    for (size_t i = 0; i < text.length(); i++) {
        if (text[i] == ' ') {
            if (word != "")
                toReturn.push_back(word);
            toReturn.push_back(" ");
            word = std::string();
            continue;
        }
        else if (text[i] == '\n') {
            if (word != "")
                toReturn.push_back(word);
            toReturn.push_back("\n");
            word = std::string();
            continue;
        }

        word += text[i];
    }

    if (word != "")
        toReturn.push_back(word);

    return toReturn;
}

void TextArea::CalculateLines() {
    _lines.clear();
    CalculateLines(_text);
}

void TextArea::CalculateLines(std::string text, bool forceLine) {
    TextLine currentLine = TextLine();
    if (_lines.size() != 0 && !forceLine) {
        text = _lines[_lines.size()-1].LineText + text;
        // remove it so we can add it back at the end
        _lines.erase(_lines.begin() + _lines.size()-1);
    }

    if (_wordWrap) {
        for (std::string word : GatherWords(text)) {
            currentLine = AddTextToLine(word, currentLine);
        }
    }
    else {
        for (size_t i = 0; i < text.length(); i++) {
            currentLine = AddTextToLine(std::string(1, text[i]), currentLine);
        }
    }

    //if (currentLine.Size() != 0)
    _lines.push_back(currentLine);

    FormatLines();
}

TextLine TextArea::AddTextToLine(std::string text, TextLine line) {
    if (text == "\n") {
        if (line.LineText == "")
            // add size divider for rendering empty new lines
            line.CurrentBox = BasicDrawing::MeasureText("|", _currentSize, _currentSpacing);
        line.HasNewLine = true;
        _lines.push_back(line);
        line = TextLine();
        return line;
    }
    
    if (!_boundingArea.ContainsAABB(BasicDrawing::MeasureText(text, _currentSize, _currentSpacing))) {
        Log::Warning("Word does not fit in TextArea: " + text);
        if (line.Size() != 0) {
            _lines.push_back(line);
            line = TextLine();
        }
        line.CurrentBox = BasicDrawing::MeasureText(text, _currentSize, _currentSpacing);
        line.LineText = text;
        return line;
    }

    AABB currentSize = BasicDrawing::MeasureText(line.LineText + text, _currentSize, _currentSpacing);
    if (!_boundingArea.ContainsAABB(currentSize)) {
        _lines.push_back(line);
        line = TextLine();
        currentSize = BasicDrawing::MeasureText(line.LineText + text, _currentSize, _currentSpacing);
    }
    line.CurrentBox = currentSize;
    line.LineText += text;

    return line;
}

void TextArea::FormatLines() {
    if (!_enabled) return;
    size_t size = _lines.size();
    if (size == 0) return;
    Vector2 offset = Vector2();
    offset.Y = _boundingArea.GetMinExtents().Y;
    for (size_t i = 0; i < size; i++) {
        switch (_currentFormat) {
            case TextFormat::LEFT:
                offset.X = _boundingArea.GetMinExtents().X;
                break;
            case TextFormat::CENTER:
                offset.X = _lines[i].CurrentBox.GetMinExtents().X;
                break;
            case TextFormat::RIGHT:
                offset.X = (_boundingArea.GetMaxExtents().X - _lines[i].CurrentBox.GetMaxExtents().X) - _lines[i].CurrentBox.GetHalfSize().X;
                break;
        }
        if (i != 0) {
            offset.Y += _lines[i-1].CurrentBox.GetHalfSize().Y*2;
        }

        _lines[i].DrawPosition = offset;
        _lines[i].CurrentBox.SetOffset(offset + _lines[i].CurrentBox.GetHalfSize());
    }
}

void TextArea::SaveToJson(nlohmann::json& j) {
    Component::SaveToJson(j);
    j["fontSize"] = _currentSize;
    j["fontSpacing"] = _currentSpacing;
    j["fontColor"] = _color;
    j["text"] = _text;
}

void TextArea::LoadFromJson(const nlohmann::json& j) {
    Component::LoadFromJson(j);
    SetSize(j.at("fontSize"));
    SetSpacing(j.at("fontSpacing"));
    SetColor(j.at("fontColor"));
    SetText(j.at("text"));
}
