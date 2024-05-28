#pragma once

#include <map>
#include <functional>
#include <string>
#include <typeinfo>
#include "Assets/Asset.h"
#include "Logging/Log.h"

class AssetFactory {
    private:
        inline static std::map<std::string, std::function<Asset* ()>> Creators;
        inline static std::map<size_t, std::string> SaveNames;

    public:
        template <class T>
        static void RegisterClass(const std::string &name) {
            static_assert(std::is_base_of<Asset, T>{},
            "Provided type must be a Asset");
            Creators.insert({name, []() -> Asset*
                            { return new T(); }});
            SaveNames.insert({typeid(T).hash_code(), name});
        }

        static Asset* Create(const std::string &name) {
            const auto it = Creators.find(name);
            if (it == Creators.end())
                return nullptr; // name is not a registered Asset

            return (it->second)();
        }

        template <class T>
        static const std::string GetSaveName() {
            static_assert(std::is_base_of<Asset, T>{},
            "Provided type must be a Asset");
            return GetSaveName(typeid(T).hash_code());
        }

        static const std::string GetSaveName(const size_t type) {
            const auto it = SaveNames.find(type);
            if (it == SaveNames.end())
                return {}; // name is not a registered Asset
            return it->second;
        }
};

template <class T>
class AssetCreator {
static_assert(std::is_base_of<Asset, T>{},
"Provided type must be a Asset");
public:
    explicit AssetCreator(const std::string &name) {
        Log::Info("Registering Asset to factory: " + name);
        AssetFactory::RegisterClass<T>(name);
    }
};

#define REGISTER_ASSET(derived_class) AssetCreator<derived_class> derived_class##ACreator(#derived_class);