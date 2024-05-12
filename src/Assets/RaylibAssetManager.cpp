#include "Assets/RaylibAssetManager.h"
#include <unordered_map>
#include <stdexcept>

static std::unordered_map<std::string, Image> _imageData = std::unordered_map<std::string, Image>();
static std::unordered_map<std::string, Texture2D> _texture2DData = std::unordered_map<std::string, Texture2D>();

bool RaylibAssetManager::AddImageAsset(ImageAsset* asset) {
    if (_imageData.find(asset->GetAssetID()) != _imageData.end()) {
        // collision
        return false;
    }

    _imageData.emplace(asset->GetAssetID(), ::LoadImage(asset->GetFilePath().c_str()));
    return true;
}

bool RaylibAssetManager::AddTexture2DAsset(Texture2DAsset* asset) {
    if (_texture2DData.find(asset->GetAssetID()) != _texture2DData.end()) {
        // collision
        return false;
    }

    bool removeImageAfter = false;
    if (_imageData.find(asset->GetImageAsset()->GetAssetID()) == _imageData.end()) {
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

void RaylibAssetManager::RemoveImageData(ImageAsset* asset) {
    RemoveImageData(asset->GetAssetID());
}

void RaylibAssetManager::RemoveImageData(std::string id) {
    if (_imageData.find(id) == _imageData.end()) {
        return;
    }

    Image data = _imageData.at(id);
    _imageData.erase(id);
    ::UnloadImage(data);
    return;
}

void RaylibAssetManager::RemoveTexture2DData(Texture2DAsset* asset) {
    RemoveTexture2DData(asset->GetAssetID());
}

void RaylibAssetManager::RemoveTexture2DData(std::string id) {
    if (!LettuceEngine::Engine::IsRunning()) {
        throw new std::runtime_error("LettuceEngine is not running, cannot unload Texture2D data");
    }

    if (_texture2DData.find(id) == _texture2DData.end()) {
        return;
    }

    Texture2D data = _texture2DData.at(id);
    _texture2DData.erase(id);
    ::UnloadTexture(data);
    return;
}

Image RaylibAssetManager::GetImageData(ImageAsset* asset) {
    return GetImageData(asset->GetAssetID());
}

Image RaylibAssetManager::GetImageData(std::string id) {
    if (_imageData.find(id) == _imageData.end()) {
        throw std::runtime_error("Raylib image data is not loaded yet for: " + id);
    }

    return _imageData.at(id);
}

Texture2D RaylibAssetManager::GetTexture2DData(Texture2DAsset* asset) {
    return GetTexture2DData(asset->GetAssetID());
}

Texture2D RaylibAssetManager::GetTexture2DData(std::string id) {
    if (!LettuceEngine::Engine::IsRunning()) {
        throw new std::runtime_error("LettuceEngine is not running, cannot get Texture2D data");
    }

    if (_texture2DData.find(id) == _texture2DData.end()) {
        throw std::runtime_error("Raylib Texture2D data is not loaded yet for: " + id);
    }

    return _texture2DData.at(id);
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