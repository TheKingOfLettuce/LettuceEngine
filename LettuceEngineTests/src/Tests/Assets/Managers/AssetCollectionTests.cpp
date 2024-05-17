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

}

TEST_CASE("AssetCollection.HasAsset", AssetCollectionTAG) {

}

TEST_CASE("AssetCollection.GetAsset", AssetCollectionTAG) {

}

TEST_CASE("AssetCollection.GetAllAssets", AssetCollectionTAG) {

}