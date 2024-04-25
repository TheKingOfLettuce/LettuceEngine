#include "catch_amalgamated.hpp"
#include "MessageSystem/MessageHandler.h"
#include "MessageSystem/MessageBase.h"

TEST_CASE("CallbackHandler.Construction Tests", "[CallbackHandler]") {
	class ConstructionTestHelper {
		public:
			void TestCallback(MessageBase* message) {}
	};

	ConstructionTestHelper helper = ConstructionTestHelper();

	SECTION("Should Not Throw Exception") {
		CallbackHandler<MessageBase, ConstructionTestHelper> callback = CallbackHandler<MessageBase, ConstructionTestHelper>(&helper, &ConstructionTestHelper::TestCallback);
	}

	SECTION("Should Throw Exception If Instance Is Null") {
		REQUIRE_THROWS_AS((CallbackHandler<MessageBase, ConstructionTestHelper>(nullptr, &ConstructionTestHelper::TestCallback)), std::invalid_argument);
	}

	SECTION("Should Throw Exception If Callback Is Null") {
		REQUIRE_THROWS_AS((CallbackHandler<MessageBase, ConstructionTestHelper>(&helper, nullptr)), std::invalid_argument);
	}
}

TEST_CASE("CallbackHandler.Equals Tests", "[CallbackHandler]") {
	class EqualsTestHelper {
		public:
			void TestCallback(MessageBase* message) {}
			void SecondTestCallback(MessageBase* message) {}
	};

	EqualsTestHelper helper = EqualsTestHelper();

	SECTION("Should Return True When Compared With Self") {
		CallbackHandler<MessageBase, EqualsTestHelper> callback = CallbackHandler<MessageBase, EqualsTestHelper>(&helper, &EqualsTestHelper::TestCallback);
		REQUIRE(callback == callback);
	}

	SECTION("Should Return True When Ptr Compared With Self") {
		CallbackHandler<MessageBase, EqualsTestHelper> callback = CallbackHandler<MessageBase, EqualsTestHelper>(&helper, &EqualsTestHelper::TestCallback);
		REQUIRE(callback == &callback);
	}

	SECTION("Should Return True If Same Callback And Instance") {
		CallbackHandler<MessageBase, EqualsTestHelper> callback = CallbackHandler<MessageBase, EqualsTestHelper>(&helper, &EqualsTestHelper::TestCallback);
		CallbackHandler<MessageBase, EqualsTestHelper> sameCallback = CallbackHandler<MessageBase, EqualsTestHelper>(&helper, &EqualsTestHelper::TestCallback);
		REQUIRE(callback == sameCallback);
		REQUIRE(sameCallback == callback);
		REQUIRE_FALSE(callback != sameCallback);
		REQUIRE_FALSE(sameCallback != callback);
	}

	SECTION("Should Return True When Ptr Compared If Same Callback And Instance") {
		CallbackHandler<MessageBase, EqualsTestHelper> callback = CallbackHandler<MessageBase, EqualsTestHelper>(&helper, &EqualsTestHelper::TestCallback);
		CallbackHandler<MessageBase, EqualsTestHelper> sameCallback = CallbackHandler<MessageBase, EqualsTestHelper>(&helper, &EqualsTestHelper::TestCallback);
		REQUIRE(callback == &sameCallback);
		REQUIRE(sameCallback == &callback);
		REQUIRE_FALSE(callback != &sameCallback);
		REQUIRE_FALSE(sameCallback != &callback);
	}

	SECTION("Should Return False If Different Callback Same Instance") {
		CallbackHandler<MessageBase, EqualsTestHelper> callback = CallbackHandler<MessageBase, EqualsTestHelper>(&helper, &EqualsTestHelper::TestCallback);
		CallbackHandler<MessageBase, EqualsTestHelper> sameCallback = CallbackHandler<MessageBase, EqualsTestHelper>(&helper, &EqualsTestHelper::SecondTestCallback);
		REQUIRE_FALSE(callback == sameCallback);
		REQUIRE_FALSE(sameCallback == callback);
		REQUIRE(callback != sameCallback);
		REQUIRE(sameCallback != callback);
	}

	SECTION("Should Return False When Ptr Compared If Different Callback Same Instance") {
		CallbackHandler<MessageBase, EqualsTestHelper> callback = CallbackHandler<MessageBase, EqualsTestHelper>(&helper, &EqualsTestHelper::TestCallback);
		CallbackHandler<MessageBase, EqualsTestHelper> sameCallback = CallbackHandler<MessageBase, EqualsTestHelper>(&helper, &EqualsTestHelper::SecondTestCallback);
		REQUIRE_FALSE(callback == &sameCallback);
		REQUIRE_FALSE(sameCallback == &callback);
		REQUIRE(callback != &sameCallback);
		REQUIRE(sameCallback != &callback);
	}

	SECTION("Should Return False If Same Callback Different Instance") {
		CallbackHandler<MessageBase, EqualsTestHelper> callback = CallbackHandler<MessageBase, EqualsTestHelper>(&helper, &EqualsTestHelper::TestCallback);
		EqualsTestHelper instance = EqualsTestHelper();
		CallbackHandler<MessageBase, EqualsTestHelper> sameCallback = CallbackHandler<MessageBase, EqualsTestHelper>(&instance, &EqualsTestHelper::TestCallback);
		REQUIRE_FALSE(callback == sameCallback);
		REQUIRE_FALSE(sameCallback == callback);
		REQUIRE(callback != sameCallback);
		REQUIRE(sameCallback != callback);
	}

	SECTION("Should Return False When Ptr Compared If Same Callback Different Instance") {
		CallbackHandler<MessageBase, EqualsTestHelper> callback = CallbackHandler<MessageBase, EqualsTestHelper>(&helper, &EqualsTestHelper::TestCallback);
		EqualsTestHelper instance = EqualsTestHelper();
		CallbackHandler<MessageBase, EqualsTestHelper> sameCallback = CallbackHandler<MessageBase, EqualsTestHelper>(&instance, &EqualsTestHelper::TestCallback);
		REQUIRE_FALSE(callback == &sameCallback);
		REQUIRE_FALSE(sameCallback == &callback);
		REQUIRE(callback != &sameCallback);
		REQUIRE(sameCallback != &callback);
	}
}

TEST_CASE("CallbackHandler.HandleCallback Tests", "[CallbackHandler]") {
	class HandleCallbackHelper {
		public:
			bool DidCallback;
			void TestCallback(MessageBase* message) {
				DidCallback = true;
			}
	};

	HandleCallbackHelper helper = HandleCallbackHelper();
	CallbackHandler<MessageBase, HandleCallbackHelper> callback = CallbackHandler<MessageBase, HandleCallbackHelper>(&helper, &HandleCallbackHelper::TestCallback);

	SECTION("Should Return True When Called") {
		REQUIRE_FALSE(helper.DidCallback);
		MessageBase msg = MessageBase();
		callback.HandleCallback(&msg);
		REQUIRE(helper.DidCallback);
	}
};