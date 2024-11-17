#include "LettuceEngine/Components/Render/RenderTextureRenderer.h"
#include "Raylib/raylib.h"
#include "LettuceEngine/Assets/Managers/RaylibAssetManager.h"
#include <unordered_map>
#include "LettuceEngine/Drawing/BasicDrawing.h"
#include "LettuceEngine/Drawing/RaylibDrawing.h"

static std::unordered_map<const RenderTextureRenderer*, RenderTexture2D> RENDER_TEXTURE_MAP = std::unordered_map<const RenderTextureRenderer*, RenderTexture2D>();
using LColor = LettuceEngine::Math::Color;

bool HasRenderTexture(const RenderTextureRenderer* render) {
    return RENDER_TEXTURE_MAP.find(render) != RENDER_TEXTURE_MAP.end();
}

bool RemoveRenderTexture(const RenderTextureRenderer* render) {
    if (!HasRenderTexture(render))
        return false;

    ::UnloadRenderTexture(RENDER_TEXTURE_MAP[render]);
    RENDER_TEXTURE_MAP.erase(render);
    return true;
}

RenderTextureRenderer::RenderTextureRenderer() : Component() {
    
}

RenderTextureRenderer::~RenderTextureRenderer() {
    RemoveRenderTexture(this);
}

void RenderTextureRenderer::Render(RenderMessage* message) {
    if (!HasRenderTexture(this)) {
        BasicDrawing::DrawRectangle(_lettuce->Position(), LColor(), LettuceEngine::Math::Vector2(50, 50), _lettuce->Rotation());
        return;
    }

    Texture2D tex = RENDER_TEXTURE_MAP[this].texture;
    RaylibDrawing::DrawTexture(_lettuce->Position(), tex, WHITE, _lettuce->Scale(), _lettuce->Rotation());
}

void RenderTextureRenderer::LoadFromSize(int width, int height) {
    RemoveRenderTexture(this);  
    RenderTexture2D renderTexture = ::LoadRenderTexture(width, height);
    RENDER_TEXTURE_MAP[this] = renderTexture;
}

const std::vector<LColor> RenderTextureRenderer::GetColors() {
    if (!HasRenderTexture(this))
        return std::vector<LColor>();

    std::vector<LColor> colors = std::vector<LColor>();

    Image renderData = ::LoadImageFromTexture(RENDER_TEXTURE_MAP[this].texture);
    ::Color* textureColors = static_cast<::Color*>(renderData.data);
    while(textureColors) {
        ::Color c = *textureColors;
        colors.push_back(LColor(c.r, c.g, c.b, c.a));
        textureColors++;
    }
    ::UnloadImage(renderData);
    return colors;
}

void RenderTextureRenderer::WriteColors(const std::vector<LColor> colors) {
    if (!HasRenderTexture(this))
        return;
    int textureWidth = RENDER_TEXTURE_MAP[this].texture.width;
    int textureHeight = RENDER_TEXTURE_MAP[this].texture.height;
    if (colors.size() != textureWidth*textureHeight) {
        throw new std::invalid_argument("Provided color length does not match RenderTexture width x height");
    }

    ::BeginTextureMode(RENDER_TEXTURE_MAP[this]);
    
    ::EndTextureMode();
}