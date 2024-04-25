#pragma once
#include "Component.h"
#include "Math/Color.h"

class PrimitiveRenderer : public Component {
    public:
        typedef enum {
            PIXEL,
            CIRCLE,
            ELLIPSE,
            RECTANGLE
        } Shape;

        PrimitiveRenderer();
        ~PrimitiveRenderer();

        void Render(RenderMessage* message) override;

        Shape GetShape() const;
        void SetShape(Shape shpae);
        LettuceEngine::Math::Color GetColor() const;
        void SetColor(LettuceEngine::Math::Color color);
        float GetSize() const;
        void SetSize(float size);
    protected:
        void SaveToJson(nlohmann::json& j) override;
        void LoadFromJson(const nlohmann::json& data) override;
    
    private:
        LettuceEngine::Math::Color _color;
        Shape _renderShape;
        float _size;
};