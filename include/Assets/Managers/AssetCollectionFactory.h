#pragma once

#include "Utils/Factory.h"
#include "Assets/Managers/AssetCollection.h"

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

#define REGISTER_ASSET_COLLECTION(derived_class) AssetCollectionCreator<derived_class> derived_class##Creator(#derived_class);