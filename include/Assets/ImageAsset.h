#pragma once
#include "Assets/Asset.h"

class ImageAsset : public Asset {
    public:
        ImageAsset(std::string filePath, std::string id);
        ~ImageAsset();

        std::string GetFilePath();
    private:
        std::string _filePath;
};