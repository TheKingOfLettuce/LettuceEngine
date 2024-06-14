#include "catch_amalgamated.hpp"
#include "LettuceEngine/CollisionSystem/CollisionSystem2D.h"
#include "LettuceEngine/CollisionSystem/AABB.h"

using LettuceEngine::Math::Vector2;
using LettuceEngine::CollisionSystem::AABB;

const char* CollisionSystem2DTAG = "[CollisionSystem2D]";

TEST_CASE("CollisionSystem2D.Insert Tests", CollisionSystem2DTAG) {
    SECTION("Should allow insert if within area") {
        Collision2DQuadTree system = Collision2DQuadTree(AABB(Vector2(100, 100), Vector2()));
        LettuceObject lettuce1 = LettuceObject();
        lettuce1.SetPosition(Vector2(25, 25));
        Collider2D* collider1 = new Collider2D();
        lettuce1.AddComponent(collider1, false);
        REQUIRE(system.Insert(collider1));

        LettuceObject lettuce2 = LettuceObject();
        lettuce2.SetPosition(Vector2(46.5, 86.27));
        Collider2D* collider2 = new Collider2D();
        lettuce2.AddComponent(collider2, false);
        REQUIRE(system.Insert(collider2));

        LettuceObject lettuce3 = LettuceObject();
        lettuce3.SetPosition(Vector2(90, 5));
        Collider2D* collider3 = new Collider2D();
        lettuce3.AddComponent(collider3, false);
        REQUIRE(system.Insert(collider3));
    }

    SECTION("Should not allow insert if not within area") {
        Collision2DQuadTree system = Collision2DQuadTree(AABB(Vector2(100, 100), Vector2()));
        LettuceObject lettuce1 = LettuceObject();
        lettuce1.SetPosition(Vector2(-25, -25));
        Collider2D* collider1 = new Collider2D();
        lettuce1.AddComponent(collider1, false);
        REQUIRE(system.Insert(collider1));
        
        LettuceObject lettuce2 = LettuceObject();
        lettuce2.SetPosition(Vector2(99.5, 99.5));
        Collider2D* collider2 = new Collider2D();
        lettuce2.AddComponent(collider2, false);
        REQUIRE(system.Insert(collider2));

        LettuceObject lettuce3 = LettuceObject();
        lettuce3.SetPosition(Vector2(0, 0));
        Collider2D* collider3 = new Collider2D();
        lettuce3.AddComponent(collider3, false);
        REQUIRE(system.Insert(collider3));
    }
}

TEST_CASE("CollisionSystem2D.Remove Tests", CollisionSystem2DTAG) {
    SECTION("Should not remove if not added") {
        Collision2DQuadTree system = Collision2DQuadTree(AABB(Vector2(100, 100), Vector2()));
        LettuceObject lettuce1 = LettuceObject();
        lettuce1.SetPosition(Vector2(25, 25));
        Collider2D* collider1 = new Collider2D();
        lettuce1.AddComponent(collider1, false);
        REQUIRE_FALSE(system.Remove(collider1));
    }

    SECTION("Should remove if added") {
        Collision2DQuadTree system = Collision2DQuadTree(AABB(Vector2(100, 100), Vector2()));
        LettuceObject lettuce1 = LettuceObject();
        lettuce1.SetPosition(Vector2(25, 25));
        Collider2D* collider1 = new Collider2D();
        lettuce1.AddComponent(collider1, false);
        REQUIRE(system.Insert(collider1));
        REQUIRE(system.Remove(collider1));
    }

    SECTION("Should remove all if all added") {
        Collision2DQuadTree system = Collision2DQuadTree(AABB(Vector2(100, 100), Vector2()));
        LettuceObject lettuce1 = LettuceObject();
        lettuce1.SetPosition(Vector2(25, 25));
        Collider2D* collider1 = new Collider2D();
        lettuce1.AddComponent(collider1, false);
        REQUIRE(system.Insert(collider1));

        LettuceObject lettuce2 = LettuceObject();
        lettuce2.SetPosition(Vector2(46.5, 86.27));
        Collider2D* collider2 = new Collider2D();
        lettuce2.AddComponent(collider2, false);
        REQUIRE(system.Insert(collider2));

        LettuceObject lettuce3 = LettuceObject();
        lettuce3.SetPosition(Vector2(90, 5));
        Collider2D* collider3 = new Collider2D();
        lettuce3.AddComponent(collider3, false);
        REQUIRE(system.Insert(collider3));

        REQUIRE_FALSE(system.IsEmpty(true));
        REQUIRE(system.Remove(collider1));
        REQUIRE(system.Remove(collider2));
        REQUIRE(system.Remove(collider3));
        REQUIRE(system.IsEmpty(true));
    }
}

TEST_CASE("CollisionSystem2D.FindIntersections Tests", CollisionSystem2DTAG) {
    SECTION("Should find nothing if nothing added with point") {
        Collision2DQuadTree system = Collision2DQuadTree(AABB(Vector2(100, 100), Vector2()));
        std::unordered_set<Collider2D*>* hits = system.FindIntersections(Vector2(25, 25));
        REQUIRE(hits->size() == 0);
        delete hits;
        hits = system.FindIntersections(Vector2(500, 500));
        REQUIRE(hits->size() == 0);
        delete hits;
    }

    SECTION("Should find individual colliders with point") {
        Collision2DQuadTree system = Collision2DQuadTree(AABB(Vector2(100, 100), Vector2()));
        LettuceObject lettuce1 = LettuceObject();
        lettuce1.SetPosition(Vector2(25, 25));
        Collider2D* collider1 = new Collider2D();
        lettuce1.AddComponent(collider1, false);
        REQUIRE(system.Insert(collider1));

        LettuceObject lettuce2 = LettuceObject();
        lettuce2.SetPosition(Vector2(46.5, 86.27));
        Collider2D* collider2 = new Collider2D();
        lettuce2.AddComponent(collider2, false);
        REQUIRE(system.Insert(collider2));

        LettuceObject lettuce3 = LettuceObject();
        lettuce3.SetPosition(Vector2(90, 5));
        Collider2D* collider3 = new Collider2D();
        lettuce3.AddComponent(collider3, false);
        REQUIRE(system.Insert(collider3));

        std::unordered_set<Collider2D*>* hits = system.FindIntersections(Vector2(25, 25));
        REQUIRE(hits->size() == 1);
        REQUIRE_FALSE(hits->find(collider1) == hits->end());
        delete hits;

        hits = system.FindIntersections(Vector2(46.6, 86.37));
        REQUIRE(hits->size() == 1);
        REQUIRE_FALSE(hits->find(collider2) == hits->end());
        delete hits;
    }

    SECTION("Should find overlapped colliders with point") {
        Collision2DQuadTree system = Collision2DQuadTree(AABB(Vector2(100, 100), Vector2()));
        LettuceObject lettuce1 = LettuceObject();
        lettuce1.SetPosition(Vector2(10, 10));
        Collider2D* collider1 = new Collider2D();
        lettuce1.AddComponent(collider1, false);
        REQUIRE(system.Insert(collider1));

        LettuceObject lettuce2 = LettuceObject();
        lettuce2.SetPosition(Vector2(10.25, 10.25));
        Collider2D* collider2 = new Collider2D();
        lettuce2.AddComponent(collider2, false);
        REQUIRE(system.Insert(collider2));

        std::unordered_set<Collider2D*>* hits = system.FindIntersections(Vector2(10.25, 10.25));
        REQUIRE(hits->size() == 2);
        REQUIRE_FALSE(hits->find(collider1) == hits->end());
        REQUIRE_FALSE(hits->find(collider2) == hits->end());
        delete hits;
    }

    SECTION("Should find nothing if nothing added with area") {
        Collision2DQuadTree system = Collision2DQuadTree(AABB(Vector2(100, 100), Vector2()));
        LettuceObject lettuceArea = LettuceObject();
        Collider2D* colliderArea = new Collider2D();
        colliderArea->SetBox(AABB(Vector2(10, 10), Vector2()));
        lettuceArea.AddComponent(colliderArea, false);
        lettuceArea.SetPosition(Vector2(25, 25));
        std::unordered_set<Collider2D*>* hits = system.FindIntersections(colliderArea);
        REQUIRE(hits->size() == 0);
        delete hits;
        hits = system.FindIntersections(Vector2(500, 500));
        REQUIRE(hits->size() == 0);
        delete hits;
    }

    SECTION("Should find individual colliders with area") {
        Collision2DQuadTree system = Collision2DQuadTree(AABB(Vector2(100, 100), Vector2()));
        LettuceObject lettuce1 = LettuceObject();
        lettuce1.SetPosition(Vector2(25, 25));
        Collider2D* collider1 = new Collider2D();
        lettuce1.AddComponent(collider1, false);
        REQUIRE(system.Insert(collider1));

        LettuceObject lettuce2 = LettuceObject();
        lettuce2.SetPosition(Vector2(46.5, 86.27));
        Collider2D* collider2 = new Collider2D();
        lettuce2.AddComponent(collider2, false);
        REQUIRE(system.Insert(collider2));

        LettuceObject lettuce3 = LettuceObject();
        lettuce3.SetPosition(Vector2(90, 5));
        Collider2D* collider3 = new Collider2D();
        lettuce3.AddComponent(collider3, false);
        REQUIRE(system.Insert(collider3));

        LettuceObject lettuceArea = LettuceObject();
        Collider2D* colliderArea = new Collider2D();
        colliderArea->SetBox(AABB(Vector2(10, 10), Vector2()));
        lettuceArea.AddComponent(colliderArea, false);
    
        lettuceArea.SetPosition(Vector2(17, 17));
        std::unordered_set<Collider2D*>* hits = system.FindIntersections(colliderArea);
        REQUIRE(hits->size() == 1);
        REQUIRE_FALSE(hits->find(collider1) == hits->end());
        delete hits;

        lettuceArea.SetPosition(Vector2(46.6, 86.37));
        hits = system.FindIntersections(colliderArea);
        REQUIRE(hits->size() == 1);
        REQUIRE_FALSE(hits->find(collider2) == hits->end());
        delete hits;

        lettuceArea.SetPosition(Vector2(15, 15));
        hits = system.FindIntersections(colliderArea);
        REQUIRE(hits->size() == 1);
        REQUIRE_FALSE(hits->find(collider1) == hits->end());
        delete hits;
    }

    SECTION("Should find overlapped colliders with area") {
        Collision2DQuadTree system = Collision2DQuadTree(AABB(Vector2(100, 100), Vector2()));
        LettuceObject lettuce1 = LettuceObject();
        lettuce1.SetPosition(Vector2(10, 10));
        Collider2D* collider1 = new Collider2D();
        lettuce1.AddComponent(collider1, false);
        REQUIRE(system.Insert(collider1));

        LettuceObject lettuce2 = LettuceObject();
        lettuce2.SetPosition(Vector2(10.25, 10.25));
        Collider2D* collider2 = new Collider2D();
        lettuce2.AddComponent(collider2, false);
        REQUIRE(system.Insert(collider2));

        LettuceObject lettuceArea = LettuceObject();
        Collider2D* colliderArea = new Collider2D();
        colliderArea->SetBox(AABB(Vector2(10, 10), Vector2()));
        lettuceArea.AddComponent(colliderArea, false);

        lettuceArea.SetPosition(Vector2(10.1, 10.1));
        std::unordered_set<Collider2D*>* hits = system.FindIntersections(colliderArea);
        REQUIRE(hits->size() == 2);
        REQUIRE_FALSE(hits->find(collider1) == hits->end());
        REQUIRE_FALSE(hits->find(collider2) == hits->end());
        delete hits;
    }

    SECTION("Should find overlapped colliders with area with max results") {
        Collision2DQuadTree system = Collision2DQuadTree(AABB(Vector2(100, 100), Vector2()));
        LettuceObject lettuce1 = LettuceObject();
        lettuce1.SetPosition(Vector2(10, 10));
        Collider2D* collider1 = new Collider2D();
        lettuce1.AddComponent(collider1, false);
        REQUIRE(system.Insert(collider1));

        LettuceObject lettuce2 = LettuceObject();
        lettuce2.SetPosition(Vector2(10.25, 10.25));
        Collider2D* collider2 = new Collider2D();
        lettuce2.AddComponent(collider2, false);
        REQUIRE(system.Insert(collider2));

        LettuceObject lettuceArea = LettuceObject();
        Collider2D* colliderArea = new Collider2D();
        colliderArea->SetBox(AABB(Vector2(10, 10), Vector2()));
        lettuceArea.AddComponent(colliderArea, false);

        lettuceArea.SetPosition(Vector2(10.1, 10.1));
        std::unordered_set<Collider2D*>* hits = system.FindIntersections(colliderArea);
        REQUIRE(hits->size() == 2);
        delete hits;
        hits = system.FindIntersections(colliderArea, nullptr, 1);
        REQUIRE(hits->size() == 1);
    }
}