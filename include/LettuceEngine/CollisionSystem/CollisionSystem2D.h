#pragma once
#include "LettuceEngine/CollisionSystem/AABB.h"
#include "LettuceEngine/Components/Collision/Collider2D.h"
#include <unordered_set>

class Collision2DQuadTree {
    public:
        Collision2DQuadTree(LettuceEngine::CollisionSystem::AABB size, int maxObjects = 4);
        ~Collision2DQuadTree();

        void Render(RenderMessage* msg) const;

        bool Insert(Collider2D* object);
        bool Remove(Collider2D* object);
        bool IsEmpty(bool includeChildren) const;

        std::unordered_set<Collider2D*>* FindIntersections(const Collider2D* area, std::unordered_set<Collider2D*>* results = nullptr, size_t numResults = 0) const;
        std::unordered_set<Collider2D*>* FindIntersections(LettuceEngine::Math::Vector2 point, std::unordered_set<Collider2D*>* results = nullptr, size_t numResults = 0) const;
        std::unordered_set<Collider2D*>* GetAllObjects(std::unordered_set<Collider2D*>* results = nullptr);
    private:
        LettuceEngine::CollisionSystem::AABB _area;
        std::unordered_set<Collider2D*> _objects;
        Collision2DQuadTree* _children[4];
        int _maxObjects;

        void Split();
        void Unsplit();
        bool IsLeaf() const;
};