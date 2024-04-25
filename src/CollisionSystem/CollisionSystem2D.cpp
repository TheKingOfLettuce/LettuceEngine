#include "CollisionSystem/CollisionSystem2D.h"
#include "Math/Vector2.h"
#include <utility>
#include "Drawing/BasicDrawing.h"
#include "Math/Color.h"

using LettuceEngine::CollisionSystem::AABB;
using LettuceEngine::Math::Vector2;
using LettuceEngine::Math::Color;

static const int MAX_OBJECTS = 4;

Collision2DQuadTree::Collision2DQuadTree(AABB size) {
    _area = size;
    _objects = std::unordered_set<Collider2D*>();
    for(int i = 0; i < 4; i++) {
        _children[i] = nullptr;
    }
}

Collision2DQuadTree::~Collision2DQuadTree() {
    if (IsLeaf()) return;
    for(int i = 0; i < 4; i++) {
        delete _children[i];
    }
}

void Collision2DQuadTree::Render(RenderMessage* msg) const {
    if (IsLeaf()) {
        BasicDrawing::DrawRectangleLines(_area.GetOffset(), Color(0, 0, 255, 255), _area.GetHalfSize());
        return;
    }

    for(int i = 0; i < 4; i++) {
        _children[i]->Render(msg);
    }
}

bool Collision2DQuadTree::Insert(Collider2D* object) {
    if (!object->Intersects(_area)) return false;

    if (_objects.size() < MAX_OBJECTS && IsLeaf()) {
        _objects.emplace(object);
        return true;
    }

    if (IsLeaf())
        Split();

    for (int i = 0; i < 4; i++) {
        if (_children[i]->Insert(object))
            return true;
    }

    _objects.emplace(object);
    return true;
}

bool Collision2DQuadTree::Remove(Collider2D* object) {
    if (!object->Intersects(_area)) 
        return false;
    bool didRemove = _objects.erase(object);
    if (IsLeaf()) 
        return didRemove;

    for(int i = 0; i < 4; i++) {
        if (_children[i]->Remove(object)) {
            didRemove = true;
            break;
        }
    }

    if (!didRemove) 
        return false;
    for (int i = 0; i < 4; i++) {
        if (!_children[i]->IsEmpty(true)) 
            return true;
    }

    Unsplit();
    return true;
}

void Collision2DQuadTree::Split() {
    if (_children[0] != nullptr) return;
    Vector2 newHalfs = _area.GetHalfSize() / 2;
    Vector2 newOffset = _area.GetOffset() + Vector2(-newHalfs.X, newHalfs.Y);
    _children[0] = new Collision2DQuadTree(AABB(newHalfs, newOffset));
    newOffset = _area.GetOffset() + newHalfs;
    _children[1] = new Collision2DQuadTree(AABB(newHalfs, newOffset));
    newOffset = _area.GetOffset() - newHalfs;
    _children[2] = new Collision2DQuadTree(AABB(newHalfs, newOffset));
    newOffset = _area.GetOffset() + Vector2(newHalfs.X, -newHalfs.Y);
    _children[3] = new Collision2DQuadTree(AABB(newHalfs, newOffset));

    std::unordered_set<Collider2D*> newValues = std::unordered_set<Collider2D*>();
    for(Collider2D* object : _objects) {
        bool addedToChild = false;
        for(int i = 0; i < 4; i++) {
            if (_children[i]->Insert(object)) {
                addedToChild = true;
                break;
            }
        }

        if (!addedToChild) {
            newValues.emplace(object);
        }
    }

    _objects = std::move(newValues);
}

std::unordered_set<Collider2D*>* Collision2DQuadTree::FindIntersections(const Collider2D* area, std::unordered_set<Collider2D*>* results) const {
    if (results == nullptr) {
        results = new std::unordered_set<Collider2D*>();
    }

    if (!area->Intersects(_area)) return results;

    for(Collider2D* object : _objects) {
        if (area->Intersects(object))
            results->emplace(object);
    }

    if (IsLeaf()) return results;

    for (int i = 0; i < 4; i++) {
       _children[i]->FindIntersections(area, results);
    }

    return results;
}

std::unordered_set<Collider2D*>* Collision2DQuadTree::FindIntersections(Vector2 point, std::unordered_set<Collider2D*>* results) const {
    if (results == nullptr) {
        results = new std::unordered_set<Collider2D*>();
    }
    if (!_area.ContainsPoint(point)) return results;

    for(Collider2D* obj : _objects) {
        if (obj->Contains(point))
            results->emplace(obj);
    }

    if (IsLeaf()) return results;

    for (int i = 0; i < 4; i++) {
        _children[i]->FindIntersections(point, results);
    }

    return results;
}

void Collision2DQuadTree::Unsplit() {
    for(int i = 0; i < 4; i++) {
        delete _children[i];
        _children[i] = nullptr;
    }
}

bool Collision2DQuadTree::IsLeaf() const {
    return _children[0] == nullptr;
}

bool Collision2DQuadTree::IsEmpty(bool includeChildren) const {
    if (!_objects.empty())
        return false;
    if (!includeChildren || IsLeaf())
        return true;

    for (int i = 0; i < 4; i++) {
        if (!_children[i]->IsEmpty(true))
            return false;
    }

    return true;
}