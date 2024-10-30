#include "catch_amalgamated.hpp"
#include "LettuceEngine/Assets/Managers/AssetManager.h"
#include "LettuceEngine/Assets/Managers/AssetFactory.h"
#include "LettuceEngine/Assets/Managers/AssetCollectionFactory.h"

const char* AssetManagerTAG = "[AssetManager]";

class CustomAsset : public Asset {
    public:
        CustomAsset(std::string id) : Asset(id) {}
};

TEST_CASE("AssetManager.AddAsset Tests", AssetManagerTAG) {
    AssetManager::UnloadAllAssets();

    SECTION("Should add assets") {
        REQUIRE(AssetManager::AddAsset(new Asset("Asset1")));
        REQUIRE(AssetManager::AddAsset(new Asset("Asset2")));
        REQUIRE(AssetManager::AddAsset(new CustomAsset("CustomAsset1")));
        REQUIRE(AssetManager::AddAsset(new CustomAsset("CustomAsset2")));
    }

    SECTION("Should add assets if same ID but different type") {
        REQUIRE(AssetManager::AddAsset(new Asset("Asset1")));
        REQUIRE(AssetManager::AddAsset(new Asset("Asset2")));
        REQUIRE(AssetManager::AddAsset(new CustomAsset("Asset1")));
        REQUIRE(AssetManager::AddAsset(new CustomAsset("Asset2")));
    }

    SECTION("Should not add assets if no collection added") {
        Asset* asset = new Asset("Asset1");
        CustomAsset* customAsset = new CustomAsset("CustomAsset1");
        REQUIRE_FALSE(AssetManager::AddAsset(asset, false));
        REQUIRE_FALSE(AssetManager::AddAsset(customAsset, false));

        delete asset;
        delete customAsset;
    }

    SECTION("Should not add assets if ID match") {
        Asset* asset1 = new Asset("Asset1");
        Asset* dupeAsset1 = new Asset("Asset1");

        REQUIRE(AssetManager::AddAsset(asset1));
        REQUIRE_FALSE(AssetManager::AddAsset(dupeAsset1));

        delete dupeAsset1;
    }

    SECTION("Should throw if null provided") {
        REQUIRE_THROWS_AS(AssetManager::AddAsset(nullptr), std::invalid_argument);
    }
}

TEST_CASE("AssetManager.GetAsset Tests", AssetManagerTAG) {
    AssetManager::UnloadAllAssets();

    SECTION("Should Get Assets") {
        Asset* asset = new Asset("Asset");
        CustomAsset* customAsset = new CustomAsset("CustomAsset");
        AssetManager::AddAsset(asset);
        AssetManager::AddAsset(customAsset);

        REQUIRE(AssetManager::GetAsset<Asset>("Asset") == asset);
        REQUIRE(AssetManager::GetAsset<CustomAsset>("CustomAsset"));
    }

    SECTION("Should Not Get Assets If Wrong ID") {
        AssetManager::AddAsset(new Asset("Asset"));
        AssetManager::AddAsset(new CustomAsset("CustomAsset"));

        // IDs are case sensitive
        REQUIRE(AssetManager::GetAsset<Asset>("asset") == nullptr);
        REQUIRE(AssetManager::GetAsset<CustomAsset>("cusomtaSSET") == nullptr);
        REQUIRE(AssetManager::GetAsset<Asset>("FOOL!") == nullptr);
    }

    SECTION("Should Not Get Assets If None Added") {
        REQUIRE(AssetManager::GetAsset<Asset>("nothingtoseehere") == nullptr);
        REQUIRE(AssetManager::GetAsset<CustomAsset>("notAdded") == nullptr);
    }

    SECTION("Should Add Assets with Same ID but Different Type") {
        Asset* asset = new Asset("Asset");
        CustomAsset* customAsset = new CustomAsset("Asset");

        AssetManager::AddAsset(asset);
        REQUIRE(AssetManager::GetAsset<Asset>("Asset") == asset);
        REQUIRE(AssetManager::GetAsset<CustomAsset>("Asset") == nullptr);
        AssetManager::AddAsset(customAsset);
        REQUIRE(AssetManager::GetAsset<CustomAsset>("Asset") == customAsset);
        REQUIRE(AssetManager::GetAsset<Asset>("Asset") != customAsset);
        REQUIRE(AssetManager::GetAsset<CustomAsset>("Asset") != asset);
    }
}

TEST_CASE("AssetManager.RemoveAsset Tests", AssetManagerTAG) {
    AssetManager::UnloadAllAssets();

    SECTION("Should Remove Added Assets") {
        Asset* asset = new Asset("Asset");
        CustomAsset* customAsset = new CustomAsset("Asset");
        AssetManager::AddAsset(asset);
        AssetManager::AddAsset(customAsset);

        REQUIRE(AssetManager::RemoveAsset(asset));
        REQUIRE(AssetManager::RemoveAsset(customAsset));

        delete asset;
        delete customAsset;
    }

    SECTION("Should Remove Added Assets with ID") {
        Asset* asset = new Asset("Asset");
        CustomAsset* customAsset = new CustomAsset("Asset");
        AssetManager::AddAsset(asset);
        AssetManager::AddAsset(customAsset);

        REQUIRE(AssetManager::RemoveAsset<Asset>(asset->GetAssetID()) == asset);
        REQUIRE(AssetManager::RemoveAsset<CustomAsset>(customAsset->GetAssetID()) == customAsset);

        delete asset;
        delete customAsset;
    }

    SECTION("Should Not Remove Assets if Pointers Not Same") {
        Asset* asset1 = new Asset("Asset1");
        Asset* asset1dupe = new Asset("Asset1");
        AssetManager::AddAsset(asset1);
        REQUIRE_FALSE(AssetManager::RemoveAsset(asset1dupe));

        delete asset1dupe;
    }

    SECTION("Should Not Remove If Asset Not Added") {
        Asset* asset3 = new Asset("Asset3");
        AssetManager::AddAsset(new Asset("Asset1"));
        AssetManager::AddAsset(new Asset("Asset2"));

        REQUIRE_FALSE(AssetManager::RemoveAsset(asset3));
        delete asset3;
    }

    SECTION("Should Not Remove If ID Not Added") {
        AssetManager::AddAsset(new Asset("Asset1"));
        AssetManager::AddAsset(new Asset("Asset2"));
        AssetManager::AddAsset(new Asset("Asset3"));

        REQUIRE(AssetManager::RemoveAsset<Asset>("Asset42") == nullptr);
        REQUIRE(AssetManager::RemoveAsset<Asset>("HelloWorld") == nullptr);
        REQUIRE(AssetManager::RemoveAsset<Asset>("FOOL!") == nullptr);
    }

    SECTION("Should Throw If Null") {
        REQUIRE_THROWS_AS(AssetManager::RemoveAsset<Asset>(nullptr), std::invalid_argument);
    }
}

TEST_CASE("AssetManager.HasAsset Tests", AssetManagerTAG) {
    AssetManager::UnloadAllAssets();

    SECTION("Should Find Asset With ID") {
        AssetManager::AddAsset(new Asset("Asset1"));
        AssetManager::AddAsset(new Asset("Asset2"));
        AssetManager::AddAsset(new Asset("Asset3"));

        REQUIRE(AssetManager::HasAsset<Asset>("Asset1"));
        REQUIRE(AssetManager::HasAsset<Asset>("Asset2"));
        REQUIRE(AssetManager::HasAsset<Asset>("Asset3"));
    }

    SECTION("Should Find Asset With Object") {
        Asset* asset1 = new Asset("Asset1");
        Asset* asset2 = new Asset("Asset2");
        Asset* asset3 = new Asset("Asset3");
        AssetManager::AddAsset(asset1);
        AssetManager::AddAsset(asset2);
        AssetManager::AddAsset(asset3);

        REQUIRE(AssetManager::HasAsset(asset1));
        REQUIRE(AssetManager::HasAsset(asset2));
        REQUIRE(AssetManager::HasAsset(asset3));
    }

    SECTION("Should Not Find Asset Without ID Added") {
        AssetManager::AddAsset(new Asset("Asset1"));
        AssetManager::AddAsset(new Asset("Asset2"));
        AssetManager::AddAsset(new Asset("Asset3"));

        REQUIRE_FALSE(AssetManager::HasAsset<Asset>("Asset42"));
        REQUIRE_FALSE(AssetManager::HasAsset<Asset>("HelloWorld"));
        REQUIRE_FALSE(AssetManager::HasAsset<Asset>("FOOL!"));
    }

    SECTION("Should Not Find Asset If Not Added") {
        Asset* asset3 = new Asset("Asset3");
        AssetManager::AddAsset(new Asset("Asset1"));
        AssetManager::AddAsset(new Asset("Asset2"));

        REQUIRE_FALSE(AssetManager::HasAsset(asset3));
        delete asset3;
    }

    SECTION("Should Not Find If Wrong Type") {
        Asset* asset= new Asset("Asset");
        AssetManager::AddAsset(asset);

        REQUIRE_FALSE(AssetManager::RemoveAsset<CustomAsset>("Asset"));
    }

    SECTION("Should Throw If Null") {
        REQUIRE_THROWS_AS(AssetManager::HasAsset<Asset>(nullptr), std::invalid_argument);
    }
}

class TestCollection : public AssetTypeCollection<CustomAsset> {
        public:
            TestCollection() : AssetTypeCollection() {}

            bool Flag = false;
        protected:
            bool AddAsset(CustomAsset* asset) override {
                Flag = true;
                return AssetTypeCollection::AddAsset(asset);
            }
};

TEST_CASE("AssetManager.AddAssetCollection Tests", AssetManagerTAG) {
    AssetManager::UnloadAllAssets();

    SECTION("Should Add Collection") {
        TestCollection* collection = new TestCollection();
        REQUIRE(AssetManager::AddAssetCollection<CustomAsset>(collection));
    }

    SECTION("Should Not Add Collection If Already Added") {
        TestCollection* collection = new TestCollection();
        AssetManager::AddAsset(new CustomAsset("Asset"));
        REQUIRE_FALSE(AssetManager::AddAssetCollection<CustomAsset>(collection));
    }

    SECTION("Should Call Custom Collection") {
        TestCollection* collection = new TestCollection();
        AssetManager::AddAssetCollection<CustomAsset>(collection);
        AssetManager::AddAsset(new CustomAsset("Asset"));
        REQUIRE(collection->Flag);
    }

    SECTION("Should Throw If Null") {
        REQUIRE_THROWS_AS(AssetManager::AddAssetCollection<Asset>(nullptr), std::invalid_argument);
    }
}

TEST_CASE("AssetManager.GetAssetCollection Tests", AssetManagerTAG) {
    AssetManager::UnloadAllAssets();

    SECTION("Should Get Collection") {
        TestCollection* collection = new TestCollection();
        AssetManager::AddAssetCollection<CustomAsset>(collection);
        REQUIRE(AssetManager::GetAssetCollection<CustomAsset>() == collection);
    }

    SECTION("Should Not Get Collection") {
        TestCollection* collection = new TestCollection();
        AssetManager::AddAsset(new CustomAsset("Asset"));
        REQUIRE_FALSE(AssetManager::GetAssetCollection<CustomAsset>() == collection);
    }

    SECTION("Should Return Null If None Added") {
        REQUIRE(AssetManager::GetAssetCollection<Asset>() == nullptr);
    }
}

TEST_CASE("AssetManager.UnloadAllAssets Tests", AssetManagerTAG) {
    AssetManager::UnloadAllAssets();

    SECTION("Should unload Assets") {
        AssetManager::AddAsset(new Asset("Asset"));
        REQUIRE(AssetManager::GetAsset<Asset>("Asset"));
        REQUIRE(AssetManager::GetAssetCollection<Asset>() != nullptr);
        AssetManager::UnloadAllAssets();
        REQUIRE_FALSE(AssetManager::GetAsset<Asset>("Asset"));
        REQUIRE(AssetManager::GetAssetCollection<Asset>() == nullptr);
    }

    SECTION("Should Keep Engine Asset Collections") {
        AssetManager::AddAsset(new Asset("Asset"));
        REQUIRE(AssetManager::GetAssetCollection<Asset>() != nullptr);
        REQUIRE(AssetManager::GetAssetCollection<ImageAsset>() != nullptr);
        REQUIRE(AssetManager::GetAssetCollection<Texture2DAsset>() != nullptr);
        AssetManager::UnloadAllAssets();
        REQUIRE(AssetManager::GetAssetCollection<Asset>() == nullptr);
        REQUIRE(AssetManager::GetAssetCollection<ImageAsset>() != nullptr);
        REQUIRE(AssetManager::GetAssetCollection<Texture2DAsset>() != nullptr);
    }
}

class CounterAsset : public Asset {
    public:
        CounterAsset() : Asset() {}
        CounterAsset(std::string id) : Asset(id) {}
        int Count = 0;

        void SaveToJson(nlohmann::json& j) const override {
            Asset::SaveToJson(j);
            j["count"] = Count;
        }

        void LoadFromJson(const nlohmann::json& data) override {
            Asset::LoadFromJson(data);
            Count = data.at("count");
        }
};

class CounterAssetCollection : public AssetTypeCollection<CounterAsset> {
    public:
        CounterAssetCollection() : AssetTypeCollection<CounterAsset>() {}

        int TotalCount = 0;

    protected:
        bool AddAsset(CounterAsset* asset) override {
            bool added = AssetTypeCollection::AddAsset(asset);
            if (added)
                TotalCount += asset->Count;
            return added;
        }
};

REGISTER_ASSET(CounterAsset);
REGISTER_ASSET_COLLECTION(CounterAssetCollection);

TEST_CASE("AssetManager.LoadFromJson Tests", AssetManagerTAG) {
    AssetManager::UnloadAllAssets();

    SECTION("Should Save Then Load Specfic Assets in Generic Type Collection") {
        CounterAsset* asset0 = new CounterAsset("Asset0");
        CounterAsset* asset1 = new CounterAsset("Asset1");
        asset1->Count = 1;
        CounterAsset* asset2 = new CounterAsset("Asset2");
        asset2->Count = 2;
        CounterAsset* asset3 = new CounterAsset("Asset3");
        asset3->Count = 3;
        
        AssetManager::AddAsset(asset0);
        AssetManager::AddAsset(asset1);
        AssetManager::AddAsset(asset2);
        AssetManager::AddAsset(asset3);

        nlohmann::json managerJson;
        AssetManager::SaveToJson(managerJson);
        AssetManager::UnloadAllAssets();
        AssetManager::LoadFromJson(managerJson);

        REQUIRE(AssetManager::HasAsset<CounterAsset>("Asset0"));
        REQUIRE(AssetManager::HasAsset<CounterAsset>("Asset1"));
        REQUIRE(AssetManager::HasAsset<CounterAsset>("Asset2"));
        REQUIRE(AssetManager::HasAsset<CounterAsset>("Asset3"));

        REQUIRE(AssetManager::GetAsset<CounterAsset>("Asset0")->Count == 0);
        REQUIRE(AssetManager::GetAsset<CounterAsset>("Asset1")->Count == 1);
        REQUIRE(AssetManager::GetAsset<CounterAsset>("Asset2")->Count == 2);
        REQUIRE(AssetManager::GetAsset<CounterAsset>("Asset3")->Count == 3);
    }

    SECTION("Should Save Then Load Specfic Assets in Specfic Type Collection") {
        AssetManager::AddAssetCollection<CounterAsset>(new CounterAssetCollection());
        CounterAsset* asset0 = new CounterAsset("Asset0");
        CounterAsset* asset1 = new CounterAsset("Asset1");
        asset1->Count = 1;
        CounterAsset* asset2 = new CounterAsset("Asset2");
        asset2->Count = 2;
        CounterAsset* asset3 = new CounterAsset("Asset3");
        asset3->Count = 3;
        
        AssetManager::AddAsset(asset0);
        AssetManager::AddAsset(asset1);
        AssetManager::AddAsset(asset2);
        AssetManager::AddAsset(asset3);

        nlohmann::json managerJson;
        AssetManager::SaveToJson(managerJson);
        REQUIRE(static_cast<const CounterAssetCollection*>(AssetManager::GetAssetCollection<CounterAsset>())->TotalCount == 6);
        AssetManager::UnloadAllAssets();
        REQUIRE_FALSE(AssetManager::GetAssetCollection<CounterAsset>());
        AssetManager::LoadFromJson(managerJson);

        REQUIRE(AssetManager::HasAsset<CounterAsset>("Asset0"));
        REQUIRE(AssetManager::HasAsset<CounterAsset>("Asset1"));
        REQUIRE(AssetManager::HasAsset<CounterAsset>("Asset2"));
        REQUIRE(AssetManager::HasAsset<CounterAsset>("Asset3"));

        REQUIRE(AssetManager::GetAsset<CounterAsset>("Asset0")->Count == 0);
        REQUIRE(AssetManager::GetAsset<CounterAsset>("Asset1")->Count == 1);
        REQUIRE(AssetManager::GetAsset<CounterAsset>("Asset2")->Count == 2);
        REQUIRE(AssetManager::GetAsset<CounterAsset>("Asset3")->Count == 3);

        REQUIRE(static_cast<const CounterAssetCollection*>(AssetManager::GetAssetCollection<CounterAsset>())->TotalCount == 6);
    }

    SECTION("Should Save Then Load Assets and Delete Previous Ones") {
        AssetManager::AddAssetCollection<CounterAsset>(new CounterAssetCollection());
        CounterAsset* asset0 = new CounterAsset("Asset0");
        
        AssetManager::AddAsset(asset0);

        nlohmann::json managerJson;
        AssetManager::SaveToJson(managerJson);

        AssetManager::UnloadAllAssets();
        REQUIRE_FALSE(AssetManager::HasAsset<CounterAsset>("Asset0"));
        REQUIRE_FALSE(AssetManager::HasAsset<CounterAsset>("Asset1"));
        AssetManager::AddAssetCollection<CounterAsset>(new CounterAssetCollection());
        CounterAsset* asset1 = new CounterAsset("Asset1");
        AssetManager::AddAsset(asset1);
        REQUIRE(AssetManager::HasAsset<CounterAsset>("Asset1"));

        AssetManager::LoadFromJson(managerJson);

        REQUIRE(AssetManager::HasAsset<CounterAsset>("Asset0"));
        REQUIRE_FALSE(AssetManager::HasAsset<CounterAsset>("Asset1"));
    }

    SECTION("Should Save Then Load Assets and Keep Previous Ones") {
        AssetManager::AddAssetCollection<CounterAsset>(new CounterAssetCollection());
        CounterAsset* asset0 = new CounterAsset("Asset0");
        
        AssetManager::AddAsset(asset0);

        nlohmann::json managerJson;
        AssetManager::SaveToJson(managerJson);

        AssetManager::UnloadAllAssets();
        REQUIRE_FALSE(AssetManager::HasAsset<CounterAsset>("Asset0"));
        REQUIRE_FALSE(AssetManager::HasAsset<CounterAsset>("Asset1"));
        AssetManager::AddAssetCollection<CounterAsset>(new CounterAssetCollection());
        CounterAsset* asset1 = new CounterAsset("Asset1");
        AssetManager::AddAsset(asset1);
        REQUIRE(AssetManager::HasAsset<CounterAsset>("Asset1"));

        AssetManager::LoadFromJson(managerJson, true);

        REQUIRE(AssetManager::HasAsset<CounterAsset>("Asset0"));
        REQUIRE(AssetManager::HasAsset<CounterAsset>("Asset1"));
    }
}