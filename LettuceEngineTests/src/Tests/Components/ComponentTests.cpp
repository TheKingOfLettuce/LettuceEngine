#include "catch_amalgamated.hpp"
#include "LettuceObject.h"

using json = nlohmann::json;

class TestComponent : public Component {
	public:
		bool EnabledCalled;
		bool DisabledCalled;

		void SetEnabledForceNoCallbacks(bool flag) {
			_enabled = flag;
		}
	protected:
		void Enabled() override {
			EnabledCalled = true;
		}
		void Disabled() override {
			DisabledCalled = true;
		}
};

TEST_CASE("Component.SetEnabled Tests", "[Component]") {
	Component c = Component();

	SECTION("Should Default To False") {
		REQUIRE_FALSE(c.GetEnabled());
	}

	SECTION("Should Set To True") {
		c.SetEnabled(true);
		REQUIRE(c.GetEnabled());
	}

	SECTION("Should Set To True Then Back To False") {
		c.SetEnabled(true);
		REQUIRE(c.GetEnabled());
		c.SetEnabled(false);
		REQUIRE_FALSE(c.GetEnabled());
	}
}

TEST_CASE("Component.Enabled Tests", "[Component]") {
	TestComponent c = TestComponent();

	SECTION("Should Call Enabled") {
		c.SetEnabled(true);
		REQUIRE(c.EnabledCalled);
	}

	SECTION("Should Not Call Enabled If Already Enabled") {
		c.SetEnabledForceNoCallbacks(true);
		c.SetEnabled(true);
		REQUIRE_FALSE(c.EnabledCalled);
	}
}

TEST_CASE("Component.Disabled Tests", "[Component]") {
	TestComponent c = TestComponent();

	SECTION("Should Call Disabled") {
		c.SetEnabledForceNoCallbacks(true);
		c.SetEnabled(false);
		REQUIRE(c.DisabledCalled);
	}

	SECTION("Should Not Call Disabled If Already Disabled") {
		c.SetEnabled(false);
		REQUIRE_FALSE(c.DisabledCalled);
	}
}

TEST_CASE("Component.Init Tests", "[Component]") {
	Component c = Component();

	SECTION("Should Set LettuceObject") {
		LettuceObject obj = LettuceObject();
		c.Init(&obj);
	}

	SECTION("Should Throw Exception If LettuceObject Is Null") {
		REQUIRE_THROWS_AS(c.Init(nullptr), std::invalid_argument);
	}
}

TEST_CASE("Component.SaveToData Tests", "[Component]") {
	Component c = Component();

	SECTION("Should Save With Enabled False") {
		json j = json {
			{"enabled", false}
		};

		REQUIRE(c.SaveToData() == j.dump());
	}

	SECTION("Should Save With Enabled True If Component Enabled") {
		c.SetEnabled(true);
		json j = json {
			{"enabled", true}
		};

		REQUIRE(c.SaveToData() == j.dump());
	}
}

TEST_CASE("Component.LoadFromData Tests", "[Component]") {
	Component c = Component();

	SECTION("Should Load With Enabled False") {
		json j = json {
			{"enabled", false}
		};

		c.SetEnabled(true);
		REQUIRE(c.GetEnabled());
		c.LoadFromData(j.dump());
		REQUIRE_FALSE(c.GetEnabled());
	}

	SECTION("Should Load With Enabled True") {
		json j = json {
			{"enabled", true}
		};
		c.LoadFromData(j.dump());

		REQUIRE(c.GetEnabled());
	}
}