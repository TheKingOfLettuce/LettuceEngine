#pragma once
#include "Raylib/raylib.h"
#include "Assets/ImageAsset.h"
#include "Assets/Texture2DAsset.h"
#include "Assets/AssetManager.h"
#include "Engine.h"

class RaylibAssetManager {
    friend AssetManager;
    friend LettuceEngine::Engine;

    public:
        static Image GetImageData(ImageAsset* asset);
        static Image GetImageData(std::string id);

        static Texture2D GetTexture2DData(Texture2DAsset* asset);
        static Texture2D GetTexture2DData(std::string id);       

    private:
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