#pragma once
#include "LettuceEngine/Components/Component.h"
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>
#include <typeinfo>
#include "LettuceEngine/Utils/json.hpp"
#include "LettuceEngine/Math/Vector2.h"
#include "LettuceEngine/Utils/Callbacks/CallbackWithArg.h"

class Component; // forward declare

class ComponentPair {
        public:
            std::string TypeName;
            nlohmann::json ComponentData;
    };

class LettuceObjectData {
    public:
        LettuceEngine::Math::Vector2 Position;
        LettuceEngine::Math::Vector2 Scale;
        float Rotation;
        bool Enabled;
        std::vector<ComponentPair> ComponentData;
        std::vector<LettuceObjectData> ChildrenData;
};

void to_json(nlohmann::json& j, const ComponentPair& data);
void from_json(const nlohmann::json& j, ComponentPair& data);
void to_json(nlohmann::json& j, const LettuceObjectData& data);
void from_json(const nlohmann::json& j, LettuceObjectData& data);

class LettuceObject {
    public:
        LettuceObject();
        ~LettuceObject();

        // Getters
        LettuceEngine::Math::Vector2 Position() const; 
        float const Rotation() const;
        LettuceEngine::Math::Vector2 Scale() const;
        bool Enabled() const;
        size_t NumChildren() const;
        LettuceObject* GetParent() const;

        // Setters
        void SetPosition(LettuceEngine::Math::Vector2 newPos);
        void SetRotation(float rotation);
        void SetScale(LettuceEngine::Math::Vector2 scale);
        void SetEnable(bool flag);

        // Component Stuff
        void AddComponent(Component* component, bool startEnabled = true);
        bool RemoveComponent(Component* component);
        template <typename T>
        T* RemoveComponent() {
            size_t toRemove = typeid(T).hash_code();
            if (_components->find(toRemove) == _components->end()) return nullptr;
            std::vector<Component*>* componentList = _components->at(toRemove);
            T* toReturn = static_cast<T*>(componentList->at(0));
            componentList->erase(componentList->begin());

            return toReturn;
        }
        template <typename T>
        T* GetComponent() const {
            size_t toRemove = typeid(T).hash_code();
            if (_components->find(toRemove) == _components->end()) return nullptr;
            std::vector<Component*>* componentList = _components->at(toRemove);
            T* toReturn = static_cast<T*>(componentList->at(0));

            return toReturn;
        }
        template <typename T>
        std::vector<T*> GetComponents() const {
            size_t toRemove = typeid(T).hash_code();
            if (_components->find(toRemove) == _components->end()) return std::vector<T*>();
            std::vector<Component*>* componentList = _components->at(toRemove);

            std::vector<T*> toReturn = std::vector<T*>();
            for (size_t i = 0; i < componentList->size(); i++) {
                toReturn.push_back(static_cast<T*>(componentList->operator[](i)));
            }

            return toReturn;
        }
        template <typename T>
        bool HasComponent() const {
            size_t toRemove = typeid(T).hash_code();
            if (_components->find(toRemove) == _components->end()) return false;
            return _components->at(toRemove)->size() != 0;
        }
        void Update(UpdateMessage* msg);
        void Render(RenderMessage* msg) const;

        // Children Stuff
        void AddChild(LettuceObject* child);
        bool RemoveChild(LettuceObject* child);
        LettuceObject* RemoveChildAt(int index);
        LettuceObject* GetChildAt(int index) const;
        int GetChildIndex(LettuceObject* child) const;

        // Misc
        CallbackWithArg<bool>* OnPositionChanged() const;
        void LoadFromData(LettuceObjectData data);
        LettuceObjectData SaveToData() const;
        void Destroy();
        
    protected:
        LettuceEngine::Math::Vector2 _position;
        float _rotation;
        LettuceEngine::Math::Vector2 _scale;
        std::unordered_map<size_t, std::vector<Component*>*>* _components;
        bool _enabled;
        std::vector<LettuceObject*>* _children;
        CallbackWithArg<bool>* _positionChangeCallback;
        LettuceObject* _parent;
};