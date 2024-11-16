#include "LettuceEngine/Assets/Managers/AssetManager.h"
#include "LettuceEngine/Assets/Managers/RaylibAssetManager.h"
#include "LettuceEngine/Assets/Managers/AssetTypeCollection.h"
#include "LettuceEngine/Engine.h"
#include "LettuceEngine/Assets/Managers/AssetCollectionFactory.h"
REGISTER_ASSET_COLLECTION(ImageAssetCollection);
REGISTER_ASSET_COLLECTION(Texture2DAssetCollection);

ImageAssetCollection::ImageAssetCollection() : AssetTypeCollection<ImageAsset>() {}

bool ImageAssetCollection::AddAsset(ImageAsset* asset) {
    bool added = AssetTypeCollection::AddAsset(asset);
    if (added)
        RaylibAssetManager::AddImageAsset(asset);
    return added;
}

Asset* ImageAssetCollection::RemoveAsset(std::string id) {
    Asset* removed = AssetTypeCollection::RemoveAsset(id);
    if (removed)
        RaylibAssetManager::RemoveImageData(id);
    return removed;
}

Texture2DAssetCollection::Texture2DAssetCollection() : AssetTypeCollection<Texture2DAsset>() {}

bool Texture2DAssetCollection::AddAsset(Texture2DAsset* asset) {
    bool added = AssetTypeCollection::AddAsset(asset);
    if (added && LettuceEngine::Engine::IsRunning())
        RaylibAssetManager::AddTexture2DAsset(asset);
    return added;
}

Asset* Texture2DAssetCollection::RemoveAsset(std::string id) {
    Asset* removed = AssetTypeCollection::RemoveAsset(id);
    if (removed)
        RaylibAssetManager::RemoveTexture2DData(id);
    return removed;
}

std::unordered_map<size_t, AssetCollection*> AssetManager::_assets = std::unordered_map<size_t, AssetCollection*>
{
    // engine level asset collections
    {typeid(ImageAsset).hash_code(), new ImageAssetCollection()},
    {typeid(Texture2DAsset).hash_code(), new Texture2DAssetCollection()}
};

void AssetManager::UnloadAllAssets() {
    for(auto& pair : _assets) {
        delete pair.second;
    }
    _assets.clear();
    AddEngineCollections();
}

void AssetManager::AddEngineCollections() {
    _assets.emplace(typeid(ImageAsset).hash_code(), new ImageAssetCollection());
    _assets.emplace(typeid(Texture2DAsset).hash_code(), new Texture2DAssetCollection());
}

bool AssetManager::HasAssetType(size_t typeID) {
    return _assets.find(typeID) != _assets.end();
}

bool AssetManager::AddAsset(Asset* asset, bool addDefaultCollection) {
    if (asset == nullptr) {
        throw std::invalid_argument("Provided asset is null");
    }
    size_t typeID = typeid(*asset).hash_code();
    if (!HasAssetType(typeID)) {
        if (!addDefaultCollection) return false;
        AddAssetCollection(new AssetCollection(), typeID);
    }

    return _assets.at(typeID)->AddAsset(asset);
}

bool AssetManager::AddAssetCollection(AssetCollection* collection, size_t assetType) {
    if (collection == nullptr) {
        throw std::invalid_argument("Provided collection is null");
    }
    if (HasAssetType(assetType)) return false;
    _assets.emplace(assetType, collection);
    return true;
}

using json = nlohmann::json;

void AssetManager::SaveToJson(json& j) {
    std::vector<std::pair<std::string, json>> saveData = std::vector<std::pair<std::string, json>>();
    for(const auto& assetCollectionPair : _assets) {
        if (!assetCollectionPair.second->ShouldSave())
            continue;
        const std::type_info& collectionType = typeid(*assetCollectionPair.second);
        std::string saveName = "";
        if (collectionType != typeid(AssetCollection)) {
            saveName = Factory<AssetCollection>::GetSaveName(typeid(*assetCollectionPair.second).hash_code());
            if (saveName.empty()) {
                Log::Warning("Cannot persist Unique AssetCollection " + std::string(typeid(*assetCollectionPair.second).name(), " saving as default collection"));
                saveName = "";
            }
        }
        else if (!assetCollectionPair.second->HasAssets()) {
            // default collection with no assets, dont save
            continue;
        }

        json assetData;
        assetCollectionPair.second->SaveToJson(assetData);
        std::pair<std::string, json> assetCollectionData = std::pair<std::string, json>(saveName, assetData);
        saveData.push_back(assetCollectionData);
    }

    j["assetData"] = saveData;
}

void AssetManager::LoadFromJson(const json& data, bool additive) {
    std::vector<std::pair<std::string, json>> saveData = data.at("assetData");
    if (!additive)
        _assets.clear();
        // could add engine collections here if we dont want third-party ways to handle engine data
    for(const auto& assetCollectionPair : saveData) {
        AssetCollection* collection;
        bool isDefaultCollection = assetCollectionPair.first == "";
        if (!isDefaultCollection) {
            collection = Factory<AssetCollection>::Create(assetCollectionPair.first);
            if (collection == nullptr) {
                Log::Error("Failed to create asset collection from save name: " + assetCollectionPair.first);
                continue;
            }
        }
        else {
            collection = new AssetCollection();
        }
        collection->LoadFromJson(assetCollectionPair.second);
        // hack for default collection, 
        // Assets are deserialized fine but collection->GetAssetType() returns default Asset type instead of concrete
        // if we walk through the assets, it will know to assoicate the concrete type with default collection
        if (isDefaultCollection || !AddAssetCollection(collection, collection->GetAssetType())) {
            for(Asset* asset : collection->GetAllAssets()) {
                if (!AddAsset(asset, isDefaultCollection)) {
                    Log::Error("Failed to add asset to existing collection with name " + asset->GetAssetID());
                    continue;
                }
                collection->RemoveAsset(asset);
            }
            delete collection;
        }
    }
    if (!additive)
        // ensure engine collections are there
        AddEngineCollections();
}