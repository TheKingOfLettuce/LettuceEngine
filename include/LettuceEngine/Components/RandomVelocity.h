#pragma once
#include "LettuceEngine/Components/Component.h"

class RandomVelocity : public Component {
    public:
        RandomVelocity();
        ~RandomVelocity();


        LettuceEngine::Math::Vector2 GetVelocity() const;
        void SetVelocity(LettuceEngine::Math::Vector2 vel);
        float GetVelocityScale() const;
        void SetVelocityScale(float scale);
    protected:
        void SaveToJson(nlohmann::json& j) override;
        void LoadFromJson(const nlohmann::json& data) override;

        void Update(UpdateMessage* message) override;

    protected:
        LettuceEngine::Math::Vector2 _velocity;
        float _velocityScale;
};