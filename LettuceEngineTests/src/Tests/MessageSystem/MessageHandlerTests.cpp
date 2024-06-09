#include "catch_amalgamated.hpp"
#include "LettuceEngine/MessageSystem/MessageHandler.h"
#include "LettuceEngine/MessageSystem/MessageBase.h"

TEST_CASE("MessageHandler.AddCallback Tests", "[MessageHandler]") {
	class AddCallbackHelper {
		public:
			void TestCallback(MessageBase* msg) {}
	};
	AddCallbackHelper helper = AddCallbackHelper();

	SECTION("Should Not Throw Exception") {
		MessageHandler<MessageBase> handler = MessageHandler<MessageBase>();
		handler.AddCallback(new CallbackHandler<MessageBase, AddCallbackHelper>(&helper, &AddCallbackHelper::TestCallback));
	}

	SECTION("Should Throw Exception If Null Callback Given") {
		MessageHandler<MessageBase> handler = MessageHandler<MessageBase>();
		REQUIRE_THROWS_AS(handler.AddCallback(nullptr), std::invalid_argument);
	}
}

TEST_CASE("MessageHandler.HandleCallback Tests", "[MessageHandler]") {
	class HandleCallbackHelper {
		public:
			int CallbackCount;
			void Count(MessageBase* msg) {CallbackCount++;}
	};
	HandleCallbackHelper helper = HandleCallbackHelper();

	SECTION("Should Return True When No Callbacks") {
		MessageHandler<MessageBase> handler = MessageHandler<MessageBase>();
		MessageBase msg = MessageBase();
		handler.HandleCallback(&msg);

		REQUIRE(helper.CallbackCount == 0);
	}

	SECTION("Should Return True When Single Callback") {
		MessageHandler<MessageBase> handler = MessageHandler<MessageBase>();
		handler.AddCallback(new CallbackHandler<MessageBase, HandleCallbackHelper>(&helper, &HandleCallbackHelper::Count));
		MessageBase msg = MessageBase();
		handler.HandleCallback(&msg);

		REQUIRE(helper.CallbackCount == 1);
	}

	SECTION("Should Return True When Multiple Callbacks") {
		MessageHandler<MessageBase> handler = MessageHandler<MessageBase>();
		handler.AddCallback(new CallbackHandler<MessageBase, HandleCallbackHelper>(&helper, &HandleCallbackHelper::Count));
		handler.AddCallback(new CallbackHandler<MessageBase, HandleCallbackHelper>(&helper, &HandleCallbackHelper::Count));
		handler.AddCallback(new CallbackHandler<MessageBase, HandleCallbackHelper>(&helper, &HandleCallbackHelper::Count));
		MessageBase msg = MessageBase();
		handler.HandleCallback(&msg);

		REQUIRE(helper.CallbackCount == 3);
	}
}

TEST_CASE("MessageHandler.RemoveCallback Tests", "[MessageHandler]") {
	class RemoveCallbackHelper {
		public:
			bool DidCallback;
			void SetCallback(MessageBase* msg) {DidCallback = true;}
	};
	RemoveCallbackHelper helper = RemoveCallbackHelper();

	SECTION("Should Return True If Single Callback Removed") {
		CallbackHandler<MessageBase, RemoveCallbackHelper>* callback = new CallbackHandler<MessageBase, RemoveCallbackHelper>(&helper, &RemoveCallbackHelper::SetCallback);
		CallbackHandler<MessageBase, RemoveCallbackHelper>* secondCallback = new CallbackHandler<MessageBase, RemoveCallbackHelper>(&helper, &RemoveCallbackHelper::SetCallback);
		MessageHandler<MessageBase> handler = MessageHandler<MessageBase>();
		handler.AddCallback(callback);
		handler.AddCallback(secondCallback);
		CallbackHandler<MessageBase, RemoveCallbackHelper>* toRemove = new CallbackHandler<MessageBase, RemoveCallbackHelper>(&helper, &RemoveCallbackHelper::SetCallback);
		// should delete callback since its first added, also should delete toRemove after its done looking
		handler.RemoveCallback(toRemove);
		MessageBase msg = MessageBase();
		handler.HandleCallback(&msg);

		REQUIRE(helper.DidCallback);
	}

	SECTION("Should Return False If All Callbacks Removed") {
		CallbackHandler<MessageBase, RemoveCallbackHelper>* callback = new CallbackHandler<MessageBase, RemoveCallbackHelper>(&helper, &RemoveCallbackHelper::SetCallback);
		CallbackHandler<MessageBase, RemoveCallbackHelper>* secondCallback = new CallbackHandler<MessageBase, RemoveCallbackHelper>(&helper, &RemoveCallbackHelper::SetCallback);
		MessageHandler<MessageBase> handler = MessageHandler<MessageBase>();
		handler.AddCallback(callback);
		handler.AddCallback(secondCallback);
		CallbackHandler<MessageBase, RemoveCallbackHelper>* toRemove = new CallbackHandler<MessageBase, RemoveCallbackHelper>(&helper, &RemoveCallbackHelper::SetCallback);
		handler.RemoveCallback(toRemove);
		// need to reInitialize since its gets deleted
		toRemove = new CallbackHandler<MessageBase, RemoveCallbackHelper>(&helper, &RemoveCallbackHelper::SetCallback);
		handler.RemoveCallback(toRemove);
		MessageBase msg = MessageBase();
		handler.HandleCallback(&msg);

		REQUIRE_FALSE(helper.DidCallback);
	}
}