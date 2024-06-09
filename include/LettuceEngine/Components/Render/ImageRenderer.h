#pragma once
#include "LettuceEngine/Components/Component.h"
#include "LettuceEngine/Assets/Texture2DAsset.h"
#include "LettuceEngine/Math/Color.h"

class ImageRenderer : public Component {
    public:
        ImageRenderer();
        ~ImageRenderer();

        void Render(RenderMessage* message) override;

        void SetTexture(Texture2DAsset* image);
        Texture2DAsset* GetTexture();

        void SetColor(LettuceEngine::Math::Color color);
        LettuceEngine::Math::Color GetColor();
    protected:
        void SaveToJson(nlohmann::json& j) override;
        void LoadFromJson(const nlohmann::json& data) override;
    private:
        Texture2DAsset* _texture;
        LettuceEngine::Math::Color _color;
};