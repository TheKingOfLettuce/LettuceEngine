#include "LettuceEngine/Components/Collision/Collider2D.h"
#include <stdexcept>
#include <string>
#include "LettuceEngine/Engine.h"
#include "LettuceEngine/CollisionSystem/CollisionSystem2D.h"
#include "LettuceEngine/Drawing/BasicDrawing.h"
#include "LettuceEngine/Math/Color.h"
#include "LettuceEngine/Components/ComponentFactory.h"
REGISTER_COMPONENT(Collider2D)

using json = nlohmann::json;
using LettuceEngine::Math::Vector2;
using LettuceEngine::Math::Color;

Collider2D::Collider2D() : Component() {
    _box = LettuceEngine::CollisionSystem::AABB();
}
Collider2D::~Collider2D() {
    if (_enabled)
        SetEnabled(false);
}

void Collider2D::Enabled() {
    _callbackID = _lettuce->OnPositionChanged()->AddCallback(&Collider2D::PositionChange, this);
    Collision2DQuadTree* system = LettuceEngine::Engine::CollisionSystem();
    if (!system->Insert(this))
        Log::Warning("Collider was not inserted into the system");
}

void Collider2D::Disabled() {
    _lettuce->OnPositionChanged()->RemoveCallback(_callbackID);
    Collision2DQuadTree* system = LettuceEngine::Engine::CollisionSystem();
    system->Remove(this);
}

void Collider2D::PositionChange(bool hasChanged) {
    Collision2DQuadTree* system = LettuceEngine::Engine::CollisionSystem();
    if (hasChanged)
        system->Insert(this);
    else
        system->Remove(this);
}

const LettuceEngine::CollisionSystem::AABB Collider2D::GetBox() const {
    return _box;
}

void Collider2D::SetBox(LettuceEngine::CollisionSystem::AABB box) {
    Collision2DQuadTree* system = LettuceEngine::Engine::CollisionSystem();
    if (_enabled)
        system->Remove(this);
    _box = box;
    if (_enabled)
        system->Insert(this);
}

void Collider2D::Render(RenderMessage* msg) {
    if (!LettuceEngine::Engine::IsDebugView()) return;
    BasicDrawing::DrawRectangleLines(_box.GetOffset() + _lettuce->Position(), Color(0, 255, 0, 255), _box.GetHalfSize());
}

bool Collider2D::Contains(const Collider2D* other) const {
    return _box.ContainsAABB(other->_box, _lettuce->Position(), other->_lettuce->Position());
}

bool Collider2D::Contains(const LettuceEngine::CollisionSystem::AABB box) const {
    return _box.ContainsAABB(box, _lettuce->Position(), Vector2());
}

bool Collider2D::Contains(const Vector2 point) const {
    return _box.ContainsPoint(point, _lettuce->Position());
}

bool Collider2D::Intersects(const Collider2D* other) const {
    return _box.IntersectsAABB(other->_box, _lettuce->Position(), other->_lettuce->Position());
}

bool Collider2D::Intersects(const LettuceEngine::CollisionSystem::AABB box) const {
    return _box.IntersectsAABB(box, _lettuce->Position(), Vector2());
}

bool Collider2D::ContainedWithin(const LettuceEngine::CollisionSystem::AABB other) const {
    return other.ContainsAABB(_box, Vector2(), _lettuce->Position());
}

void Collider2D::SaveToJson(json& j) {
    Component::SaveToJson(j);
    j["boundingBox"] = _box;
}

void Collider2D::LoadFromJson(const json& j) {
    _box = j.at("boundingBox");
    Component::LoadFromJson(j);
}