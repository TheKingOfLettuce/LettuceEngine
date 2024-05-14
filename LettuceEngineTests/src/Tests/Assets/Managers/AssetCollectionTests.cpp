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

    SECTION("Should Throw") { }
}

TEST_CASE("AssetCollection.RemoveAsset", AssetCollectionTAG) {

}

TEST_CASE("AssetCollection.HasAsset", AssetCollectionTAG) {

}

TEST_CASE("AssetCollection.GetAsset", AssetCollectionTAG) {

}

TEST_CASE("AssetCollection.GetAllAssets", AssetCollectionTAG) {

}