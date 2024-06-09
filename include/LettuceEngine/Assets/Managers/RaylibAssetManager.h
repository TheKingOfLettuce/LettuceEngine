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
        static Image GetImageData(ImageAsset* asset);
        static Image GetImageData(std::string id);
        static bool HasImageData(ImageAsset* asset);
        static bool HasImageData(std::string id);

        static Texture2D GetTexture2DData(Texture2DAsset* asset);
        static Texture2D GetTexture2DData(std::string id); 
        static bool HasTexture2DData(Texture2DAsset* asset);
        static bool HasTexture2DData(std::string id);      

    private:
        static void LoadAllAssetManagerGPUData();
        static void UnloadAllAssetManagerGPUData();

        static bool AddImageAsset(ImageAsset* asset);
        static bool AddTexture2DAsset(Texture2DAsset* asset);

        static void RemoveImageData(ImageAsset* asset);
        static void RemoveImageData(std::string id);
        static void RemoveTexture2DData(Texture2DAsset* asset);
        static void RemoveTexture2DData(std::string id);

        static void RemoveAllData();
        static void RemoveAllImageData();
        static void RemoveAllTexture2DData();
};