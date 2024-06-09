#pragma once

#include <map>
#include <functional>
#include <string>
#include <typeinfo>
#include "LettuceEngine/Logging/Log.h"

template <class Item>
class Factory {
    private:
        inline static std::map<std::string, std::function<Item* ()>> Creators;
        inline static std::map<size_t, std::string> SaveNames;

    public:
        template <class T>
        static void RegisterClass(const std::string &name) {
            static_assert(std::is_base_of<Item, T>{},
            "Provided type must be a Item");
            Creators.insert({name, []() -> Item*
                            { return new T(); }});
            SaveNames.insert({typeid(T).hash_code(), name});
        }

        static Item* Create(const std::string &name) {
            const auto it = Creators.find(name);
            if (it == Creators.end())
                return nullptr; // name is not a registered Item

            return (it->second)();
        }

        template <class T>
        static const std::string GetSaveName() {
            static_assert(std::is_base_of<Item, T>{},
            "Provided type must be a Item");
            return GetSaveName(typeid(T).hash_code());
        }

        static const std::string GetSaveName(const size_t type) {
            const auto it = SaveNames.find(type);
            if (it == SaveNames.end())
                return {}; // name is not a registered Item
            return it->second;
        }
};