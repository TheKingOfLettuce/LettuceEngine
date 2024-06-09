#include "catch_amalgamated.hpp"
#include "LettuceEngine/Utils/LinkedList.h"

TEST_CASE("LinkedList.Add Tests", "[LinkedList]") {
    LinkedList<int> list = LinkedList<int>();

	#pragma region Single
	SECTION("Single Should Set 1 Size") {
		list.Add(5);
		REQUIRE(1 == list.Size());
	}

	SECTION("Single Should Return First Object") {
		list.Add(5);
		REQUIRE(5 == list.Get(0));
	}

	SECTION("Single Should Set Correct Link") {
		list.Add(5);
		Node<int>* head = list.GetHead();
		REQUIRE(nullptr == head->Next);
		REQUIRE(nullptr == head->Previous);
		REQUIRE(5 == head->Data);
		head = nullptr;
	}
	#pragma endregion Single

	#pragma region Double
	SECTION("Double Should Make Size 2") {
		list.Add(5);
		list.Add(10);
		REQUIRE(2 == list.Size());
	}

	SECTION("Double Should Set Element Index") {
		list.Add(5);
		list.Add(10);
		REQUIRE(5 == list.Get(0));
		REQUIRE(10 == list.Get(1));
	}

	SECTION("Double Should Set Correct Link") {
		list.Add(5);
		list.Add(10);
		Node<int>* current = list.GetHead();
		REQUIRE(nullptr == current->Previous);
		REQUIRE(nullptr != current->Next);
		REQUIRE(5 == current->Data);
		current = current->Next;
		REQUIRE(nullptr == current->Next);
		REQUIRE(nullptr != current->Previous);
		REQUIRE(10 == current->Data);
		current = nullptr;
	}
	#pragma endregion Double

	#pragma region Triple
	SECTION("Triple Should Make Size 3") {
		list.Add(5);
		list.Add(10);
		list.Add(15);
		REQUIRE(3 == list.Size());
	}

	SECTION("Triple Should Set Correct Index") {
		list.Add(5);
		list.Add(10);
		list.Add(15);
		REQUIRE(5 == list.Get(0));
		REQUIRE(10 == list.Get(1));
		REQUIRE(15 == list.Get(2));
	}

	SECTION("Triple Should Set Correct Link") {
		list.Add(5);
		list.Add(10);
		list.Add(15);
		Node<int>* current = list.GetHead();
		REQUIRE(nullptr == current->Previous);
		REQUIRE(nullptr != current->Next);
		REQUIRE(5 == current->Data);
		current = current->Next;
		REQUIRE(nullptr != current->Next);
		REQUIRE(nullptr != current->Previous);
		REQUIRE(10 == current->Data);
		current = current->Next;
		REQUIRE(nullptr != current->Previous);
		REQUIRE(nullptr == current->Next);
		REQUIRE(15 == current->Data);
		current = nullptr;
	}
	#pragma endregion Triple
}

TEST_CASE("LinkedList.Push Tests", "[LinkedList]") {
    LinkedList<int> list = LinkedList<int>();

	#pragma region Single
	SECTION("Single Should Set 1 Size") {
		list.Push(5);
		REQUIRE(1 == list.Size());
	}

	SECTION("Single Should Return First Object") {
		list.Push(5);
		REQUIRE(5 == list.Get(0));
	}

	SECTION("Single Should Set Correct Link") {
		list.Push(5);
		Node<int>* head = list.GetHead();
		REQUIRE(nullptr == head->Next);
		REQUIRE(nullptr == head->Previous);
		REQUIRE(5 == head->Data);
		head = nullptr;
	}
	#pragma endregion Single

	#pragma region Double
	SECTION("Double Should Make Size 2") {
		list.Push(5);
		list.Push(10);
		REQUIRE(2 == list.Size());
	}

	SECTION("Double Should Set Element Index") {
		list.Push(5);
		list.Push(10);
		REQUIRE(10 == list.Get(0));
		REQUIRE(5 == list.Get(1));
	}

	SECTION("Double Should Set Correct Link") {
		list.Push(5);
		list.Push(10);
		Node<int>* current = list.GetHead();
		REQUIRE(nullptr == current->Previous);
		REQUIRE(nullptr != current->Next);
		REQUIRE(10 == current->Data);
		current = current->Next;
		REQUIRE(nullptr == current->Next);
		REQUIRE(nullptr != current->Previous);
		REQUIRE(5 == current->Data);
		current = nullptr;
	}
	#pragma endregion Double

	#pragma region Triple
	SECTION("Triple Should Make Size 3") {
		list.Push(5);
		list.Push(10);
		list.Push(15);
		REQUIRE(3 == list.Size());
	}

	SECTION("Triple Should Set Correct Index") {
		list.Push(5);
		list.Push(10);
		list.Push(15);
		REQUIRE(15 == list.Get(0));
		REQUIRE(10 == list.Get(1));
		REQUIRE(5 == list.Get(2));
	}

	SECTION("Triple Should Set Correct Link") {
		list.Push(5);
		list.Push(10);
		list.Push(15);
		Node<int>* current = list.GetHead();
		REQUIRE(nullptr == current->Previous);
		REQUIRE(nullptr != current->Next);
		REQUIRE(15 == current->Data);
		current = current->Next;
		REQUIRE(nullptr != current->Next);
		REQUIRE(nullptr != current->Previous);
		REQUIRE(10 == current->Data);
		current = current->Next;
		REQUIRE(nullptr != current->Previous);
		REQUIRE(nullptr == current->Next);
		REQUIRE(5 == current->Data);
		current = nullptr;
	}
	#pragma endregion Triple
}

TEST_CASE("LinkedList.Get Tests", "[LinkedList]") {
	LinkedList<int> list = LinkedList<int>();

	SECTION("Should Return Correct First Index") {
		list.Push(1);
		REQUIRE(1 == list.Get(0));
		list.Push(2);
		REQUIRE(2 == list.Get(0));
		list.Push(3);
		REQUIRE(3 == list.Get(0));
	}

	SECTION("Should Return Correct Last Index") {
		list.Add(1);
		REQUIRE(1 == list.Get(list.Size() - 1));
		list.Add(2);
		REQUIRE(2 == list.Get(list.Size() - 1));
		list.Add(3);
		REQUIRE(3 == list.Get(list.Size() - 1));
	}

	SECTION("Should Return Correct Elements") {
		list.Add(1);
		list.Add(2);
		list.Add(3);
		list.Add(4);
		
		REQUIRE(1 == list.Get(0));
		REQUIRE(2 == list.Get(1));
		REQUIRE(3 == list.Get(2));
		REQUIRE(4 == list.Get(3));
	}

	SECTION("Should Throw Exception When Negative Index") {
		REQUIRE_THROWS_AS(list.Get(-1), std::out_of_range);
	}

	SECTION("Should Throw Exception When Larger Index") {
		REQUIRE_THROWS_AS(list.Get(0), std::out_of_range);
		list.Add(0);
		list.Add(1);
		list.Add(2);

		REQUIRE_THROWS_AS(list.Get(100), std::out_of_range);
		REQUIRE_THROWS_AS(list.Get(3), std::out_of_range);
	}
}

TEST_CASE("LinkedList.GetIndex Tests", "[LinkedList]") {
	LinkedList<int> list = LinkedList<int>();

	SECTION("Should Return Correct Index") {
		list.Add(15);
		list.Add(50);
		list.Add(3);
		list.Add(100);

		REQUIRE(0 == list.GetIndex(15));
		REQUIRE(1 == list.GetIndex(50));
		REQUIRE(2 == list.GetIndex(3));
		REQUIRE(3 == list.GetIndex(100));
	}

	SECTION("Should Return Negative") {
		list.Add(15);
		list.Add(50);
		list.Add(3);
		list.Add(100);

		REQUIRE(-1 == list.GetIndex(200));
		REQUIRE(-1 == list.GetIndex(14));
	}
}

TEST_CASE("LinkedList.IndexOperator Tests", "[LinkedList]") {
	LinkedList<int> list = LinkedList<int>();

	SECTION("Should Return Correct First Element") {
		list.Push(1);
		REQUIRE(1 == list[0]);
		list.Push(2);
		REQUIRE(2 == list[0]);
		list.Push(3);
		REQUIRE(3 == list[0]);
	}

	SECTION("Should Return Correct Last Element") {
		list.Add(1);
		REQUIRE(1 == list[list.Size() - 1]);
		list.Add(2);
		REQUIRE(2 == list[list.Size() - 1]);
		list.Add(3);
		REQUIRE(3 == list[list.Size() - 1]);
	}

	SECTION("Should Return Correct Elements") {
		list.Add(1);
		list.Add(2);
		list.Add(3);
		list.Add(4);

		REQUIRE(1 == list[0]);
		REQUIRE(2 == list[1]);
		REQUIRE(3 == list[2]);
		REQUIRE(4 == list[3]);
	}

	SECTION("Should Throw Exception When Negative Index") {
		REQUIRE_THROWS_AS(list[-1], std::out_of_range);
	}

	SECTION("Should Throw Exception When Larger Index") {
		REQUIRE_THROWS_AS(list[0], std::out_of_range);
		list.Add(0);
		list.Add(1);
		list.Add(2);

		REQUIRE_THROWS_AS(list[100], std::out_of_range);
		REQUIRE_THROWS_AS(list[3], std::out_of_range);
	}
}

TEST_CASE("LinkedList.Remove Tests", "[LinkedList]") {
	LinkedList<int> list = LinkedList<int>();

	SECTION("Should Return False If Empty") {
		REQUIRE_FALSE(list.Remove(5));
	}

	SECTION("Should Return False If Non Element Removed") {
		list.Add(5);
		REQUIRE_FALSE(list.Remove(4));
		REQUIRE(1 == list.Size());
	}

	SECTION("Should Return False On Double If Non Elements Removed") {
		list.Add(5);
		list.Add(10);
		REQUIRE_FALSE(list.Remove(4));
		REQUIRE_FALSE(list.Remove(9));
		REQUIRE(2 == list.Size());
	}

	SECTION("Should Return False On Triple If Non Elements Removed") {
		list.Add(5);
		list.Add(10);
		list.Add(15);
		REQUIRE_FALSE(list.Remove(4));
		REQUIRE_FALSE(list.Remove(9));
		REQUIRE(3 == list.Size());
	}

	SECTION("Should Return True On Single If Removed") {
		list.Add(5);
		REQUIRE(list.Remove(5));
		REQUIRE(0 == list.Size());
	}

	SECTION("Should Return True On Double If Removed") {
		list.Add(5);
		list.Add(10);
		REQUIRE(list.Remove(10));
		REQUIRE(1 == list.Size());
	}

	SECTION("Should Return True On Triple If Removed") {
		list.Add(5);
		list.Add(10);
		list.Add(15);
		REQUIRE(list.Remove(10));
		REQUIRE(2 == list.Size());
	}
};

TEST_CASE("LinkedList.RemoveAt Tests", "[LinkedList]") {
	LinkedList<int> list = LinkedList<int>();

	SECTION("Should Return Element If Removed") {
		list.Add(5);
		REQUIRE(5 == list.RemoveAt(0));
		REQUIRE(0 == list.Size());
	}

	SECTION("Should Return Double Element If Removed") {
		list.Add(5);
		list.Add(10);
		REQUIRE(10 == list.RemoveAt(1));
		REQUIRE(1 == list.Size());
	}

	SECTION("Should Return Triple Element If Removed") {
		list.Add(5);
		list.Add(10);
		list.Add(15);
		REQUIRE(10 == list.RemoveAt(1));
		REQUIRE(2 == list.Size());
	}

	SECTION("Should Throw Exception If Negative Index") {
		REQUIRE_THROWS_AS(list.RemoveAt(-1), std::out_of_range);
	}

	SECTION("Should Throw Exception If Large Index") {
		REQUIRE_THROWS_AS(list.RemoveAt(0), std::out_of_range);
		list.Add(1);
		list.Add(2);
		list.Add(3);
		REQUIRE_THROWS_AS(list.RemoveAt(3), std::out_of_range);
		REQUIRE_THROWS_AS(list.RemoveAt(100), std::out_of_range);
	}
}

TEST_CASE("LinkedList.Clear Tests", "[LinkedList]") {
	LinkedList<int> list = LinkedList<int>();

	SECTION("Should Clear If Empty") {
		REQUIRE(0 == list.Size());
		list.Clear();
		REQUIRE(0 == list.Size());
	}

	SECTION("Should Clear If Size 1") {
		list.Add(1);
		REQUIRE(1 == list.Size());
		list.Clear();
		REQUIRE(0 == list.Size());
	}

	SECTION("Should Clear If Size 2") {
		list.Add(1);
		list.Add(2);
		REQUIRE(2 == list.Size());
		list.Clear();
		REQUIRE(0 == list.Size());
	}

	SECTION("Should Clear If Size 3") {
		list.Add(1);
		list.Add(2);
		list.Add(3);
		REQUIRE(3 == list.Size());
		list.Clear();
		REQUIRE(0 == list.Size());
	}
}

TEST_CASE("LinkedList.Size Tests", "[LinkedList]") {
	LinkedList<int> list = LinkedList<int>();

	SECTION("Should Return Zero Size") {
		REQUIRE(0 == list.Size());
	}

	SECTION("Should Return One Size") {
		list.Add(1);
		REQUIRE(1 == list.Size());
	}

	SECTION("Should Return Two Size") {
		list.Add(1);
		list.Add(2);
		REQUIRE(2 == list.Size());
	}

	SECTION("Should Return Three Size") {
		list.Add(1);
		list.Add(2);
		list.Add(3);
		REQUIRE(3 == list.Size());
	}
};