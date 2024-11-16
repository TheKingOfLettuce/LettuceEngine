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

        std::vector<LettuceEngine::Math::Color> GetColors();
        void WriteColors(std::vector<LettuceEngine::Math::Color> newColors);
} ;