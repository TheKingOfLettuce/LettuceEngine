#include "catch_amalgamated.hpp"
#include "LettuceEngine/LettuceObject.h"
#include "LettuceEngine/Components/ComponentFactory.h"
#include <unordered_set>

using LettuceEngine::Math::Vector2;

class SaveComponent : public Component {

};
REGISTER_COMPONENT(SaveComponent);

TEST_CASE("LettuceObject.Position Tests", "[LettuceObject]") {
    LettuceObject obj = LettuceObject();

    SECTION("Should Be Zero Vector On Start") {
        REQUIRE(obj.Position() == Vector2::Zero());
    }

    SECTION("Should Be Set Vector") {
		Vector2 newPos = Vector2(5, 5);
		obj.SetPosition(newPos);
        REQUIRE_FALSE(obj.Position() == Vector2::Zero());
        REQUIRE(obj.Position() == newPos);
    }

    SECTION("Should Offset Children") {
        LettuceObject* childA = new LettuceObject();
		LettuceObject* childB = new LettuceObject();
		obj.AddChild(childA);
		childA->AddChild(childB);
		Vector2 newPos = Vector2();
		newPos.X = 100;
		newPos.Y = 100;
		obj.SetPosition(newPos);
		newPos.X = 150;
		newPos.Y = 150;
		childA->SetPosition(newPos);
		newPos.X = 200;
		newPos.Y = 200;
		childB->SetPosition(newPos);

		newPos.X = 150;
		newPos.Y = 150;
		obj.SetPosition(newPos);

		REQUIRE(newPos == obj.Position());
		newPos.X = 200;
		newPos.Y = 200;
		REQUIRE(newPos == childA->Position());
		newPos.X = 250;
		newPos.Y = 250;
		REQUIRE(newPos == childB->Position());
    }
}

TEST_CASE("LettuceObject.AddComponent Tests", "[LettuceObject]") {
    LettuceObject obj = LettuceObject();

    SECTION("Should Add Component") {
		Component* c = new Component();
		obj.AddComponent(c);
    }

    SECTION("Should Throw Exception When Component Null") {
        REQUIRE_THROWS_AS(obj.AddComponent((Component*)nullptr), std::invalid_argument);
    }

    SECTION("Should Default Component Enabled") {
		Component* c = new Component();
		obj.AddComponent(c);
		REQUIRE(c->GetEnabled());
    }

    SECTION("Should Default Component Enabled") {
		Component* c = new Component();
		obj.AddComponent(c, false);
		REQUIRE_FALSE(c->GetEnabled());
    }
}

TEST_CASE("LettuceObject.HasComponent Tests", "[LettuceObject]") {
    class OtherComponent : public Component {};
    LettuceObject obj = LettuceObject();

    SECTION("Should Return False When No Components") {
		REQUIRE_FALSE(obj.HasComponent<Component>());
		REQUIRE_FALSE(obj.HasComponent<OtherComponent>());
    }

    SECTION("Should Return True When Component Added") {
		obj.AddComponent(new Component());
		REQUIRE(obj.HasComponent<Component>());
		REQUIRE_FALSE(obj.HasComponent<OtherComponent>());
	}

    SECTION("Should Return True When Other Component Added") {
		obj.AddComponent(new OtherComponent());
		REQUIRE_FALSE(obj.HasComponent<Component>());
		REQUIRE(obj.HasComponent<OtherComponent>());
    }

    SECTION("Should Return True When Both Components Added") {
		obj.AddComponent(new Component());
		obj.AddComponent(new OtherComponent());
		REQUIRE(obj.HasComponent<Component>());
		REQUIRE(obj.HasComponent<OtherComponent>());
    }
}

TEST_CASE("LettuceObject.RemoveComponent Test", "[LettuceObject]") {
    class OtherComponent : public Component {};
    LettuceObject obj = LettuceObject();

    SECTION("Should Return Null When No Components Added") {
        REQUIRE(obj.RemoveComponent<Component>() == nullptr);
        REQUIRE(obj.RemoveComponent<OtherComponent>() == nullptr);
    }

    SECTION("Should Return True When Added Component Removed") {
        Component* component = new Component();
		obj.AddComponent(component);
		REQUIRE(component == obj.RemoveComponent<Component>());
		REQUIRE_FALSE(obj.HasComponent<Component>());
		delete component;
    }

    SECTION("Should Return True When One Of Added Components Removed") {
        Component* component = new Component();
		OtherComponent* otherComponent = new OtherComponent();
		obj.AddComponent(component);
		obj.AddComponent(otherComponent);

		REQUIRE(component == obj.RemoveComponent<Component>());
		REQUIRE(obj.HasComponent<OtherComponent>());
		REQUIRE_FALSE(obj.HasComponent<Component>());
		delete component;
    }

    SECTION("Should Return True When Other Added Component Removed") {
        Component* component = new Component();
		OtherComponent* otherComponent = new OtherComponent();
		obj.AddComponent(component);
		obj.AddComponent(otherComponent);

		REQUIRE(otherComponent == obj.RemoveComponent<OtherComponent>());
		REQUIRE_FALSE(obj.HasComponent<OtherComponent>());
		REQUIRE(obj.HasComponent<Component>());
		delete otherComponent;
    }
}

TEST_CASE("LettuceObject.SetEnabled Tests", "[LettuceObject]") {
    LettuceObject obj = LettuceObject();

    SECTION("Set Enabled Should Default To True") {
        REQUIRE(obj.Enabled());
    }

    SECTION("Set Enabled Should Set To False") {
        obj.SetEnable(false);
		REQUIRE_FALSE(obj.Enabled());
    }

    SECTION("Set Enabled Should Set Component To False When Object Set To False") {
        Component *c = new Component();
		obj.AddComponent(c);
		REQUIRE(c->GetEnabled());
		obj.SetEnable(false);
		REQUIRE_FALSE(c->GetEnabled());
    }

    SECTION("Set Enabled Should Set Children To False When One Parent Set To False") {
        LettuceObject* layer1A = new LettuceObject();
		obj.AddChild(layer1A);
		LettuceObject* layer1B = new LettuceObject();
		obj.AddChild(layer1B);
		LettuceObject* layer1AChild = new LettuceObject();
		layer1A->AddChild(layer1AChild);
		LettuceObject* layer1BChildA = new LettuceObject();
		layer1B->AddChild(layer1BChildA);
		LettuceObject* layer1BChildB = new LettuceObject();
		layer1B->AddChild(layer1BChildB);
		LettuceObject* layer1BChildBChildA = new LettuceObject();
		layer1BChildB->AddChild(layer1BChildBChildA);

		layer1B->SetEnable(false);
		REQUIRE_FALSE(layer1B->Enabled());
		REQUIRE_FALSE(layer1BChildA->Enabled());
		REQUIRE_FALSE(layer1BChildB->Enabled());
		REQUIRE_FALSE(layer1BChildBChildA->Enabled());
		REQUIRE(layer1A->Enabled());
		REQUIRE(layer1AChild->Enabled());
    }

    SECTION("Set Enabled Should Set Children To True When Parent Is Toggled") {
        LettuceObject* layer1A = new LettuceObject();
		obj.AddChild(layer1A);
		LettuceObject* layer1B = new LettuceObject();
		obj.AddChild(layer1B);
		LettuceObject* layer1AChild = new LettuceObject();
		layer1A->AddChild(layer1AChild);
		LettuceObject* layer1BChildA = new LettuceObject();
		layer1B->AddChild(layer1BChildA);
		LettuceObject* layer1BChildB = new LettuceObject();
		layer1B->AddChild(layer1BChildB);
		LettuceObject* layer1BChildBChildA = new LettuceObject();
		layer1BChildB->AddChild(layer1BChildBChildA);

		layer1B->SetEnable(false);
        layer1B->SetEnable(true);
		REQUIRE(layer1B->Enabled());
		REQUIRE(layer1BChildA->Enabled());
		REQUIRE(layer1BChildB->Enabled());
		REQUIRE(layer1BChildBChildA->Enabled());
		REQUIRE(layer1A->Enabled());
		REQUIRE(layer1AChild->Enabled());
    }

    SECTION("Set Enabled Should Set Children To False When Root Set To False") {
        LettuceObject* layer1A = new LettuceObject();
		obj.AddChild(layer1A);
		LettuceObject* layer1B = new LettuceObject();
		obj.AddChild(layer1B);
		LettuceObject* layer1AChild = new LettuceObject();
		layer1A->AddChild(layer1AChild);
		LettuceObject* layer1BChildA = new LettuceObject();
		layer1B->AddChild(layer1BChildA);
		LettuceObject* layer1BChildB = new LettuceObject();
		layer1B->AddChild(layer1BChildB);
		LettuceObject* layer1BChildBChildA = new LettuceObject();
		layer1BChildB->AddChild(layer1BChildBChildA);

		obj.SetEnable(false);
		REQUIRE_FALSE(layer1B->Enabled());
		REQUIRE_FALSE(layer1BChildA->Enabled());
		REQUIRE_FALSE(layer1BChildB->Enabled());
		REQUIRE_FALSE(layer1BChildBChildA->Enabled());
		REQUIRE_FALSE(layer1A->Enabled());
		REQUIRE_FALSE(layer1AChild->Enabled());
    }
}

TEST_CASE("LettuceObject.AddChild Tests", "[LettuceObject]") {
	LettuceObject obj = LettuceObject();

	SECTION("Should Add Object") {
		LettuceObject* child = new LettuceObject();
		obj.AddChild(child);
		REQUIRE(obj.NumChildren() == 1);
	}

	SECTION("Should Throw Exception When Null Child Added") {
		REQUIRE_THROWS_AS(obj.AddChild(nullptr), std::invalid_argument);
	}
}

TEST_CASE("LettuceObject.GetChildAt Tests", "[LettuceObject]") {
	LettuceObject obj = LettuceObject();

	SECTION("Should Throw Exception When Negative Index Passed") {
		REQUIRE_THROWS_AS(obj.GetChildAt(-1), std::out_of_range);
		REQUIRE_THROWS_AS(obj.GetChildAt(-10), std::out_of_range);
	}

	SECTION("Should Throw Exception When No Children Added") {
		REQUIRE_THROWS_AS(obj.GetChildAt(0), std::out_of_range);
		REQUIRE_THROWS_AS(obj.GetChildAt(10), std::out_of_range);
	}

	SECTION("Should Throw Exception When Child Index Out Of Range") {
		obj.AddChild(new LettuceObject());
		obj.AddChild(new LettuceObject());
		REQUIRE_THROWS_AS(obj.GetChildAt(3), std::out_of_range);
		REQUIRE_THROWS_AS(obj.GetChildAt(10), std::out_of_range);
	}

	SECTION("Should Return True") {
		LettuceObject* child1 = new LettuceObject();
		LettuceObject* child2 = new LettuceObject();
		obj.AddChild(child1);
		obj.AddChild(child2);
		REQUIRE(child1 == obj.GetChildAt(0));
		REQUIRE(child2 == obj.GetChildAt(1));
	}
}

TEST_CASE("LettuceObject.GetChildIndex Tests", "[LettuceObject]") {
	LettuceObject obj = LettuceObject();

	SECTION("Should Return -1 When No Children Added") {
		REQUIRE(-1 == obj.GetChildIndex(nullptr));
		LettuceObject* nonChild = new LettuceObject();
		REQUIRE(-1 == obj.GetChildIndex(nonChild));
		delete nonChild;
	}

	SECTION("Should Return Index For Added Child") {
		LettuceObject* child1 = new LettuceObject();
		LettuceObject* child2 = new LettuceObject();
		obj.AddChild(child1);
		REQUIRE(0 == obj.GetChildIndex(child1));
		REQUIRE(-1 == obj.GetChildIndex(child2));
		delete child2;
	}

	SECTION("Should Return Index For Added Children") {
		LettuceObject* child1 = new LettuceObject();
		LettuceObject* child2 = new LettuceObject();
		LettuceObject* child3 = new LettuceObject();
		obj.AddChild(child1);
		obj.AddChild(child2);
		obj.AddChild(child3);
		REQUIRE(0 == obj.GetChildIndex(child1));
		REQUIRE(1 == obj.GetChildIndex(child2));
		REQUIRE(2 == obj.GetChildIndex(child3));
	}
}

TEST_CASE("LettuceObject.RemoveChild Tests", "[LettuceObject]") {
	LettuceObject obj = LettuceObject();

	SECTION("Should Return False When No Children Added") {
		REQUIRE_FALSE(obj.RemoveChild(nullptr));
		LettuceObject* child = new LettuceObject();
		REQUIRE_FALSE(obj.RemoveChild(child));
		delete child;
	}

	SECTION("Should Return True If One Child Added") {
		LettuceObject* child1 = new LettuceObject();
		LettuceObject* child2 = new LettuceObject();
		obj.AddChild(child1);
		REQUIRE_FALSE(obj.RemoveChild(child2));
		REQUIRE(obj.RemoveChild(child1));
		REQUIRE(0 == obj.NumChildren());
		delete child1;
		delete child2;
	}

	SECTION("Should Retrun True If Both Children Added") {
		LettuceObject* child1 = new LettuceObject();
		LettuceObject* child2 = new LettuceObject();
		obj.AddChild(child1);
		obj.AddChild(child2);
		REQUIRE(obj.RemoveChild(child1));
		REQUIRE(1 == obj.NumChildren());
		REQUIRE(obj.RemoveChild(child2));
		REQUIRE(0 == obj.NumChildren());
		delete child1;
		delete child2;
	}

	SECTION("Should Return True If Three Children Added And One Removed") {
		LettuceObject* child1 = new LettuceObject();
		LettuceObject* child2 = new LettuceObject();
		LettuceObject* child3 = new LettuceObject();
		obj.AddChild(child1);
		obj.AddChild(child2);
		obj.AddChild(child3);
		REQUIRE(obj.RemoveChild(child1));
		REQUIRE(2 == obj.NumChildren());
		REQUIRE(child2 == obj.GetChildAt(0));
		REQUIRE(child3 == obj.GetChildAt(1));
		delete child1;
	}
}

TEST_CASE("LettuceObject.RemoveChildAt Tests", "[LettuceObject]") {
	LettuceObject obj = LettuceObject();

	SECTION("Should Throw Exception When No Children") {
		REQUIRE_THROWS_AS(obj.RemoveChildAt(0), std::out_of_range);
	}

	SECTION("Should Return True When Children Removed") {
		LettuceObject* child1 = new LettuceObject();
		LettuceObject* child2 = new LettuceObject();
		LettuceObject* child3 = new LettuceObject();
		LettuceObject* child4 = new LettuceObject();
		LettuceObject* child5 = new LettuceObject();
		obj.AddChild(child1);
		obj.AddChild(child2);
		obj.AddChild(child3);
		obj.AddChild(child4);
		obj.AddChild(child5);

		REQUIRE(obj.RemoveChildAt(2) == child3);
		REQUIRE(obj.RemoveChildAt(0) == child1);
		REQUIRE(obj.RemoveChildAt(2) == child5);
		delete child3;
		delete child1;
		delete child5;
	}
}

TEST_CASE("LettuceObject.Render Tests", "[LettuceObject]") {
	class TestRenderComponent : public Component {
	public:
		bool DidRender = false;
		void Render(RenderMessage* msg) override {
			DidRender = true;
		}
	};
	LettuceObject obj = LettuceObject();

	SECTION("Should Render Component") {
		TestRenderComponent* component = new TestRenderComponent();
		obj.AddComponent(component);
		RenderMessage* msg = new RenderMessage();
		obj.Render(msg);
		REQUIRE(component->DidRender);
		delete msg;
	}

	SECTION("Should Not Render Component If Component Removed") {
		TestRenderComponent* component = new TestRenderComponent();
		obj.AddComponent(component);
		obj.RemoveComponent<TestRenderComponent>();
		RenderMessage* msg = new RenderMessage();
		obj.Render(msg);
		REQUIRE_FALSE(component->DidRender);
		delete msg;
		delete component;
	}
}

TEST_CASE("LettuceObject.Update Tests", "[LettuceObject]") {
	class TestUpdateComponent : public Component {
	public:
		bool DidUpdate = false;
		void Update(UpdateMessage* msg) override {
			DidUpdate = true;
		}
	};
	LettuceObject obj = LettuceObject();

	SECTION("Should Update Component") {
		TestUpdateComponent* component = new TestUpdateComponent();
		obj.AddComponent(component);
		UpdateMessage* msg = new UpdateMessage(0);
		obj.Update(msg);
		REQUIRE(component->DidUpdate);
		delete msg;
	}

	SECTION("Should Not Update Component If Component Removed") {
		TestUpdateComponent* component = new TestUpdateComponent();
		obj.AddComponent(component);
		obj.RemoveComponent<TestUpdateComponent>();
		UpdateMessage* msg = new UpdateMessage(0);
		obj.Update(msg);
		REQUIRE_FALSE(component->DidUpdate);
		delete msg;
		delete component;
	}
}

TEST_CASE("LettuceObject.SaveToData Tests", "[LettuceObject]") {
	LettuceObject obj = LettuceObject();

	SECTION("Should Save Position 0") {
		LettuceObjectData data = obj.SaveToData();
		REQUIRE(data.Position == Vector2::Zero());
	}

	SECTION("Should Save Set Position") {
		Vector2 pos = {15, 75};
		obj.SetPosition(pos);
		LettuceObjectData data = obj.SaveToData();
		REQUIRE(data.Position == pos);
	}

	SECTION("Should Save Enabled False") {
		obj.SetEnable(false);
		LettuceObjectData data = obj.SaveToData();
		REQUIRE_FALSE(data.Enabled);
	}

	SECTION("Should Save Enabled True") {
		obj.SetEnable(true);
		LettuceObjectData data = obj.SaveToData();
		REQUIRE(data.Enabled);
	}

	SECTION("Should Save Component Info") {
		SaveComponent* s = new SaveComponent();
		obj.AddComponent(s);
		LettuceObjectData data = obj.SaveToData();
		REQUIRE(data.ComponentData.size() == 1);
		nlohmann::json saveJ;
		s->SaveToJson(saveJ);
		REQUIRE(data.ComponentData[0].ComponentData == saveJ);
		REQUIRE(data.ComponentData[0].TypeName == Factory<Component>::GetSaveName<SaveComponent>());
	}

	SECTION("Should Save Child Info") {
		LettuceObject* child = new LettuceObject();
		child->SetEnable(false);
		obj.AddChild(child);
		LettuceObjectData data = obj.SaveToData();
		REQUIRE(data.ChildrenData.size() == 1);
		REQUIRE(data.ChildrenData[0].Enabled == child->SaveToData().Enabled);
	}
}

TEST_CASE("LettuceObject.LoadFromData Tests", "[LettuceObject]") {
	SECTION("Should Load Position 0") {
		LettuceObject* obj = new LettuceObject();
		LettuceObjectData data = obj->SaveToData();
		delete obj;
		obj = new LettuceObject();
		obj->LoadFromData(data);
		REQUIRE(obj->Position() == Vector2::Zero());
		delete obj;
	}

	SECTION("Should Load Set Position") {
		LettuceObject* obj = new LettuceObject();
		Vector2 pos = {15, 75};
		obj->SetPosition(pos);
		LettuceObjectData data = obj->SaveToData();
		delete obj;
		obj = new LettuceObject();
		obj->LoadFromData(data);
		REQUIRE(obj->Position() == pos);
		delete obj; 
	}

	SECTION("Should Load Enabled False") {
		LettuceObject* obj = new LettuceObject();
		obj->SetEnable(false);
		LettuceObjectData data = obj->SaveToData();
		delete obj;
		obj = new LettuceObject();
		obj->LoadFromData(data);
		REQUIRE_FALSE(obj->Enabled());
		delete obj;
	}

	SECTION("Should Load Enabled True") {
		LettuceObject* obj = new LettuceObject();
		obj->SetEnable(true);
		LettuceObjectData data = obj->SaveToData();
		delete obj;
		obj = new LettuceObject();
		obj->SetEnable(false);
		REQUIRE_FALSE(obj->Enabled());
		obj->LoadFromData(data);
		REQUIRE(obj->Enabled());
		delete obj;
	}

	SECTION("Should Load Component") {
		LettuceObject* obj = new LettuceObject();
		SaveComponent* s = new SaveComponent();
		obj->AddComponent(s);
		LettuceObjectData data = obj->SaveToData();
		delete obj;
		obj = new LettuceObject();
		REQUIRE_FALSE(obj->HasComponent<SaveComponent>());
		obj->LoadFromData(data);
		REQUIRE(obj->HasComponent<SaveComponent>());
		delete obj;
	}

	SECTION("Should Load Child") {
		LettuceObject* obj = new LettuceObject();
		LettuceObject* child = new LettuceObject();
		child->SetEnable(false);
		obj->AddChild(child);
		LettuceObjectData data = obj->SaveToData();
		delete obj;
		obj = new LettuceObject();
		REQUIRE(obj->NumChildren() == 0);
		obj->LoadFromData(data);
		REQUIRE(obj->NumChildren() == 1);
		REQUIRE_FALSE(obj->GetChildAt(0)->Enabled());
		delete obj;
	}
}

TEST_CASE("LettuceObject.GetComponent Tests", "[LettuceObject]") {
	class OtherComponent : public Component {};
	class SpecialComponent : public Component {};

	SECTION("Should return null when no components added") {
		LettuceObject obj = LettuceObject();
		REQUIRE(obj.GetComponent<Component>() == nullptr);
		REQUIRE(obj.GetComponent<OtherComponent>() == nullptr);
		REQUIRE(obj.GetComponent<SpecialComponent>() == nullptr);
	}

	SECTION("Should return special component when added") {
		LettuceObject obj = LettuceObject();
		SpecialComponent* comp = new SpecialComponent();
		obj.AddComponent(comp);
		REQUIRE(obj.GetComponent<Component>() == nullptr);
		REQUIRE(obj.GetComponent<OtherComponent>() == nullptr);
		REQUIRE(obj.GetComponent<SpecialComponent>() == comp);
	}

	SECTION("Should return all components when added") {
		LettuceObject obj = LettuceObject();
		Component* comp = new Component();
		OtherComponent* otherComp = new OtherComponent();
		SpecialComponent* specialComp = new SpecialComponent();
		obj.AddComponent(comp);
		obj.AddComponent(otherComp);
		obj.AddComponent(specialComp);
		REQUIRE(obj.GetComponent<Component>() == comp);
		REQUIRE(obj.GetComponent<OtherComponent>() == otherComp);
		REQUIRE(obj.GetComponent<SpecialComponent>() == specialComp);
	}
}

TEST_CASE("LettuceObject.GetComponents Tests", "[LettuceObject]") {
	class OtherComponent : public Component {};
	class SpecialComponent : public Component {};

	SECTION("Should return null when no components added") {
		LettuceObject obj = LettuceObject();
		REQUIRE(obj.GetComponents<Component>().size() == 0);
		REQUIRE(obj.GetComponents<OtherComponent>().size() == 0);
		REQUIRE(obj.GetComponents<SpecialComponent>().size() == 0);
	}

	SECTION("Should return 1 special component when added") {
		LettuceObject obj = LettuceObject();
		SpecialComponent* comp = new SpecialComponent();
		obj.AddComponent(comp);
		REQUIRE(obj.GetComponents<Component>().size() == 0);
		REQUIRE(obj.GetComponents<OtherComponent>().size() == 0);
		REQUIRE(obj.GetComponents<SpecialComponent>().size() == 1);
	}

	SECTION("Should return 2 special component when added") {
		LettuceObject obj = LettuceObject();
		SpecialComponent* comp = new SpecialComponent();
		SpecialComponent* comp2 = new SpecialComponent();
		obj.AddComponent(comp);
		obj.AddComponent(comp2);
		REQUIRE(obj.GetComponents<Component>().size() == 0);
		REQUIRE(obj.GetComponents<OtherComponent>().size() == 0);
		REQUIRE(obj.GetComponents<SpecialComponent>().size() == 2);
	}

	SECTION("Should return all components when added") {
		LettuceObject obj = LettuceObject();
		Component* comp = new Component();
		Component* comp2 = new Component();
		OtherComponent* otherComp = new OtherComponent();
		OtherComponent* otherComp2 = new OtherComponent();
		OtherComponent* otherComp3 = new OtherComponent();
		SpecialComponent* specialComp = new SpecialComponent();
		SpecialComponent* specialComp2 = new SpecialComponent();
		SpecialComponent* specialComp3 = new SpecialComponent();
		SpecialComponent* specialComp4 = new SpecialComponent();
		obj.AddComponent(comp);
		obj.AddComponent(comp2);
		obj.AddComponent(otherComp);
		obj.AddComponent(otherComp2);
		obj.AddComponent(otherComp3);
		obj.AddComponent(specialComp);
		obj.AddComponent(specialComp2);
		obj.AddComponent(specialComp3);
		obj.AddComponent(specialComp4);
		std::vector<Component*> comps = obj.GetComponents<Component>();
		std::vector<OtherComponent*> otherComps = obj.GetComponents<OtherComponent>();
		std::vector<SpecialComponent*> specialComps = obj.GetComponents<SpecialComponent>();
		REQUIRE(comps.size() == 2);
		REQUIRE(otherComps.size() == 3);
		REQUIRE(specialComps.size() == 4);
		// check to see if each component truly is unique
		std::unordered_set<Component*> allComps = std::unordered_set<Component*>();
		allComps.emplace(comp);
		allComps.emplace(comp2);
		allComps.emplace(otherComp);
		allComps.emplace(otherComp2);
		allComps.emplace(otherComp3);
		allComps.emplace(specialComp);
		allComps.emplace(specialComp2);
		allComps.emplace(specialComp3);
		allComps.emplace(specialComp4);
		for(Component* c : comps) {
			allComps.erase(c);
		}
		for(OtherComponent* c : otherComps) {
			allComps.erase(c);
		}
		for(SpecialComponent* c : specialComps) {
			allComps.erase(c);
		}

		REQUIRE(allComps.size() == 0);
	}
}