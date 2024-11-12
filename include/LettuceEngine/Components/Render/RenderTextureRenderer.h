#pragma once

#include "LettuceEngine/Components/Component.h"
#include "LettuceEngine/Assets/ImageAsset.h"

class RenderTextureRenderer : public Component {
    public:
        RenderTextureRenderer();
        ~RenderTextureRenderer();

        void Render(RenderMessage* message) override;

        void LoadFromImage(ImageAsset* image);
} ;