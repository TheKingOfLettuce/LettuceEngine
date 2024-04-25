#pragma once

#include <map>
#include <functional>
#include <string>
#include <typeinfo>
#include "Component.h"
#include "Logging/Log.h"

class Component;

class ComponentFactory {
    private:
        inline static std::map<std::string, std::function<Component* ()>> Creators;
        inline static std::map<size_t, std::string> SaveNames;

    public:
        template <class T>
        static void RegisterClass(const std::string &name) {
            Creators.insert({name, []() -> Component*
                            { return new T(); }});
            SaveNames.insert({typeid(T).hash_code(), name});
        }

        static Component* Create(const std::string &name) {
            const auto it = Creators.find(name);
            if (it == Creators.end())
                return nullptr; // name is not a registered component

            return (it->second)();
        }

        template <class T>
        static const std::string GetSaveName() {
            return GetSaveName(typeid(T).hash_code());
        }

        static const std::string GetSaveName(const size_t type) {
            const auto it = SaveNames.find(type);
            if (it == SaveNames.end())
                return {}; // name is not a registered component
            return it->second;
        }
};

template <class T>
class Creator {
public:
    explicit Creator(const std::string &name) {
        Log::Info("Registering component to factory: " + name);
        ComponentFactory::RegisterClass<T>(name);
    }
};

#define REGISTER(derived_class) Creator<derived_class> derived_class##Creator(#derived_class);