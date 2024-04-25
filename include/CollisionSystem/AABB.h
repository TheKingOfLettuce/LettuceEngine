#pragma once
#include "Math/Vector2.h"

namespace LettuceEngine::CollisionSystem {

class AABB {
    public:
        AABB(LettuceEngine::Math::Vector2 halfLengths, LettuceEngine::Math::Vector2 offset);
        AABB();
        ~AABB();

        void SetOffset(LettuceEngine::Math::Vector2 offset);
        void SetSize(LettuceEngine::Math::Vector2 size);
        void SetHalfSize(LettuceEngine::Math::Vector2 halfSize);

        LettuceEngine::Math::Vector2 GetOffset() const;
        LettuceEngine::Math::Vector2 GetHalfSize() const;
        LettuceEngine::Math::Vector2 GetMinExtents() const;
        LettuceEngine::Math::Vector2 GetMaxExtents() const;

        bool ContainsAABB(AABB other) const;
        bool ContainsAABB(AABB other, LettuceEngine::Math::Vector2 thisOffset, LettuceEngine::Math::Vector2 otherOffset) const;
        bool ContainsPoint(LettuceEngine::Math::Vector2 point) const;
        bool ContainsPoint(LettuceEngine::Math::Vector2 point, LettuceEngine::Math::Vector2 offset) const;
        bool IntersectsAABB(AABB other) const;
        bool IntersectsAABB(AABB other, LettuceEngine::Math::Vector2 thisOffset, LettuceEngine::Math::Vector2 otherOffset) const;
    protected:
        LettuceEngine::Math::Vector2 _offset;
        LettuceEngine::Math::Vector2 _halfLengths;
        LettuceEngine::Math::Vector2 _minExtents;
        LettuceEngine::Math::Vector2 _maxExtents;

        void CalculateLocalExtents();
};

void to_json(nlohmann::json& j, const AABB& v);
void from_json(const nlohmann::json& j, AABB& v);

}