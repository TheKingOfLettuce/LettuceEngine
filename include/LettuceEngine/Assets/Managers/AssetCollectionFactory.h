#pragma once

#include "LettuceEngine/Utils/Factory.h"
#include "LettuceEngine/Assets/Managers/AssetCollection.h"

template class Factory<AssetCollection>;

template <class T>
class AssetCollectionCreator {
static_assert(std::is_base_of<AssetCollection, T>{},
"Provided type must be a Asset");
public:
    explicit AssetCollectionCreator(const std::string &name) {
        Log::Info("Registering Asset Collection to factory: " + name);
        Factory<AssetCollection>::RegisterClass<T>(name);
    }
};

#define REGISTER_ASSET_COLLECTION(collectionType) AssetCollectionCreator<collectionType> collectionType##Creator(#collectionType);