#include <gtest/gtest.h>

#include "models/bridge/bridgeGamestate.hpp"

#include <boost/json.hpp>

#include <fstream>
#include <sstream>

class JsonTest : public ::testing::Test {


    protected:

        JsonTest() {
            
            std::ifstream testJsonFile("testBoards.json");
            std::stringstream buffer;
            buffer << testJsonFile.rdbuf();

            std::string testJsonStr = buffer.str();

            testJson = boost::json::parse(testJsonStr).as_object(); 
        }


        boost::json::object testJson;


};


TEST_F(JsonTest, ConstructorTests) {

    boost::json::object defaultJson = testJson["default_board_config"].as_object(); 

    ASSERT_NO_THROW(Bridge::BridgeGamestate defaultBG(defaultJson));

    Bridge::BridgeGamestate defaultBG(defaultJson);
    EXPECT_EQ(boost::json::serialize(defaultBG.getGamestateJson()), boost::json::serialize(defaultJson));

}







