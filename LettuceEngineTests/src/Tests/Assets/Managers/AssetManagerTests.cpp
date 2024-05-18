#include "catch_amalgamated.hpp"
#include "Assets/Managers/AssetManager.h"

const char* AssetManagerTAG = "[AssetManager]";

class CustomAsset : public Asset {
    public:
        CustomAsset(std::string id) : Asset(id) {}
};

TEST_CASE("AssetManager.AddAsset Tests", AssetManagerTAG) {
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
        REQUIRE_THROWS_AS(AssetManager::AddAsset<Asset>(nullptr), std::invalid_argument);
    }
}

TEST_CASE("AssetManager.GetAsset Tests", AssetManagerTAG) {

}

TEST_CASE("AssetManager.RemoveAsset Tests", AssetManagerTAG) {

}

TEST_CASE("AssetManager.HasAsset Tests", AssetManagerTAG) {

}

TEST_CASE("AssetManager.AddAssetCollection Tests", AssetManagerTAG) {

}

TEST_CASE("AssetManager.GetAssetCollection Tests", AssetManagerTAG) {

}