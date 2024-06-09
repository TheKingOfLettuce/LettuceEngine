#include "LettuceEngine/Assets/Asset.h"

using json = nlohmann::json;

Asset::Asset() {}

Asset::Asset(std::string id) {
    _assetID = id;
}

Asset::~Asset() {}

std::string Asset::GetAssetID() {return _assetID;}

void Asset::SaveToJson(json& j) const {
    j["assetID"] = _assetID;
}

void Asset::LoadFromJson(const json& data) {
    _assetID = data.at("assetID");
}