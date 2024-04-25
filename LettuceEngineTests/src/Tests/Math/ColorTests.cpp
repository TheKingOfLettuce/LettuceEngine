#include "catch_amalgamated.hpp"
#include "Math/Color.h"

using LettuceEngine::Math::Color;

TEST_CASE("Color.Construction Tests", "[Color]") {
    SECTION("Should default construct with white") {
        Color c = Color();
        REQUIRE(c.R == 255);
        REQUIRE(c.G == 255);
        REQUIRE(c.B == 255);
        REQUIRE(c.A == 255);
    }

    SECTION("Should default construct with values") {
        Color c = Color(10, 15, 20, 25);
        REQUIRE(c.R == 10);
        REQUIRE(c.G == 15);
        REQUIRE(c.B == 20);
        REQUIRE(c.A == 25);
    }

    SECTION("Should default alpha with 255") {
        Color c = Color(10, 15, 20);
        REQUIRE(c.R == 10);
        REQUIRE(c.G == 15);
        REQUIRE(c.B == 20);
        REQUIRE(c.A == 255);
    }
}

TEST_CASE("Color.operator+/+= Tests", "[Color]") {
    SECTION("Should add colors and return new Color") {
        Color c1 = Color(10, 10, 10, 10);
        Color c2 = Color(50, 50, 50, 50);
        Color c3 = c1 + c2;
        REQUIRE(c1 != c3);
        REQUIRE(c2 != c3);
        REQUIRE(c3.R == 60);
        REQUIRE(c3.G == 60);
        REQUIRE(c3.B == 60);
        REQUIRE(c3.A == 60);
    }

    SECTION("Should add colors and not overflow new Color") {
        Color c1 = Color(245, 245, 245, 245);
        Color c2 = Color (75, 75, 75, 75);
        Color c3 = c1 + c2;
        REQUIRE(c3.R == 255);
        REQUIRE(c3.G == 255);
        REQUIRE(c3.B == 255);
        REQUIRE(c3.A == 255);
    }

    SECTION("Should add color to first color") {
        Color c1 = Color(10, 10, 10, 10);
        Color c2 = Color(50, 50, 50, 50);
        c1 += c2;
        REQUIRE(&c1 != &c2);
        REQUIRE(c1.R == 60);
        REQUIRE(c1.G == 60);
        REQUIRE(c1.B == 60);
        REQUIRE(c1.A == 60);
    }

    SECTION("Should add color and not overflow first color") {
        Color c1 = Color(245, 245, 245, 245);
        Color c2 = Color (75, 75, 75, 75);
        c1 += c2;
        REQUIRE(c1.R == 255);
        REQUIRE(c1.G == 255);
        REQUIRE(c1.B == 255);
        REQUIRE(c1.A == 255);
    }
}

TEST_CASE("Color.operator-/-= Tests", "[Color]") {
    SECTION("Should subtract colors and return new Color") {
        Color c1 = Color(60, 60, 60, 60);
        Color c2 = Color(50, 50, 50, 50);
        Color c3 = c1 - c2;
        REQUIRE(c1 != c3);
        REQUIRE(c2 != c3);
        REQUIRE(c3.R == 10);
        REQUIRE(c3.G == 10);
        REQUIRE(c3.B == 10);
        REQUIRE(c3.A == 10);
    }

    SECTION("Should subtract colors and not underflow new Color") {
        Color c1 = Color(45, 45, 45, 45);
        Color c2 = Color (75, 75, 75, 75);
        Color c3 = c1 - c2;
        REQUIRE(c3.R == 0);
        REQUIRE(c3.G == 0);
        REQUIRE(c3.B == 0);
        REQUIRE(c3.A == 0);
    }

    SECTION("Should subtract color to first color") {
        Color c1 = Color(60, 60, 60, 60);
        Color c2 = Color(50, 50, 50, 50);
        c1 -= c2;
        REQUIRE(&c1 != &c2);
        REQUIRE(c1.R == 10);
        REQUIRE(c1.G == 10);
        REQUIRE(c1.B == 10);
        REQUIRE(c1.A == 10);
    }

    SECTION("Should subtract color and not underflow first color") {
        Color c1 = Color(45, 45, 45, 45);
        Color c2 = Color (75, 75, 75, 75);
        c1 -= c2;
        REQUIRE(c1.R == 0);
        REQUIRE(c1.G == 0);
        REQUIRE(c1.B == 0);
        REQUIRE(c1.A == 0);
    }
}

TEST_CASE("Color.operator*/*= Tests", "[Color]") {
    SECTION("Should multiply colors and return new Color") {
        Color c1 = Color(5, 5, 5, 5);
        Color c2 = Color(50, 50, 50, 50);
        Color c3 = c1 * c2;
        REQUIRE(c1 != c3);
        REQUIRE(c2 != c3);
        REQUIRE(c3.R == 250);
        REQUIRE(c3.G == 250);
        REQUIRE(c3.B == 250);
        REQUIRE(c3.A == 250);
    }

    SECTION("Should multiply colors and not overflow new Color") {
        Color c1 = Color(245, 245, 245, 245);
        Color c2 = Color (75, 75, 75, 75);
        Color c3 = c1 * c2;
        REQUIRE(c3.R == 255);
        REQUIRE(c3.G == 255);
        REQUIRE(c3.B == 255);
        REQUIRE(c3.A == 255);
    }

    SECTION("Should multiply color to first color") {
        Color c1 = Color(5, 5, 5, 5);
        Color c2 = Color(50, 50, 50, 50);
        c1 *= c2;
        REQUIRE(&c1 != &c2);
        REQUIRE(c1.R == 250);
        REQUIRE(c1.G == 250);
        REQUIRE(c1.B == 250);
        REQUIRE(c1.A == 250);
    }

    SECTION("Should multiply color and not overflow first color") {
        Color c1 = Color(245, 245, 245, 245);
        Color c2 = Color (75, 75, 75, 75);
        c1 *= c2;
        REQUIRE(c1.R == 255);
        REQUIRE(c1.G == 255);
        REQUIRE(c1.B == 255);
        REQUIRE(c1.A == 255);
    }
}

TEST_CASE("Color.operator/|/= Tests", "[Color]") {
    SECTION("Should divide colors and return new Color") {
        Color c1 = Color(50, 50, 50, 50);
        Color c2 = Color(5, 5, 5, 5);
        Color c3 = c1 / c2;
        REQUIRE(c1 != c3);
        REQUIRE(c2 != c3);
        REQUIRE(c3.R == 10);
        REQUIRE(c3.G == 10);
        REQUIRE(c3.B == 10);
        REQUIRE(c3.A == 10);
    }

    SECTION("Should divide colors and not underflow new Color") {
        Color c1 = Color(45, 45, 45, 45);
        Color c2 = Color (75, 75, 75, 75);
        Color c3 = c1 / c2;
        REQUIRE(c3.R == 0);
        REQUIRE(c3.G == 0);
        REQUIRE(c3.B == 0);
        REQUIRE(c3.A == 0);
    }

    SECTION("Should divide color to first color") {
        Color c1 = Color(50, 50, 50, 50);
        Color c2 = Color(5, 5, 5, 5);
        c1 /= c2;
        REQUIRE(&c1 != &c2);
        REQUIRE(c1.R == 10);
        REQUIRE(c1.G == 10);
        REQUIRE(c1.B == 10);
        REQUIRE(c1.A == 10);
    }

    SECTION("Should divide color and not underflow first color") {
        Color c1 = Color(45, 45, 45, 45);
        Color c2 = Color (75, 75, 75, 75);
        c1 /= c2;
        REQUIRE(c1.R == 0);
        REQUIRE(c1.G == 0);
        REQUIRE(c1.B == 0);
        REQUIRE(c1.A == 0);
    }

    SECTION("Should return zero vector if divide by 0") {
        Color c1 = Color();
        Color zeroC = Color(0, 0, 0, 0);
        c1 /= zeroC;
        REQUIRE(c1 == zeroC);
    }
}

TEST_CASE("Color.operator== Tests", "[Color]") {
    SECTION("Should return true") {
        Color c1 = Color(54, 54, 54, 54);
        Color c2 = Color(54, 54, 54, 54);
        REQUIRE(c1 == c2);
    }

    SECTION("Should return false") {
        Color c1 = Color();
        Color c2 = Color(1, 2, 3, 4);
        REQUIRE_FALSE(c1 == c2);
        c1 = Color(1, 2, 3, 5);
        REQUIRE_FALSE(c1 == c2);
    }
}

TEST_CASE("Color.operator!= Tests", "[Color]") {
    SECTION("Should return true") {
        Color c1 = Color(54, 54, 54, 54);
        Color c2 = Color(1, 2, 3, 4);
        REQUIRE(c1 != c2);
        c1 = Color(1, 2, 3, 5);
        REQUIRE(c1 != c2);
    }

    SECTION("Should return false") {
        Color c1 = Color();
        Color c2 = Color();
        REQUIRE_FALSE(c1 != c2);
    }
}

TEST_CASE("Color.operator= Tests", "[Color]") {
    SECTION("Should assign members only") {
        Color c1 = Color();
        Color c2 = Color(1, 2, 3, 4);
        REQUIRE(c1 != c2);
        c1 = c2;
        REQUIRE(c1 == c2);
        REQUIRE(&c1 != &c2);
        REQUIRE(c1.R == 1);
        REQUIRE(c1.G == 2);
        REQUIRE(c1.B == 3);
        REQUIRE(c1.A == 4);
    }
}