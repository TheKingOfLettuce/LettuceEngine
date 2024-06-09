#include "catch_amalgamated.hpp"
#include "LettuceEngine/CollisionSystem/AABB.h"

using LettuceEngine::Math::Vector2;
using LettuceEngine::CollisionSystem::AABB;

const char* AABBTAG = "[AABB]";

TEST_CASE("AABB.Construction Tests", AABBTAG) {
    SECTION("Should default construct with unit size") {
        AABB box = AABB();
        Vector2 halfSize = box.GetHalfSize();
        REQUIRE(halfSize == Vector2(.5, .5));
        Vector2 offSet = box.GetOffset();
        REQUIRE(offSet == Vector2());
    }

    SECTION("Should construct with vectors") {
        Vector2 halfSize = Vector2(18, 7);
        Vector2 offSet = Vector2(1005, 54);
        AABB box = AABB(halfSize, offSet);
        REQUIRE(halfSize == box.GetHalfSize());
        REQUIRE(offSet == box.GetOffset());
    }
}

TEST_CASE("AABB.SetOffset Tests", AABBTAG) {
    SECTION("Should set offset") {
        AABB box = AABB();
        Vector2 newOffset = Vector2(55, -67);
        REQUIRE(box.GetOffset() != newOffset);
        box.SetOffset(newOffset);
        REQUIRE(newOffset == box.GetOffset());
    }
}

TEST_CASE("AABB.SetSize Tests", AABBTAG) {
    SECTION("Should set full size") {
        AABB box = AABB();
        Vector2 fullSize = Vector2(4, 4);
        REQUIRE(box.GetHalfSize() == Vector2(.5, .5));
        box.SetSize(fullSize);
        REQUIRE(fullSize / 2 == box.GetHalfSize());
    }

    SECTION("Should correct size when X is negative") {
        AABB box = AABB();
        REQUIRE(box.GetHalfSize() == Vector2(.5, .5));
        box.SetSize(Vector2(-4, 4));
        REQUIRE(Vector2(2, 2) == box.GetHalfSize());
    }

    SECTION("Should correct size when Y is negative") {
        AABB box = AABB();
        REQUIRE(box.GetHalfSize() == Vector2(.5, .5));
        box.SetSize(Vector2(4, -4));
        REQUIRE(Vector2(2, 2) == box.GetHalfSize());
    }

    SECTION("Should correct size when X and Y is negative") {
        AABB box = AABB();
        REQUIRE(box.GetHalfSize() == Vector2(.5, .5));
        box.SetSize(Vector2(-4, -4));
        REQUIRE(Vector2(2, 2) == box.GetHalfSize());
    }
}

TEST_CASE("AABB.SetHalfSize Tests", AABBTAG) {
    SECTION("Should set full size") {
        AABB box = AABB();
        REQUIRE(box.GetHalfSize() == Vector2(.5, .5));
        box.SetHalfSize(Vector2(4, 4));
        REQUIRE(Vector2(4, 4) == box.GetHalfSize());
    }

    SECTION("Should correct size when X is negative") {
        AABB box = AABB();
        REQUIRE(box.GetHalfSize() == Vector2(.5, .5));
        box.SetHalfSize(Vector2(-4, 4));
        REQUIRE(Vector2(4, 4) == box.GetHalfSize());
    }

    SECTION("Should correct size when Y is negative") {
        AABB box = AABB();
        REQUIRE(box.GetHalfSize() == Vector2(.5, .5));
        box.SetHalfSize(Vector2(4, -4));
        REQUIRE(Vector2(4, 4) == box.GetHalfSize());
    }

    SECTION("Should correct size when X and Y is negative") {
        AABB box = AABB();
        REQUIRE(box.GetHalfSize() == Vector2(.5, .5));
        box.SetHalfSize(Vector2(-4, -4));
        REQUIRE(Vector2(4, 4) == box.GetHalfSize());
    }
}


TEST_CASE("AABB.GetMinExtents Tests", AABBTAG) {
    SECTION("Should default to negative half unit vector") {
        AABB box = AABB();
        REQUIRE(box.GetMinExtents() == Vector2(-.5, -.5));
    }

    SECTION("Should set min extents to negative set half size") {
        AABB box = AABB();
        box.SetHalfSize(Vector2(10, 10));
        REQUIRE(box.GetMinExtents() == Vector2(-10, -10));
    }

    SECTION("Should set min extents to negative set half size + offset") {
        AABB box = AABB();
        box.SetHalfSize(Vector2(10, 10));
        box.SetOffset(Vector2(5, 5));
        REQUIRE(box.GetMinExtents() == Vector2(-5, -5));
    }

    SECTION("Should set min extents to negative set half size + negative offset") {
        AABB box = AABB();
        box.SetHalfSize(Vector2(-10, -10));
        box.SetOffset(Vector2(-5, -5));
        REQUIRE(box.GetMinExtents() == Vector2(-15, -15));
    }
}

TEST_CASE("AABB.GetMaxExtents Tests", AABBTAG) {
    SECTION("Should default to half unit vector") {
        AABB box = AABB();
        REQUIRE(box.GetMaxExtents() == Vector2(.5, .5));
    }

    SECTION("Should set max extents to set half size") {
        AABB box = AABB();
        box.SetHalfSize(Vector2(10, 10));
        REQUIRE(box.GetMaxExtents() == Vector2(10, 10));
    }

    SECTION("Should set max extents to negative set half size + offset") {
        AABB box = AABB();
        box.SetHalfSize(Vector2(10, 10));
        box.SetOffset(Vector2(5, 5));
        REQUIRE(box.GetMaxExtents() == Vector2(15, 15));
    }

    SECTION("Should set max extents to negative set half size + negative offset") {
        AABB box = AABB();
        box.SetHalfSize(Vector2(-10, -10));
        box.SetOffset(Vector2(-5, -5));
        REQUIRE(box.GetMaxExtents() == Vector2(5, 5));
    }
}

TEST_CASE("AABB.ContainsAABB Tests", AABBTAG) {
    SECTION("Should contains when default values") {
        AABB box1 = AABB();
        AABB box2 = AABB();
        REQUIRE(box1.ContainsAABB(box2));
        REQUIRE(box2.ContainsAABB(box1));
    }

    SECTION("Should contain when one box is bigger") {
        AABB box1 = AABB(Vector2(1, 1), Vector2());
        AABB box2 = AABB();
        REQUIRE(box1.ContainsAABB(box2));
        REQUIRE_FALSE(box2.ContainsAABB(box1));
    }

    SECTION("Should contain when one box is smaller") {
        AABB box1 = AABB(Vector2(.25, .25), Vector2());
        AABB box2 = AABB();
        REQUIRE_FALSE(box1.ContainsAABB(box2));
        REQUIRE(box2.ContainsAABB(box1));
    }

    SECTION("Should contain when one box is bigger but other is offset to edge") {
        AABB box1 = AABB(Vector2(1, 1), Vector2());
        AABB box2 = AABB();
        box2.SetOffset(Vector2(.5, .5));
        REQUIRE(box1.ContainsAABB(box2));
        REQUIRE_FALSE(box2.ContainsAABB(box1));
    }

    SECTION("Should not contain when one box is smaller but other is offset slightly") {
        AABB box1 = AABB(Vector2(.25, .25), Vector2());
        AABB box2 = AABB();
        box1.SetOffset(Vector2(.5 , .5));
        REQUIRE_FALSE(box1.ContainsAABB(box2));
        REQUIRE_FALSE(box2.ContainsAABB(box1));
    }

    SECTION("Should not contain when one box is bigger but offset provided") {
        AABB box1 = AABB(Vector2(1, 1), Vector2());
        AABB box2 = AABB();
        REQUIRE_FALSE(box1.ContainsAABB(box2, Vector2(10, 10), Vector2()));
        REQUIRE_FALSE(box2.ContainsAABB(box1, Vector2(10, 10), Vector2()));
    }

    SECTION("Should not contain when one box is smaller but offset provided") {
        AABB box1 = AABB(Vector2(.25, .25), Vector2());
        AABB box2 = AABB();
        REQUIRE_FALSE(box1.ContainsAABB(box2, Vector2(10, 10), Vector2()));
        REQUIRE_FALSE(box2.ContainsAABB(box1, Vector2(10, 10), Vector2()));
    }

    SECTION("Should contain when one box is bigger and both offset provided") {
        AABB box1 = AABB(Vector2(1, 1), Vector2());
        AABB box2 = AABB();
        REQUIRE(box1.ContainsAABB(box2, Vector2(10, 10), Vector2(10, 10)));
        REQUIRE_FALSE(box2.ContainsAABB(box1));
    }

    SECTION("Should contain when one box is smaller and both offset provided") {
        AABB box1 = AABB(Vector2(.25, .25), Vector2());
        AABB box2 = AABB();
        REQUIRE_FALSE(box1.ContainsAABB(box2, Vector2(10, 10), Vector2(10, 10)));
        REQUIRE(box2.ContainsAABB(box1, Vector2(10, 10), Vector2(10, 10)));
    }
}

TEST_CASE("AABB.IntersectsAABB Tests", AABBTAG) {
    SECTION("Should intersect with default values") {
        AABB box1 = AABB();
        AABB box2 = AABB();

        REQUIRE(box1.IntersectsAABB(box2));
        REQUIRE(box2.IntersectsAABB(box1));
    }

    SECTION("Should intersect if one box is bigger") {
        AABB box1 = AABB();
        AABB box2 = AABB();
        box1.SetHalfSize(Vector2(1, 1));

        REQUIRE(box1.IntersectsAABB(box2));
        REQUIRE(box2.IntersectsAABB(box1));
    }

    SECTION("Should intersect if one box is smaller") {
        AABB box1 = AABB();
        AABB box2 = AABB();
        box1.SetHalfSize(Vector2(.25, .25));

        REQUIRE(box1.IntersectsAABB(box2));
        REQUIRE(box2.IntersectsAABB(box1));
    }

    SECTION("Should intersect if 1 box is offset slightly") {
        AABB box1 = AABB();
        AABB box2 = AABB();

        box1.SetOffset(Vector2(.25, .25));

        REQUIRE(box1.IntersectsAABB(box2));
        REQUIRE(box2.IntersectsAABB(box1));
    }

    SECTION("Should intersect if both boxes are offset slightly") {
        AABB box1 = AABB();
        AABB box2 = AABB();

        box1.SetOffset(Vector2(.1, .1));
        box2.SetOffset(Vector2(-.1, -.1));

        REQUIRE(box1.IntersectsAABB(box2));
        REQUIRE(box2.IntersectsAABB(box1));
    }

    SECTION("Should not intersect if offsets are large") {
        AABB box1 = AABB();
        AABB box2 = AABB();

        box1.SetOffset(Vector2(10, 10));
        box2.SetOffset(Vector2(-.1, -.1));

        REQUIRE_FALSE(box1.IntersectsAABB(box2));
        REQUIRE_FALSE(box2.IntersectsAABB(box1));
    }

    SECTION("Should intersect if 1 box is provided with offset") {
        AABB box1 = AABB();
        AABB box2 = AABB();

        REQUIRE(box1.IntersectsAABB(box2, Vector2(.25, .25), Vector2()));
        REQUIRE(box2.IntersectsAABB(box1, Vector2(), Vector2(.25, .25)));
    }

    SECTION("Should intersect if both boxes are provided with slight offsets") {
        AABB box1 = AABB();
        AABB box2 = AABB();

        REQUIRE(box1.IntersectsAABB(box2, Vector2(.1, .1), Vector2(-.1, -.1)));
        REQUIRE(box2.IntersectsAABB(box1, Vector2(-.1, -.1), Vector2(.1, .1)));
    }

    SECTION("Should not intersect if provided offsets are large") {
        AABB box1 = AABB();
        AABB box2 = AABB();

        REQUIRE_FALSE(box1.IntersectsAABB(box2, Vector2(10, 10), Vector2(-.1, -.1)));
        REQUIRE_FALSE(box2.IntersectsAABB(box1, Vector2(-.1, -.1), Vector2(10, 10)));
    }
}

TEST_CASE("AABB.ContainsPoint Tests", AABBTAG) {
    SECTION("Should contain zero vector") {
        AABB box = AABB();
        REQUIRE(box.ContainsPoint(Vector2::Zero()));
    }

    SECTION("Should contain points within default values") {
        AABB box = AABB();
        REQUIRE(box.ContainsPoint(Vector2(.25, .25)));
        REQUIRE(box.ContainsPoint(Vector2(-.25, .25)));
        REQUIRE(box.ContainsPoint(Vector2(-.25, -.25)));
        REQUIRE(box.ContainsPoint(Vector2(.25, -.25)));
    }

    SECTION("Should contain points on edge") {
        AABB box = AABB();
        REQUIRE(box.ContainsPoint(Vector2(.5, .5)));
        REQUIRE(box.ContainsPoint(Vector2(-.5, .5)));
        REQUIRE(box.ContainsPoint(Vector2(-.5, -.5)));
        REQUIRE(box.ContainsPoint(Vector2(.5, -.5)));
    }

    SECTION("Should not contain zero vector if offset") {
        AABB box = AABB();
        box.SetOffset(Vector2(5, 5));
        REQUIRE_FALSE(box.ContainsPoint(Vector2::Zero()));
    }

    SECTION("Should not contain points within default values if offset") {
        AABB box = AABB();
        box.SetOffset(Vector2(5, 5));
        REQUIRE_FALSE(box.ContainsPoint(Vector2(.25, .25)));
        REQUIRE_FALSE(box.ContainsPoint(Vector2(-.25, .25)));
        REQUIRE_FALSE(box.ContainsPoint(Vector2(-.25, -.25)));
        REQUIRE_FALSE(box.ContainsPoint(Vector2(.25, -.25)));
    }

    SECTION("Should not contain points on edge if offset") {
        AABB box = AABB();
        box.SetOffset(Vector2(5, 5));
        REQUIRE_FALSE(box.ContainsPoint(Vector2(.5, .5)));
        REQUIRE_FALSE(box.ContainsPoint(Vector2(-.5, .5)));
        REQUIRE_FALSE(box.ContainsPoint(Vector2(-.5, -.5)));
        REQUIRE_FALSE(box.ContainsPoint(Vector2(.5, -.5)));
    }

    SECTION("Should contain offset vector if offset") {
        AABB box = AABB();
        box.SetOffset(Vector2(5, 5));
        REQUIRE(box.ContainsPoint(Vector2(5, 5)));
    }

    SECTION("Should contain points within offset values if offset") {
        AABB box = AABB();
        box.SetOffset(Vector2(5, 5));
        REQUIRE(box.ContainsPoint(Vector2(5.25, 5.25)));
        REQUIRE(box.ContainsPoint(Vector2(4.75, 5.25)));
        REQUIRE(box.ContainsPoint(Vector2(4.75, 4.75)));
        REQUIRE(box.ContainsPoint(Vector2(5.25, 4.75)));
    }

    SECTION("Should contain points on edge if offset") {
        AABB box = AABB();
        box.SetOffset(Vector2(5, 5));
        REQUIRE(box.ContainsPoint(Vector2(5.5, 5.5)));
        REQUIRE(box.ContainsPoint(Vector2(4.5, 5.5)));
        REQUIRE(box.ContainsPoint(Vector2(4.5, 4.5)));
        REQUIRE(box.ContainsPoint(Vector2(5.5, 4.5)));
    }

    SECTION("Should contain offset vector if offset provided") {
        AABB box = AABB();
        REQUIRE(box.ContainsPoint(Vector2(5, 5), Vector2(5, 5)));
    }

    SECTION("Should contain points within offset values if offset provided") {
        AABB box = AABB();
        REQUIRE(box.ContainsPoint(Vector2(5.25, 5.25), Vector2(5, 5)));
        REQUIRE(box.ContainsPoint(Vector2(4.75, 5.25), Vector2(5, 5)));
        REQUIRE(box.ContainsPoint(Vector2(4.75, 4.75), Vector2(5, 5)));
        REQUIRE(box.ContainsPoint(Vector2(5.25, 4.75), Vector2(5, 5)));
    }

    SECTION("Should contain points on edge if offset provided") {
        AABB box = AABB();
        REQUIRE(box.ContainsPoint(Vector2(5.5, 5.5), Vector2(5, 5)));
        REQUIRE(box.ContainsPoint(Vector2(4.5, 5.5), Vector2(5, 5)));
        REQUIRE(box.ContainsPoint(Vector2(4.5, 4.5), Vector2(5, 5)));
        REQUIRE(box.ContainsPoint(Vector2(5.5, 4.5), Vector2(5, 5)));
    }
}