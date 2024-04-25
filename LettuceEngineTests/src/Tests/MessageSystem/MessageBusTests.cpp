#include "catch_amalgamated.hpp"
#include "MessageSystem/MessageBus.h"

TEST_CASE("MessageBus.Subscribe Tests", "[MessageBus]") {
	class SubscribeHelper {
		public:
			void TestMethod(MessageBase* msg) {}
	};
	SubscribeHelper helper = SubscribeHelper();
	MessageBus::UnsubscribeAll<MessageBase>();

	SECTION("Should Not Throw Exception") {
		MessageBus::Subscribe(&helper, &SubscribeHelper::TestMethod);
	}

	SECTION("Should Throw Exception If Instance Is Null") {
		REQUIRE_THROWS_AS((MessageBus::Subscribe<MessageBase, SubscribeHelper>(nullptr, &SubscribeHelper::TestMethod)), std::invalid_argument);
	}
}

TEST_CASE("MessageBus.Publish Tests", "[MessageBus]") {
	class PublishHelper {
		public:
			int CallbackCount;
			void Count(MessageBase* msg) {CallbackCount++;}
	};
	PublishHelper helper = PublishHelper();
	MessageBus::UnsubscribeAll<MessageBase>();

	SECTION("Should Return True If No Callbacks") {
		MessageBus::Publish(new MessageBase());

		REQUIRE(helper.CallbackCount == 0);
	}

	SECTION("Should Return True If Single Subscribe And Single Publish") {
		MessageBus::Subscribe(&helper, &PublishHelper::Count);
		MessageBus::Publish(new MessageBase());

		REQUIRE(helper.CallbackCount == 1);
	}

	SECTION("Should Return True If Single Subscribe And Multiple Publish") {
		MessageBus::Subscribe(&helper, &PublishHelper::Count);
		MessageBus::Publish(new MessageBase());
		MessageBus::Publish(new MessageBase());
		MessageBus::Publish(new MessageBase());

		REQUIRE(helper.CallbackCount == 3);
	}

	SECTION("Should Return True If Multiple Subscribes And Single Publish") {
		MessageBus::Subscribe(&helper, &PublishHelper::Count);
		MessageBus::Subscribe(&helper, &PublishHelper::Count);
		MessageBus::Subscribe(&helper, &PublishHelper::Count);
		MessageBus::Publish(new MessageBase());

		REQUIRE(helper.CallbackCount == 3);
	}
}

TEST_CASE("MessageBus.Unsubscribe Tests", "[MessageBus]") {
	class UnsubscribeHelper {
		public:
			bool DidCallback;
			bool DidOtherCallback;
			void TestCallback(MessageBase* msg) {DidCallback = true;}
			void OtherCallback(MessageBase* msg) {DidOtherCallback = true;}
	};
	UnsubscribeHelper helper = UnsubscribeHelper();
	MessageBus::UnsubscribeAll<MessageBase>();

	SECTION("Should Remove Nothing") {
		MessageBus::Unsubscribe(&helper, &UnsubscribeHelper::TestCallback);
		MessageBus::Publish(new MessageBase());

		REQUIRE_FALSE(helper.DidCallback);
	}

	SECTION("Should Remove Callback") {
		MessageBus::Subscribe(&helper, &UnsubscribeHelper::TestCallback);
		MessageBus::Unsubscribe(&helper, &UnsubscribeHelper::TestCallback);
		MessageBus::Publish(new MessageBase());

		REQUIRE_FALSE(helper.DidCallback);
	}

	SECTION("Should Keep Test Callback") {
		MessageBus::Subscribe(&helper, &UnsubscribeHelper::TestCallback);
		MessageBus::Unsubscribe(&helper, &UnsubscribeHelper::OtherCallback);
		MessageBus::Publish(new MessageBase());

		REQUIRE(helper.DidCallback);
	}

	SECTION("Should Keep Test Callback If Other Callback Removed") {
		MessageBus::Subscribe(&helper, &UnsubscribeHelper::TestCallback);
		MessageBus::Subscribe(&helper, &UnsubscribeHelper::OtherCallback);
		MessageBus::Unsubscribe(&helper, &UnsubscribeHelper::OtherCallback);
		MessageBus::Publish(new MessageBase());

		REQUIRE(helper.DidCallback);
		REQUIRE_FALSE(helper.DidOtherCallback);
	}

	SECTION("Should Keep Both Callbacks If Double Added And Single Removed") {
		MessageBus::Subscribe(&helper, &UnsubscribeHelper::TestCallback);
		MessageBus::Subscribe(&helper, &UnsubscribeHelper::OtherCallback);
		MessageBus::Subscribe(&helper, &UnsubscribeHelper::TestCallback);
		MessageBus::Subscribe(&helper, &UnsubscribeHelper::OtherCallback);
		MessageBus::Unsubscribe(&helper, &UnsubscribeHelper::TestCallback);
		MessageBus::Unsubscribe(&helper, &UnsubscribeHelper::OtherCallback);
		MessageBus::Publish(new MessageBase());

		REQUIRE(helper.DidCallback);
		REQUIRE(helper.DidOtherCallback);
	}
}

TEST_CASE("MessageBus.UnsubscribeAll Tests", "[MessageBus]") {
	class UnsubscribeAllHelper {
		public:
			bool DidCallback;
			bool DidOtherCallback;
			void TestCallback(MessageBase* msg) {}
			void OtherCallback(MessageBase* msg) {}
	};
	UnsubscribeAllHelper helper = UnsubscribeAllHelper();
	MessageBus::UnsubscribeAll<MessageBase>();

	SECTION("Should Do Nothing") {
		MessageBus::UnsubscribeAll<MessageBase>();
	}

	SECTION("Should Return False If All Callbacks Removed") {
		MessageBus::Subscribe(&helper, &UnsubscribeAllHelper::TestCallback);
		MessageBus::Subscribe(&helper, &UnsubscribeAllHelper::OtherCallback);
		MessageBus::Subscribe(&helper, &UnsubscribeAllHelper::TestCallback);
		MessageBus::Subscribe(&helper, &UnsubscribeAllHelper::OtherCallback);
		MessageBus::Subscribe(&helper, &UnsubscribeAllHelper::TestCallback);
		MessageBus::Subscribe(&helper, &UnsubscribeAllHelper::OtherCallback);
		MessageBus::UnsubscribeAll<MessageBase>();
		MessageBus::Publish(new MessageBase());

		REQUIRE_FALSE(helper.DidCallback);
		REQUIRE_FALSE(helper.DidOtherCallback);
	}
}