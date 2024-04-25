#pragma once
#include "MessageSystem/Messages/GameLoopMessages.h"
#include "LettuceObject.h"
#include "Utils/json.hpp"

class LettuceObject; // forward declare

class Component {
    public:
        Component();
        virtual ~Component();

        void virtual Init(LettuceObject* obj);
        void virtual Start();

        void SetEnabled(bool flag);
        bool GetEnabled() const;
        LettuceObject* Lettuce() const;

        void virtual Render(RenderMessage* msg);
        void virtual Update(UpdateMessage* msg);

        // Misc
        std::string SaveToData();
        void LoadFromData(const std::string data);
    protected:
        void virtual Enabled();
        void virtual Disabled();
        void virtual SaveToJson(nlohmann::json& j);
        void virtual LoadFromJson(const nlohmann::json& data);

        LettuceObject* _lettuce;
        bool _enabled;
};