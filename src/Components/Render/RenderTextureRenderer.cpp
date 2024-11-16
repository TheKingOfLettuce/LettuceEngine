#include "LettuceEngine/Components/Render/RenderTextureRenderer.h"
#include "Raylib/raylib.h"
#include "LettuceEngine/Assets/Managers/RaylibAssetManager.h"
#include <unordered_map>
#include "LettuceEngine/Drawing/BasicDrawing.h"

using LColor = LettuceEngine::Math::Color;

RenderTextureRenderer::RenderTextureRenderer() : Component() {
    
}

RenderTextureRenderer::~RenderTextureRenderer() {
    if ()
}

void RenderTextureRenderer::Render(RenderMessage* message) {
    LettuceEngine::Math::Vector2 point = this->Lettuce()->Position();
    LettuceEngine::Math::Vector2 scale = this->Lettuce()->Scale();
    Texture2D tex = RENDER_TEXTURE_MAP[this];
    ::DrawTexturePro(tex, ::Rectangle({0, 0, (float)tex.width, (float)tex.height}), 
        ::Rectangle({point.X, point.Y, tex.width*scale.X, tex.height*scale.Y}), ::Vector2({(tex.width >> 1)*scale.X, (tex.height >> 1)*scale.Y}), this->Lettuce()->Rotation(), WHITE);
}

void RenderTextureRenderer::LoadFromSize(int width, int height) {
    Image raylibImage = ::GenImageColor(width, height, BLANK);
    AddRenderTexture(raylibImage, this);
}

void AddRenderTexture(Image data, RenderTextureRenderer* instance) {
    if (RENDER_TEXTURE_MAP.find(instance) != RENDER_TEXTURE_MAP.end()) {
        ::UnloadTexture(RENDER_TEXTURE_MAP[instance]);
    }

    RENDER_TEXTURE_MAP[instance] = ::LoadTextureFromImage(data);
}

std::vector<LColor> RenderTextureRenderer::GetColors() {
    Color* colors = RENDER_TEXTURE_MAP[this].
}