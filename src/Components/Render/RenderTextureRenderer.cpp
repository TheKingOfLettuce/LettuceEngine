#include "LettuceEngine/Components/Render/RenderTextureRenderer.h"
#include "Raylib/raylib.h"
#include "LettuceEngine/Assets/Managers/RaylibAssetManager.h"

const char* RENDER_TEXTURE_ID_PREFIX = "LettuceEngineRenderTexture";
size_t RENDER_TEXTURE_ID;

RenderTextureRenderer::RenderTextureRenderer() : Component() {
    _savable = false;
}

void RenderTextureRenderer::LoadFromImage(ImageAsset* image) {
    Image raylibImage = RaylibAssetManager::GetImageData(image);
}