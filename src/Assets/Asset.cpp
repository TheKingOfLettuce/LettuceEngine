#include "Assets/Asset.h"

Asset::Asset(std::string id) {
    _assetID = id;
}

Asset::~Asset() {}

std::string Asset::GetAssetID() {return _assetID;}