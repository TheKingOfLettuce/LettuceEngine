#include "catch_amalgamated.hpp"
#include "LettuceEngine/Math/Vector2.h"

using LettuceEngine::Math::Vector2;
using Catch::Matchers::WithinRel;

TEST_CASE("Vector2.Construction Tests", "[Vector2]") {
    SECTION("Should create default zero vector") {
        Vector2 v = Vector2();
        REQUIRE(v.X == 0);
        REQUIRE(v.Y == 0);
    }

    SECTION("Should create vectors with passe in values") {
        Vector2 v = Vector2(1, 1);
        REQUIRE(v.X == 1);
        REQUIRE(v.Y == 1);
    }
}

TEST_CASE("Vector2.Magnitude Tests", "[Vector2]") {
    SECTION("Should return zero when vector is zero") {
        Vector2 v = Vector2();
        REQUIRE(v.Magnitude() == 0);
    }

    SECTION("Should return 1 when vector is one") {
        Vector2 v = Vector2(1, 1);
        REQUIRE(v.Magnitude() == sqrtf(2));
    }

    SECTION("Should return correct magnitude") {
        Vector2 v = Vector2(5, 5);
        REQUIRE(v.Magnitude() == sqrtf(50));
        v = Vector2(2, 7);
        REQUIRE(v.Magnitude() == sqrtf(53));
        v = Vector2(9, 4.8);
        REQUIRE(v.Magnitude() == 10.2f);
    }
}

TEST_CASE("Vector2.Normalize Tests", "[Vector2]") {
    SECTION("Should keep 0 vector at 0") {
        Vector2 v = Vector2();
        v.Normalize();
        REQUIRE(v == Vector2::ZERO);
    }

    SECTION("Should normalize one*x vector a one vector") {
        Vector2 v = Vector2(5, 5);
        v.Normalize();
        REQUIRE(v.X == 1/sqrtf(2));
        REQUIRE(v.Y == 1/sqrtf(2));
        v = Vector2(-3, -3);
        v.Normalize();
        
        REQUIRE_THAT(v.X, WithinRel(-(1.0f/sqrtf(2))));
        REQUIRE_THAT(v.Y, WithinRel(-(1.0f/sqrtf(2))));
    }

    SECTION("Should normalize vectors") {
        Vector2 v = Vector2(4, 3);
        v.Normalize();
        REQUIRE(v.X == 4.0f/5.0f);
        REQUIRE(v.Y == 3.0f/5.0f);
        v = Vector2(6, 4);
        v.Normalize();
        REQUIRE(v.X == 3.0f/sqrtf(13));
        REQUIRE(v.Y == 2.0f/sqrtf(13));
    }
}

TEST_CASE("Vector2.operator +/+= Tests", "[Vector2]") {
    SECTION("Should add Vectors and return new Vector") {
        Vector2 v = Vector2();
        REQUIRE(v + Vector2(3, 5) == Vector2(3, 5));
        REQUIRE(v.X != 3);
        REQUIRE(v.Y != 5);

        v = Vector2(4, 4);
        REQUIRE(v + Vector2(6, 6) == Vector2(10, 10));
        REQUIRE(v.X == 4);
        REQUIRE(v.Y == 4);
    }

    SECTION("Should add Vectors with current vector") {
        Vector2 v = Vector2();
        v += Vector2(3, 5);
        REQUIRE(v.X == 3);
        REQUIRE(v.Y == 5);

        v = Vector2(4, 4);
        v += Vector2(6, 6);
        REQUIRE(v.X == 10);
        REQUIRE(v.Y == 10);
    }
}

TEST_CASE("Vector2.operator -/-= Tests", "[Vector2]") {
    SECTION("Should subtract Vectors and return new Vector") {
        Vector2 v = Vector2();
        REQUIRE(v - Vector2(3, 5) == Vector2(-3, -5));
        REQUIRE(v.X != -3);
        REQUIRE(v.Y != -5);

        v = Vector2(4, 4);
        REQUIRE(v - Vector2(6, 6) == Vector2(-2, -2));
        REQUIRE(v.X == 4);
        REQUIRE(v.Y == 4);

        REQUIRE(v - Vector2(-6, -6) == Vector2(10, 10));
        REQUIRE(v.X == 4);
        REQUIRE(v.Y == 4);
    }

    SECTION("Should subtract Vectors with current vector") {
        Vector2 v = Vector2();
        v -= Vector2(3, 5);
        REQUIRE(v.X == -3);
        REQUIRE(v.Y == -5);

        v = Vector2(4, 4);
        v -= Vector2(6, 6);
        REQUIRE(v.X == -2);
        REQUIRE(v.Y == -2);
    }
}

TEST_CASE("Vector2.operator */*= Tests", "[Vector2]") {
    SECTION("Should multiply vectors and return new Vector") {
        Vector2 v = Vector2(1, 1);
        REQUIRE(v * Vector2(3, 5) == Vector2(3, 5));
        REQUIRE(v.X == 1);
        REQUIRE(v.Y == 1);

        v = Vector2(6, 7);
        REQUIRE(v * Vector2(3, 4) == Vector2(18, 28));
        REQUIRE(v.X == 6);
        REQUIRE(v.Y == 7);
    }

    SECTION("Should multiply vectors with current vector") {
        Vector2 v = Vector2(1, 1);
        v *= Vector2(3, 5);
        REQUIRE(v == Vector2(3, 5));

        v = Vector2(6, 7);
        v *= Vector2(3, 4);
        REQUIRE(v == Vector2(18, 28));
    }

    SECTION("Should scale vector and return new Vector") {
        Vector2 v = Vector2(1, 1);
        REQUIRE(v * 5 == Vector2(5, 5));
        REQUIRE(v.X == 1);
        REQUIRE(v.Y == 1);

        v = Vector2(6, 7);
        REQUIRE(v * 3 == Vector2(18, 21));
        REQUIRE(v.X == 6);
        REQUIRE(v.Y == 7);
    }

    SECTION("Should scale vector with current vector") {
        Vector2 v = Vector2(1, 1);
        v *= 5;
        REQUIRE(v == Vector2(5, 5));

        v = Vector2(6, 7);
        v *= 3;
        REQUIRE(v == Vector2(18, 21));
    }
}

TEST_CASE("Vector2.operator /|/= Tests", "[Vector2]") {
    SECTION("Should divide vectors and return new Vector") {
        Vector2 v = Vector2(9, 25);
        REQUIRE(v / Vector2(3, 5) == Vector2(3, 5));
        REQUIRE(v.X == 9);
        REQUIRE(v.Y == 25);

        v = Vector2(12, 28);
        REQUIRE(v / Vector2(3, 4) == Vector2(4, 7));
        REQUIRE(v.X == 12);
        REQUIRE(v.Y == 28);
    }

    SECTION("Should divide vectors with current vector") {
        Vector2 v = Vector2(3, 5);
        v /= Vector2(3, 5);
        REQUIRE(v == Vector2(1, 1));

        v = Vector2(12, 28);
        v /= Vector2(3, 4);
        REQUIRE(v == Vector2(4, 7));
    }

    SECTION("Should scale vector and return new Vector") {
        Vector2 v = Vector2(5, 5);
        REQUIRE(v / 5 == Vector2(1, 1));
        REQUIRE(v.X == 5);
        REQUIRE(v.Y == 5);

        v = Vector2(18, 21);
        REQUIRE(v / 3 == Vector2(6, 7));
        REQUIRE(v.X == 18);
        REQUIRE(v.Y == 21);
    }

    SECTION("Should scale vector with current vector") {
        Vector2 v = Vector2(5, 5);
        v /= 5;
        REQUIRE(v == Vector2(1, 1));

        v = Vector2(18, 21);
        v /= 3;
        REQUIRE(v == Vector2(6, 7));
    }
}

TEST_CASE("Vector2.operator== Tests", "[Vector2]") {
    SECTION("Should return true") {
        Vector2 v1 = Vector2(2, 2);
        Vector2 v2 = Vector2(2, 2);
        REQUIRE(&v1 != &v2);
        REQUIRE(v1 == v2);
    }

    SECTION("Should return false") {
        Vector2 v1 = Vector2(2, 2);
        Vector2 v2 = Vector2(1, 1);
        REQUIRE(&v1 != &v2);
        REQUIRE_FALSE(v1 == v2);
    }
}

TEST_CASE("Vector2.operator!= Tests", "[Vector2]") {
    SECTION("Should return true") {
        Vector2 v1 = Vector2(2, 2);
        Vector2 v2 = Vector2(1, 1);
        REQUIRE(&v1 != &v2);
        REQUIRE(v1 != v2);
    }

    SECTION("Should return false") {
        Vector2 v1 = Vector2(2, 2);
        Vector2 v2 = Vector2(2, 2);
        REQUIRE(&v1 != &v2);
        REQUIRE_FALSE(v1 != v2);
    }
}

TEST_CASE("Vector2.operator= Tests", "[Vector2]") {
    SECTION("Should assign members only") {
        Vector2 v1 = Vector2(15, 15);
        Vector2 v2 = Vector2(1.5, 2.5);
        v1 = v2;
        REQUIRE(&v1 != &v2);
        REQUIRE(v1.X == v2.X);
        REQUIRE(v1.Y == v2.Y);
        REQUIRE(v1.X != 15);
        REQUIRE(v1.Y != 15);
    }
}

TEST_CASE("Vector2.Static Tests", "[Vector2]") {
    SECTION("Should return zero vector") {
        REQUIRE(Vector2::ZERO == Vector2());
    }
}