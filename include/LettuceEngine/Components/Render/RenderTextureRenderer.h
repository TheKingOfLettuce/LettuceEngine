#pragma once

#include "LettuceEngine/Components/Component.h"
#include "LettuceEngine/Assets/ImageAsset.h"
#include <vector>
#include "LettuceEngine/Math/Color.h"

class RenderTextureRenderer : public Component {
    public:
        RenderTextureRenderer();
        ~RenderTextureRenderer();

        void Render(RenderMessage* message) override;

        void LoadFromSize(int width, int height);

        const std::vector<LettuceEngine::Math::Color> GetColors();
        void WriteColors(const std::vector<LettuceEngine::Math::Color> newColors);
} ;