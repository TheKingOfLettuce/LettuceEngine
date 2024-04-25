#include "CollisionSystem/AABB.h"
#include <stdexcept>
#include <string>
#include "Logging/Log.h"

using json = nlohmann::json;
using LettuceEngine::Math::Vector2;
using LettuceEngine::CollisionSystem::AABB;

AABB::AABB() {
    _halfLengths = Vector2(.5, .5);
    _offset = Vector2();
    CalculateLocalExtents();
}

AABB::AABB(Vector2 halfLengths, Vector2 offset) {
    SetHalfSize(halfLengths);
    SetOffset(offset);
}
AABB::~AABB() {}

Vector2 AABB::GetOffset() const {
    return _offset;
}

Vector2 AABB::GetHalfSize() const {
    return _halfLengths;
}

Vector2 AABB::GetMinExtents() const {
    return _minExtents;
}

Vector2 AABB::GetMaxExtents() const {
    return _maxExtents;
}

void AABB::SetOffset(Vector2 offset) {
    _offset = offset;
    CalculateLocalExtents();
}

void AABB::SetSize(Vector2 size) {
    SetHalfSize(size / 2);
}

void AABB::SetHalfSize(Vector2 halfSize) {
    if (halfSize.X == 0 || halfSize.Y == 0) {
        throw std::invalid_argument(std::string("Cannot set collider size to size 0"));
    }

    if (halfSize.X < 0) {
        Log::Warning("X collider size is negative, correcting to positive.");
        halfSize.X *= -1;
    }
    if (halfSize.Y < 0) {
        Log::Warning("Y collider size is negative, correcting to positive.");
        halfSize.Y *= -1;
    }
    _halfLengths = halfSize;
    CalculateLocalExtents();
}

void AABB::CalculateLocalExtents() {
    _minExtents = _offset - _halfLengths;
    _maxExtents = _offset + _halfLengths;
}

bool AABB::ContainsAABB(AABB other) const {
    if (_minExtents.X > other._minExtents.X || _maxExtents.X < other._maxExtents.X)
        return false;
    if (_minExtents.Y > other._minExtents.Y || _maxExtents.Y < other._maxExtents.Y)
        return false;

    return true;
}

bool AABB::ContainsAABB(AABB other, Vector2 thisOffset, Vector2 otherOffset) const {
    Vector2 minExtents1 = thisOffset + _minExtents;
    Vector2 maxExtents1 = thisOffset + _maxExtents;

    Vector2 minExtents2 = otherOffset + other._minExtents;
    Vector2 maxExtents2 = otherOffset + other._maxExtents;

    if (minExtents1.X > minExtents2.X || maxExtents1.X < maxExtents2.X)
        return false;
    if (minExtents1.Y > minExtents2.Y || maxExtents1.Y < maxExtents2.Y)
        return false;

    return true;
}

bool AABB::ContainsPoint(Vector2 point) const {
    if (point.X < _minExtents.X || point.X > _maxExtents.X)
        return false;
    if (point.Y < _minExtents.Y || point.Y > _maxExtents.Y)
        return false;

    return true;
}

bool AABB::ContainsPoint(Vector2 point, Vector2 offset) const {
    Vector2 minExtents = offset + _minExtents;
    Vector2 maxExtents = offset + _maxExtents;

    if (point.X < minExtents.X || point.X > maxExtents.X)
        return false;
    if (point.Y < minExtents.Y || point.Y > maxExtents.Y)
        return false;

    return true;
}

bool AABB::IntersectsAABB(AABB other) const {
    if (_maxExtents.X < other._minExtents.X || _minExtents.X > other._maxExtents.X)
        return false;
    if (_maxExtents.Y < other._minExtents.Y || _minExtents.Y > other._maxExtents.Y)
        return false;

    return true;
}

bool AABB::IntersectsAABB(AABB other, Vector2 thisOffset, Vector2 otherOffset) const {
    Vector2 minExtents1 = thisOffset + _minExtents;
    Vector2 maxExtents1 = thisOffset + _maxExtents;

    Vector2 minExtents2 = otherOffset + other._minExtents;
    Vector2 maxExtents2 = otherOffset + other._maxExtents;

    if (maxExtents1.X < minExtents2.X || minExtents1.X > maxExtents2.X)
        return false;
    if (maxExtents1.Y < minExtents2.Y || minExtents1.Y > maxExtents2.Y)
        return false;

    return true;
}

void LettuceEngine::CollisionSystem::to_json(json& j, const AABB& box) {
    j = json {
        {"offset", box.GetOffset()},
        {"halfSize", box.GetHalfSize()}
    };
}

void LettuceEngine::CollisionSystem::from_json(const json& j, AABB& box) {
    box.SetOffset(j.at("offset"));
    box.SetHalfSize(j.at("halfSize"));
}