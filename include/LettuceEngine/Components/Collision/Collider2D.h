#pragma once
#include "LettuceEngine/Components/Component.h"
#include "LettuceEngine/Math/Vector2.h"
#include "LettuceEngine/CollisionSystem/AABB.h"

class Collider2D : public Component {
    public:
        Collider2D();
        ~Collider2D();

        const LettuceEngine::CollisionSystem::AABB GetBox() const;
        void SetBox(const LettuceEngine::CollisionSystem::AABB box);

        void Render(RenderMessage* msg) override;

        bool ContainedWithin(const LettuceEngine::CollisionSystem::AABB other) const;
        bool Contains(const Collider2D* other) const;
        bool Contains(const LettuceEngine::CollisionSystem::AABB other) const;
        bool Contains(const LettuceEngine::Math::Vector2 point) const;
        bool Intersects(const Collider2D* other) const;
        bool Intersects(const LettuceEngine::CollisionSystem::AABB other) const;
    protected:
        LettuceEngine::CollisionSystem::AABB _box;

        void Enabled() override;
        void Disabled() override;
        void PositionChange(bool preUpdate);

        void SaveToJson(nlohmann::json& j) override;
        void LoadFromJson(const nlohmann::json& data) override;
    private:
        CallbackID _callbackID;
};