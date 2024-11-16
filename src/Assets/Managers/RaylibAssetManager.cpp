#include "LettuceEngine/Assets/Managers/RaylibAssetManager.h"
#include <unordered_map>
#include <stdexcept>

static std::unordered_map<std::string, Image> _imageData = std::unordered_map<std::string, Image>();
static std::unordered_map<std::string, Texture2D> _texture2DData = std::unordered_map<std::string, Texture2D>();
static std::unordered_map<const RenderTextureRenderer*, RenderTexture2D> _renderTexture2DData = std::unordered_map<const RenderTextureRenderer*, RenderTexture2D>();

bool RaylibAssetManager::AddImageAsset(const ImageAsset* asset) {
    if (HasImageData(asset->GetAssetID())) {
        // collision
        return false;
    }

    _imageData.emplace(asset->GetAssetID(), ::LoadImage(asset->GetFilePath().c_str()));
    return true;
}

bool RaylibAssetManager::AddTexture2DAsset(const Texture2DAsset* asset) {
    if (!LettuceEngine::Engine::IsRunning()) {
        throw new std::runtime_error("LettuceEngine is not running, cannot add Texture2D data");
    }

    if (HasTexture2DData(asset->GetAssetID())) {
        // collision
        return false;
    }

    bool removeImageAfter = false;
    if (!HasImageData(asset->GetImageAsset())) {
        removeImageAfter = true;
        AddImageAsset(asset->GetImageAsset());
    }
    Texture2D rayTex = ::LoadTextureFromImage(GetImageData(asset->GetImageAsset()));
    _texture2DData.emplace(asset->GetAssetID(), rayTex);
    if (removeImageAfter) {
        RemoveImageData(asset->GetImageAsset());
    }
    return true;
}

void RaylibAssetManager::RemoveImageData(const ImageAsset* asset) {
    RemoveImageData(asset->GetAssetID());
}

void RaylibAssetManager::RemoveImageData(const std::string id) {
    if (!HasImageData(id)) {
        return;
    }

    Image data = _imageData.at(id);
    _imageData.erase(id);
    ::UnloadImage(data);
    return;
}

void RaylibAssetManager::RemoveTexture2DData(const Texture2DAsset* asset) {
    RemoveTexture2DData(asset->GetAssetID());
}

void RaylibAssetManager::RemoveTexture2DData(const std::string id) {
    if (!LettuceEngine::Engine::IsRunning()) {
        throw new std::runtime_error("LettuceEngine is not running, cannot unload Texture2D data");
    }

    if (!HasTexture2DData(id)) {
        return;
    }

    Texture2D data = _texture2DData.at(id);
    _texture2DData.erase(id);
    ::UnloadTexture(data);
    return;
}

Image RaylibAssetManager::GetImageData(const ImageAsset* asset) {
    return GetImageData(asset->GetAssetID());
}

Image RaylibAssetManager::GetImageData(const std::string id) {
    if (!HasImageData(id)) {
        throw std::runtime_error("Raylib image data is not loaded yet for: " + id);
    }

    return _imageData.at(id);
}

Texture2D RaylibAssetManager::GetTexture2DData(const Texture2DAsset* asset) {
    return GetTexture2DData(asset->GetAssetID());
}

Texture2D RaylibAssetManager::GetTexture2DData(const std::string id) {
    if (!LettuceEngine::Engine::IsRunning()) {
        throw new std::runtime_error("LettuceEngine is not running, cannot get Texture2D data");
    }

    if (!HasTexture2DData(id)) {
        throw std::runtime_error("Raylib Texture2D data is not loaded yet for: " + id);
    }

    return _texture2DData.at(id);
}

bool RaylibAssetManager::HasImageData(const ImageAsset* asset) {
    return HasImageData(asset->GetAssetID());
}

bool RaylibAssetManager::HasImageData(const std::string id) {
    return _imageData.find(id) != _imageData.end();
}

bool RaylibAssetManager::HasTexture2DData(const Texture2DAsset* asset) {
    return HasTexture2DData(asset->GetAssetID());
}

bool RaylibAssetManager::HasTexture2DData(std::string id) {
    return _texture2DData.find(id) != _texture2DData.end();
}

bool RaylibAssetManager::AddRenderTexture2DData(const RenderTextureRenderer* render, const RenderTexture2D data) {
    if (!LettuceEngine::Engine::IsRunning()) {
        throw new std::runtime_error("LettuceEngine is not running, cannot get Texture2D data");
    }

    if (HasRenderTexture2DData(render)) {
        return false;
    }

    _renderTexture2DData.emplace(render, data);
    return true;
}

bool RaylibAssetManager::HasRenderTexture2DData(const RenderTextureRenderer* render) {
    return _renderTexture2DData.find(render) != _renderTexture2DData.end();
}

RenderTexture2D RaylibAssetManager::GetRenderTexture2DData(const RenderTextureRenderer* render) {
    if (!LettuceEngine::Engine::IsRunning()) {
        throw new std::runtime_error("LettuceEngine is not running, cannot get Texture2D data");
    }

    if (HasRenderTexture2DData(render)) {
        throw std::runtime_error("Raylib RenderTexture2D data is not loaded yet");
    }

    return _renderTexture2DData.at(render);
}

void RaylibAssetManager::RemoveRenderTexutre2DData(const RenderTextureRenderer* render) {
    if (!LettuceEngine::Engine::IsRunning()) {
        throw new std::runtime_error("LettuceEngine is not running, cannot unload RenderTexture2D data");
    }

    if (!HasRenderTexture2DData(render)) {
        return;
    }

    RenderTexture2D data = _renderTexture2DData.at(render);
    _renderTexture2DData.erase(render);
    ::UnloadRenderTexture(data);
    return;
}

void RaylibAssetManager::RemoveAllData() {
    RemoveAllImageData();
    RemoveAllTexture2DData();
}

void RaylibAssetManager::RemoveAllImageData() {
    while (!_imageData.empty()) {
        RemoveImageData(_imageData.begin().operator*().first);
    }
}

void RaylibAssetManager::RemoveAllTexture2DData() {
    while (!_texture2DData.empty()) {
        RemoveTexture2DData(_texture2DData.begin().operator*().first);
    }
}

void RaylibAssetManager::LoadAllAssetManagerGPUData() {
    // Texture2D Data
    const Texture2DAssetCollection* texture2Ds = static_cast<const Texture2DAssetCollection*>(AssetManager::GetAssetCollection<Texture2DAsset>());
    for (Texture2DAsset* texture : texture2Ds->GetAllAssets()) {
        AddTexture2DAsset(texture);
    }
}

void RaylibAssetManager::UnloadAllAssetManagerGPUData() {
    RemoveAllTexture2DData();
}