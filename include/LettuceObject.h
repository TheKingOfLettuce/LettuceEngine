#pragma once
#include "Components/Component.h"
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>
#include <typeinfo>
#include "Utils/json.hpp"
#include "Math/Vector2.h"
#include "Utils/LinkedList.h"
#include "Utils/Callbacks/CallbackWithArg.h"

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
        float const Rotation();
        LettuceEngine::Math::Vector2 Scale() const;
        bool const Enabled();
        size_t const NumChildren();

        // Setters
        void SetPosition(LettuceEngine::Math::Vector2 newPos);
        void SetEnable(bool flag);

        // Component Stuff
        void AddComponent(Component* component, bool startEnabled = true);
        bool RemoveComponent(Component* component);
        template <typename T>
        T* RemoveComponent() {
            size_t toRemove = typeid(T).hash_code();
            if (_components->find(toRemove) == _components->end()) return nullptr;
            LinkedList<Component*>* componentList = _components->at(toRemove);
            T* toReturn = static_cast<T*>(componentList->RemoveAt(0));
            if (componentList->Size() == 0) {
                delete componentList;
                _components->erase(toRemove);
            }

            return toReturn;
        }
        template <typename T>
        T* GetComponent() {
            size_t toRemove = typeid(T).hash_code();
            if (_components->find(toRemove) == _components->end()) return nullptr;
            LinkedList<Component*>* componentList = _components->at(toRemove);
            T* toReturn = static_cast<T*>(componentList->Get(0));

            return toReturn;
        }
        template <typename T>
        std::vector<T*> GetComponents() {
            size_t toRemove = typeid(T).hash_code();
            if (_components->find(toRemove) == _components->end()) return std::vector<T*>();
            LinkedList<Component*>* componentList = _components->at(toRemove);

            std::vector<T*> toReturn = std::vector<T*>();
            for (int i = 0; i < componentList->Size(); i++) {
                toReturn.push_back(static_cast<T*>(componentList->Get(i)));
            }

            return toReturn;
        }
        template <typename T>
        bool HasComponent() {
            size_t toRemove = typeid(T).hash_code();
            return _components->find(toRemove) != _components->end();
        }
        void Update(UpdateMessage* msg);
        void Render(RenderMessage* msg);

        // Children Stuff
        void AddChild(LettuceObject* child);
        bool RemoveChild(LettuceObject* child);
        LettuceObject* RemoveChildAt(int index);
        LettuceObject* GetChildAt(int index);
        int GetChildIndex(LettuceObject* child);

        // Misc
        CallbackWithArg<bool>* OnPositionChanged();
        void LoadFromData(LettuceObjectData data);
        LettuceObjectData SaveToData();
        
    protected:
        LettuceEngine::Math::Vector2 _position;
        float _rotation;
        LettuceEngine::Math::Vector2 _scale;
        std::unordered_map<size_t, LinkedList<Component*>*>* _components;
        bool _enabled;
        std::vector<LettuceObject*>* _children;
        CallbackWithArg<bool>* _positionChangeCallback;
};