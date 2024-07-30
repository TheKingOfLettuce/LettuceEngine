#include "LettuceEngine/CollisionSystem/CollisionSystem2D.h"
#include "LettuceEngine/Math/Vector2.h"
#include <utility>
#include "LettuceEngine/Drawing/BasicDrawing.h"
#include "LettuceEngine/Math/Color.h"
#include "LettuceEngine/Engine.h"

using LettuceEngine::CollisionSystem::AABB;
using LettuceEngine::Math::Vector2;
using LettuceEngine::Math::Color;

Collision2DQuadTree::Collision2DQuadTree(AABB size, int maxObjects) {
    _area = size;
    _objects = std::unordered_set<Collider2D*>();
    for(int i = 0; i < 4; i++) {
        _children[i] = nullptr;
    }
    _maxObjects = maxObjects;
}

Collision2DQuadTree::~Collision2DQuadTree() {
    if (IsLeaf()) return;
    for(int i = 0; i < 4; i++) {
        delete _children[i];
    }
}

void Collision2DQuadTree::Render(RenderMessage* msg) const {
    if (!LettuceEngine::Engine::IsDebugView()) return;
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

    if (_objects.size() < _maxObjects && IsLeaf()) {
        _objects.emplace(object);
        return true;
    }

    if (IsLeaf() && _area.GetHalfSize().X > .5)
        Split();

    if (!IsLeaf()) {
        for (int i = 0; i < 4; i++) {
            if (_children[i]->Insert(object))
                return true;
        }
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
    _children[0] = new Collision2DQuadTree(AABB(newHalfs, newOffset), _maxObjects);
    newOffset = _area.GetOffset() + newHalfs;
    _children[1] = new Collision2DQuadTree(AABB(newHalfs, newOffset), _maxObjects);
    newOffset = _area.GetOffset() - newHalfs;
    _children[2] = new Collision2DQuadTree(AABB(newHalfs, newOffset), _maxObjects);
    newOffset = _area.GetOffset() + Vector2(newHalfs.X, -newHalfs.Y);
    _children[3] = new Collision2DQuadTree(AABB(newHalfs, newOffset), _maxObjects);

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

std::unordered_set<Collider2D*>* Collision2DQuadTree::FindIntersections(const Collider2D* area, std::unordered_set<Collider2D*>* results, size_t numResults) const {
    if (results == nullptr) {
        results = new std::unordered_set<Collider2D*>();
    }
    if (numResults != 0 && results->size() >= numResults)
        return results;
    if (!area->Intersects(_area)) return results;

    for(Collider2D* object : _objects) {
        if (area->Intersects(object))
            results->emplace(object);
        if (numResults != 0 && results->size() >= numResults)
            return results;
    }

    if (IsLeaf()) return results;

    for (int i = 0; i < 4; i++) {
       _children[i]->FindIntersections(area, results);
    }

    return results;
}

std::unordered_set<Collider2D*>* Collision2DQuadTree::FindIntersections(Vector2 point, std::unordered_set<Collider2D*>* results, size_t numResults) const {
    if (results == nullptr) {
        results = new std::unordered_set<Collider2D*>();
    }
    if (numResults != 0 && results->size() >= numResults)
        return results;
    if (!_area.ContainsPoint(point)) return results;

    for(Collider2D* obj : _objects) {
        if (obj->Contains(point))
            results->emplace(obj);
        if (numResults != 0 && results->size() >= numResults)
            return results;
    }

    if (IsLeaf()) return results;

    for (int i = 0; i < 4; i++) {
        _children[i]->FindIntersections(point, results);
    }

    return results;
}

std::unordered_set<Collider2D*>* Collision2DQuadTree::GetAllObjects(std::unordered_set<Collider2D*>* results) {
    if (results == nullptr) {
        results = new std::unordered_set<Collider2D*>();
    }
    for (Collider2D* obj: _objects) {
        results->insert(obj);
    }
    if (IsLeaf())
        return results;
    for (int i = 0; i < 4; i++) {
        _children[i]->GetAllObjects(results);
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