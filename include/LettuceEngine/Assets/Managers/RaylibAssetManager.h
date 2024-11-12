#pragma once
#include "Raylib/raylib.h"
#include "LettuceEngine/Assets/ImageAsset.h"
#include "LettuceEngine/Assets/Texture2DAsset.h"
#include "LettuceEngine/Assets/Managers/AssetManager.h"
#include "LettuceEngine/Engine.h"

class RaylibAssetManager {
    friend AssetManager;
    friend LettuceEngine::Engine;
    friend ImageAssetCollection;
    friend Texture2DAssetCollection;

    public:
        static Image GetImageData(const ImageAsset* asset);
        static Image GetImageData(const std::string id);
        static bool HasImageData(const ImageAsset* asset);
        static bool HasImageData(const std::string id);

        static Texture2D GetTexture2DData(const Texture2DAsset* asset);
        static Texture2D GetTexture2DData(const std::string id); 
        static bool HasTexture2DData(const Texture2DAsset* asset);
        static bool HasTexture2DData(const std::string id);      

    private:
        static void LoadAllAssetManagerGPUData();
        static void UnloadAllAssetManagerGPUData();

        static bool AddImageAsset(const ImageAsset* asset);
        static bool AddImageData(const Image data, std::string id);
        static bool AddTexture2DAsset(const Texture2DAsset* asset);
        static bool AddTexture2DData(const Texture2D data, std::string id);

        static void RemoveImageData(const ImageAsset* asset);
        static void RemoveImageData(const std::string id);
        static void RemoveTexture2DData(const Texture2DAsset* asset);
        static void RemoveTexture2DData(const std::string id);

        static void RemoveAllData();
        static void RemoveAllImageData();
        static void RemoveAllTexture2DData();
};