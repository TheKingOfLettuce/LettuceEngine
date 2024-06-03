#include "catch_amalgamated.hpp"
#include "Assets/Managers/AssetCollection.h"

const char* AssetCollectionTAG = "[AssetCollection]";

TEST_CASE("AssetCollection.AddAsset", AssetCollectionTAG) {
    SECTION("Should Add Assets") {
        AssetCollection collection = AssetCollection();
        REQUIRE(collection.AddAsset(new Asset("Asset1")));
        REQUIRE(collection.AddAsset(new Asset("Asset2")));
        REQUIRE(collection.AddAsset(new Asset("Asset3")));
    }

    SECTION("Should Add Only Unique Assets") {
        AssetCollection collection = AssetCollection();
        Asset* asset1 = new Asset("Asset1");
        Asset* asset2 = new Asset("Asset2");
        Asset* dupeAsset2 = new Asset("Asset2");

        REQUIRE(collection.AddAsset(asset1));
        REQUIRE(collection.AddAsset(asset2));
        REQUIRE_FALSE(collection.AddAsset(dupeAsset2));
        delete dupeAsset2;
    }

    SECTION("Should Throw") {
        AssetCollection collection = AssetCollection();
        REQUIRE_THROWS_AS(collection.AddAsset(nullptr), std::invalid_argument);
    }
}

TEST_CASE("AssetCollection.RemoveAsset", AssetCollectionTAG) {
    SECTION("Should Remove Assets with Pointer") {
        AssetCollection collection = AssetCollection();
        Asset* asset1 = new Asset("Asset1");
        Asset* asset2 = new Asset("Asset2");
        Asset* asset3 = new Asset("Asset3");
        collection.AddAsset(asset1);
        collection.AddAsset(asset2);
        collection.AddAsset(asset3);

        REQUIRE(collection.RemoveAsset(asset1));
        REQUIRE(collection.RemoveAsset(asset2));
        REQUIRE(collection.RemoveAsset(asset3));
        delete asset1;
        delete asset2;
        delete asset3;
    }

    SECTION("Should Remove Assets with ID") {
        AssetCollection collection = AssetCollection();
        Asset* asset1 = new Asset("Asset1");
        Asset* asset2 = new Asset("Asset2");
        Asset* asset3 = new Asset("Asset3");
        collection.AddAsset(asset1);
        collection.AddAsset(asset2);
        collection.AddAsset(asset3);

        REQUIRE(collection.RemoveAsset(asset1->GetAssetID()) == asset1);
        REQUIRE(collection.RemoveAsset(asset2->GetAssetID()) == asset2);
        REQUIRE(collection.RemoveAsset(asset3->GetAssetID()) == asset3);
        delete asset1;
        delete asset2;
        delete asset3;
    }

    SECTION("Should Not Remove If Asset Pointers Not Same") {
        AssetCollection collection = AssetCollection();
        Asset* asset1 = new Asset("Asset1");
        Asset* asset1dupe = new Asset("Asset1");
        collection.AddAsset(asset1);

        REQUIRE_FALSE(collection.RemoveAsset(asset1dupe));
        delete asset1dupe;
    }

    SECTION("Should Not Remove If Asset Not Added") {
        AssetCollection collection = AssetCollection();
        Asset* asset3 = new Asset("Asset3");
        collection.AddAsset(new Asset("Asset1"));
        collection.AddAsset(new Asset("Asset2"));

        REQUIRE_FALSE(collection.RemoveAsset(asset3));
        delete asset3;
    }

    SECTION("Should Not Remove If ID Not Added") {
        AssetCollection collection = AssetCollection();
        collection.AddAsset(new Asset("Asset1"));
        collection.AddAsset(new Asset("Asset2"));
        collection.AddAsset(new Asset("Asset3"));

        REQUIRE(collection.RemoveAsset("Asset42") == nullptr);
        REQUIRE(collection.RemoveAsset("HelloWorld") == nullptr);
        REQUIRE(collection.RemoveAsset("FOOL!") == nullptr);
    }

    SECTION("Should Throw If Null") {
        AssetCollection collection = AssetCollection();
        REQUIRE_THROWS_AS(collection.RemoveAsset(nullptr), std::invalid_argument);
    }
}

TEST_CASE("AssetCollection.HasAsset", AssetCollectionTAG) {
    SECTION("Should Find Asset With ID") {
        AssetCollection collection = AssetCollection();
        collection.AddAsset(new Asset("Asset1"));
        collection.AddAsset(new Asset("Asset2"));
        collection.AddAsset(new Asset("Asset3"));

        REQUIRE(collection.HasAsset("Asset1"));
        REQUIRE(collection.HasAsset("Asset2"));
        REQUIRE(collection.HasAsset("Asset3"));
    }

    SECTION("Should Find Asset With Object") {
        AssetCollection collection = AssetCollection();
        Asset* asset1 = new Asset("Asset1");
        Asset* asset2 = new Asset("Asset2");
        Asset* asset3 = new Asset("Asset3");
        collection.AddAsset(asset1);
        collection.AddAsset(asset2);
        collection.AddAsset(asset3);

        REQUIRE(collection.HasAsset(asset1));
        REQUIRE(collection.HasAsset(asset2));
        REQUIRE(collection.HasAsset(asset3));
    }

    SECTION("Should Not Find Asset Without ID Added") {
        AssetCollection collection = AssetCollection();
        collection.AddAsset(new Asset("Asset1"));
        collection.AddAsset(new Asset("Asset2"));
        collection.AddAsset(new Asset("Asset3"));

        REQUIRE_FALSE(collection.HasAsset("Asset42"));
        REQUIRE_FALSE(collection.HasAsset("HelloWorld"));
        REQUIRE_FALSE(collection.HasAsset("FOOL!"));
    }

    SECTION("Should Not Find Asset If Not Added") {
        AssetCollection collection = AssetCollection();
        Asset* asset3 = new Asset("Asset3");
        collection.AddAsset(new Asset("Asset1"));
        collection.AddAsset(new Asset("Asset2"));

        REQUIRE_FALSE(collection.HasAsset(asset3));
        delete asset3;
    }

    SECTION("Should Throw If Null") {
        AssetCollection collection = AssetCollection();
        REQUIRE_THROWS_AS(collection.HasAsset(nullptr), std::invalid_argument);
    }
}

TEST_CASE("AssetCollection.GetAsset", AssetCollectionTAG) {
    SECTION("Should Return Added Assets") {
        AssetCollection collection = AssetCollection();
        Asset* asset1 = new Asset("Asset1");
        Asset* asset2 = new Asset("Asset2");
        Asset* asset3 = new Asset("Asset3");
        collection.AddAsset(asset1);
        collection.AddAsset(asset2);
        collection.AddAsset(asset3);

        REQUIRE(collection.GetAsset("Asset1") == asset1);
        REQUIRE(collection.GetAsset("Asset2") == asset2);
        REQUIRE(collection.GetAsset("Asset3") == asset3);
    }

    SECTION("Should Not Return Not Added Assets") {
        AssetCollection collection = AssetCollection();
        collection.AddAsset(new Asset("Asset1"));
        collection.AddAsset(new Asset("Asset2"));
        collection.AddAsset(new Asset("Asset3"));

        REQUIRE(collection.GetAsset("Asset42") == nullptr);
        REQUIRE(collection.GetAsset("HelloWorld") == nullptr);
        REQUIRE(collection.GetAsset("FOOL!") == nullptr);
    }
}

TEST_CASE("AssetCollection.GetAllAssets", AssetCollectionTAG) {
    class Helper {
        public:
            static bool HasAsset(std::vector<Asset*> assets, Asset* asset) {
                for (Asset* containedAsset : assets) {
                    if (containedAsset == asset)
                        return true;
                }

                return false;
            }
    };
    
    SECTION("Should Get All Assets") {
        AssetCollection collection = AssetCollection();
        Asset* asset1 = new Asset("Asset1");
        Asset* asset2 = new Asset("Asset2");
        Asset* asset3 = new Asset("Asset3");
        collection.AddAsset(asset1);
        collection.AddAsset(asset2);
        collection.AddAsset(asset3);

        std::vector<Asset*> assets = collection.GetAllAssets();
        REQUIRE(Helper::HasAsset(assets, asset1));
        REQUIRE(Helper::HasAsset(assets, asset2));
        REQUIRE(Helper::HasAsset(assets, asset3));
    }
}

TEST_CASE("AssetCollection.SaveToJson", AssetCollectionTAG) {
    
}