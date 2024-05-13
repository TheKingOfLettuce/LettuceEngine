#include "catch_amalgamated.hpp"
#include "Assets/Managers/AssetCollection.h"

const char* AssetCollectionTAG = "[AssetCollection]";

class TestAsset : public Asset {
    public:
        TestAsset(std::string id) : Asset(id) {}
        ~TestAsset() {}
};

TEST_CASE("AssetCollection.AddAsset", AssetCollectionTAG) {
    SECTION("Should Add Assets") {

    }

    SECTION("Should Throw")
}

TEST_CASE("AssetCollection.RemoveAsset", AssetCollectionTAG) {

}

TEST_CASE("AssetCollection.HasAsset", AssetCollectionTAG) {

}

TEST_CASE("AssetCollection.GetAsset", AssetCollectionTAG) {

}

TEST_CASE("AssetCollection.GetAllAssets", AssetCollectionTAG) {

}