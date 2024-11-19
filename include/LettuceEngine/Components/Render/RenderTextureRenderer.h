#pragma once

#include "LettuceEngine/Components/Component.h"
#include "LettuceEngine/Assets/Texture2DAsset.h"
#include <vector>
#include "LettuceEngine/Math/Color.h"

class RenderTextureRenderer : public Component {
    public:
        RenderTextureRenderer();
        ~RenderTextureRenderer();

        void Render(RenderMessage* message) override;

        void LoadFromSize(int width, int height);

        const std::vector<LettuceEngine::Math::Color> GetColors();
        void DrawPixel(const LettuceEngine::Math::Color newColor, const LettuceEngine::Math::Vector2 pos);
        void DrawPixels(const std::vector<std::pair<const LettuceEngine::Math::Color, const LettuceEngine::Math::Vector2>> colors);
        void DrawTexture(const Texture2DAsset* image, const LettuceEngine::Math::Vector2 pos);
} ;