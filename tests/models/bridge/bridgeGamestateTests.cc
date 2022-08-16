#include <gtest/gtest.h>

#include "models/bridge/bridgeGamestate.hpp"

#include <boost/json.hpp>

#include <fstream>
#include <sstream>

class BridgeGamestateTest : public ::testing::Test {


    protected:

        BridgeGamestateTest() {
            
            std::ifstream testJsonFile("testBoards.json");
            std::stringstream buffer;
            buffer << testJsonFile.rdbuf();

            std::string testJsonStr = buffer.str();

            testJson = boost::json::parse(testJsonStr).as_object(); 
        }


        boost::json::object testJson;


};


TEST_F(BridgeGamestateTest, ConstructorTests) {

    boost::json::object defaultJson = testJson["default_board_config"].as_object(); 

    ASSERT_NO_THROW(Bridge::BridgeGamestate defaultBG(defaultJson));

    Bridge::BridgeGamestate defaultBG(defaultJson);
    EXPECT_EQ(boost::json::serialize(defaultBG.getGamestateJson()), boost::json::serialize(defaultJson));

}



TEST_F(BridgeGamestateTest, MCTSInterfaceTests) {

    boost::json::object defaultJson = testJson["default_board_config"].as_object(); 

    Bridge::BridgeGamestate defaultBG(defaultJson);

    EXPECT_EQ(defaultBG.getValidMoveCnt(), 13);

    EXPECT_NO_THROW(defaultBG.makeMoveMCTS(3));

}



TEST_F(BridgeGamestateTest, MakeMoveTests) {

    boost::json::object defaultJson = testJson["default_board_config"].as_object(); 

    Bridge::BridgeGamestate defaultBG(defaultJson);

    EXPECT_THROW(defaultBG.makeMove("D","2"), std::invalid_argument);
    EXPECT_THROW(defaultBG.makeMove("C","2"), std::invalid_argument);


    EXPECT_NO_THROW(defaultBG.makeMove("S","A"));

    boost::json::object defaultJsonAfterMove = testJson["default_board_config_after_move"].as_object(); 

    EXPECT_EQ(boost::json::serialize(defaultJsonAfterMove), boost::json::serialize(defaultBG.getGamestateJson())); 

}



TEST_F(BridgeGamestateTest, FollowSuitTests) {

    boost::json::object defaultJson = testJson["default_board_config"].as_object(); 

    Bridge::BridgeGamestate defaultBG(defaultJson);


    ASSERT_NO_THROW(defaultBG.makeMove("C","K"));
    ASSERT_THROW(defaultBG.makeMove("D","5"), std::invalid_argument);
    ASSERT_NO_THROW(defaultBG.makeMove("C","A"));
    ASSERT_NO_THROW(defaultBG.makeMove("C","Q"));

}



TEST_F(BridgeGamestateTest, DeclarerLosesTrick) {

    boost::json::object defaultJson = testJson["default_board_config"].as_object(); 

    Bridge::BridgeGamestate defaultBG(defaultJson);


    ASSERT_NO_THROW(defaultBG.makeMove("C","K"));
    ASSERT_NO_THROW(defaultBG.makeMove("C","A"));
    ASSERT_NO_THROW(defaultBG.makeMove("C","Q"));
    ASSERT_NO_THROW(defaultBG.makeMove("C","J"));


    boost::json::object defaultJsonAfterLostTrick = testJson["default_board_config_after_lost_trick"].as_object(); 


    EXPECT_EQ(boost::json::serialize(defaultJsonAfterLostTrick), boost::json::serialize(defaultBG.getGamestateJson())); 

}


TEST_F(BridgeGamestateTest, DeclarerWinsTrick) {

    boost::json::object defaultJson = testJson["default_board_config"].as_object(); 

    Bridge::BridgeGamestate defaultBG(defaultJson);


    ASSERT_NO_THROW(defaultBG.makeMove("S","A"));
    ASSERT_NO_THROW(defaultBG.makeMove("C","A"));
    ASSERT_NO_THROW(defaultBG.makeMove("S","3"));
    ASSERT_NO_THROW(defaultBG.makeMove("S","J"));


    boost::json::object defaultJsonAfterWonTrick = testJson["default_board_config_after_won_trick"].as_object(); 


    EXPECT_EQ(boost::json::serialize(defaultJsonAfterWonTrick), boost::json::serialize(defaultBG.getGamestateJson())); 

}



TEST_F(BridgeGamestateTest, TrickWonByRuffing) {

    boost::json::object defaultJson = testJson["test_board_config"].as_object(); 

    Bridge::BridgeGamestate testBG(defaultJson);


    ASSERT_NO_THROW(testBG.makeMove("S","A"));
    ASSERT_NO_THROW(testBG.makeMove("D","5"));
    ASSERT_NO_THROW(testBG.makeMove("S","3"));
    ASSERT_NO_THROW(testBG.makeMove("S","J"));


    boost::json::object defaultJsonAfterRuff = testJson["test_board_config_after_ruff"].as_object(); 


    EXPECT_EQ(boost::json::serialize(defaultJsonAfterRuff), boost::json::serialize(testBG.getGamestateJson())); 

}



TEST_F(BridgeGamestateTest, DeclarerLostGameTest) {

    boost::json::object defaultJson = testJson["test_board_config"].as_object(); 

    Bridge::BridgeGamestate testBG(defaultJson);


    ASSERT_NO_THROW(testBG.makeMove("S","A"));
    ASSERT_NO_THROW(testBG.makeMove("D","5"));
    ASSERT_NO_THROW(testBG.makeMove("S","3"));
    ASSERT_NO_THROW(testBG.makeMove("S","J"));

    EXPECT_EQ( testBG.makeMove("S","4"), "Defence");

}



TEST_F(BridgeGamestateTest, DeclarerWonGameTest) {

    boost::json::object defaultJson = testJson["won_test_config"].as_object(); 

    Bridge::BridgeGamestate wonTestBG(defaultJson);


    ASSERT_NO_THROW(wonTestBG.makeMove("S","A"));
    ASSERT_NO_THROW(wonTestBG.makeMove("D","J"));
    ASSERT_NO_THROW(wonTestBG.makeMove("H","3"));
    ASSERT_NO_THROW(wonTestBG.makeMove("C","J"));

    EXPECT_EQ( wonTestBG.makeMove("S","4"), "Declarer");

}



