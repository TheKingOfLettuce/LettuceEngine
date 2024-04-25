#pragma once
#include "CollisionSystem/AABB.h"
#include "Components/Collision/Collider2D.h"
#include <unordered_set>

class Collision2DQuadTree {
    public:
        Collision2DQuadTree(LettuceEngine::CollisionSystem::AABB size);
        ~Collision2DQuadTree();

        void Render(RenderMessage* msg) const;

        bool Insert(Collider2D* object);
        bool Remove(Collider2D* object);
        bool IsEmpty(bool includeChildren) const;

        std::unordered_set<Collider2D*>* FindIntersections(const Collider2D* area, std::unordered_set<Collider2D*>* results = nullptr) const;
        std::unordered_set<Collider2D*>* FindIntersections(LettuceEngine::Math::Vector2 point, std::unordered_set<Collider2D*>* results = nullptr) const;
    private:
        LettuceEngine::CollisionSystem::AABB _area;
        std::unordered_set<Collider2D*> _objects;
        Collision2DQuadTree* _children[4];

        void Split();
        void Unsplit();
        bool IsLeaf() const;
};