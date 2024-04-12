#include "models/bridge/bridgeGamestate.hpp"
#include "models/bridge/bridgeGamestateLoader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include <catch2/catch_test_macros.hpp>

namespace Bridge {

void compareBridgeGamestateMembers(const BridgeGamestate& lhs,
                                   const BridgeGamestate& rhs) {

  REQUIRE(lhs.board() == rhs.board());
  REQUIRE(lhs.declarerHand() == rhs.declarerHand());
  REQUIRE(lhs.currentLeadHand() == rhs.currentLeadHand());
  REQUIRE(lhs.trumpSuit() == rhs.trumpSuit());
  REQUIRE(lhs.declarerTricksRequired() == rhs.declarerTricksRequired());
  REQUIRE(lhs.currentTrick() == rhs.currentTrick());
  REQUIRE(lhs.declarerTricksMade() == rhs.declarerTricksMade());
  //REQUIRE(lhs.currentTrickRecord() == rhs.currentTrickRecord());
}

const std::string TEST_BOARD_CONFIG_FILE = "testBoards.json";

TEST_CASE("BridgeGamestateTest -- MCTSInterfaceTests") {

  BridgeGamestate defaultBG =
      loadGamestate(TEST_BOARD_CONFIG_FILE, "default_board_config");

  REQUIRE(defaultBG.getValidMoveCnt() == 13);

  REQUIRE_NOTHROW(defaultBG.makeMoveMCTS(3));
}

TEST_CASE("BridgeGamestateTest -- MakeMoveTests") {

  BridgeGamestate defaultBG =
      loadGamestate(TEST_BOARD_CONFIG_FILE, "default_board_config");

  REQUIRE_THROWS_AS(defaultBG.makeMove("D", "2"), std::invalid_argument);
  REQUIRE_THROWS_AS(defaultBG.makeMove("C", "2"), std::invalid_argument);

  REQUIRE_NOTHROW(defaultBG.makeMove("S", "A"));

  BridgeGamestate defaultAfterMove =
      loadGamestate(TEST_BOARD_CONFIG_FILE, "default_board_config_after_move");

  compareBridgeGamestateMembers(defaultBG, defaultAfterMove);
}

TEST_CASE("BridgeGamestateTest -- FollowSuitTests") {

  BridgeGamestate defaultBG =
      loadGamestate(TEST_BOARD_CONFIG_FILE, "default_board_config");

  REQUIRE_NOTHROW(defaultBG.makeMove("C", "K"));
  REQUIRE_THROWS_AS(defaultBG.makeMove("D", "5"), std::invalid_argument);
  REQUIRE_NOTHROW(defaultBG.makeMove("C", "A"));
  REQUIRE_NOTHROW(defaultBG.makeMove("C", "Q"));
}

TEST_CASE("BridgeGamestateTest -- DeclarerLosesTrick") {

  BridgeGamestate defaultBG =
      loadGamestate(TEST_BOARD_CONFIG_FILE, "default_board_config");

  REQUIRE_NOTHROW(defaultBG.makeMove("C", "K"));
  REQUIRE_NOTHROW(defaultBG.makeMove("C", "A"));
  REQUIRE_NOTHROW(defaultBG.makeMove("C", "Q"));
  REQUIRE_NOTHROW(defaultBG.makeMove("C", "J"));

  BridgeGamestate defaultAfterLostTrick = loadGamestate(
      TEST_BOARD_CONFIG_FILE, "default_board_config_after_lost_trick");

  compareBridgeGamestateMembers(defaultBG, defaultAfterLostTrick);
}

TEST_CASE("BridgeGamestateTest -- DeclarerWinsTrick") {

  BridgeGamestate defaultBG =
      loadGamestate(TEST_BOARD_CONFIG_FILE, "default_board_config");

  REQUIRE_NOTHROW(defaultBG.makeMove("S", "A"));
  REQUIRE_NOTHROW(defaultBG.makeMove("C", "A"));
  REQUIRE_NOTHROW(defaultBG.makeMove("S", "3"));
  REQUIRE_NOTHROW(defaultBG.makeMove("S", "J"));

  BridgeGamestate defaultAfterWonTrick = loadGamestate(
      TEST_BOARD_CONFIG_FILE, "default_board_config_after_won_trick");

  compareBridgeGamestateMembers(defaultBG, defaultAfterWonTrick);
}

TEST_CASE("BridgeGamestateTest -- TrickWonByRuffing") {

  BridgeGamestate testBG =
      loadGamestate(TEST_BOARD_CONFIG_FILE, "test_board_config");

  REQUIRE_NOTHROW(testBG.makeMove("S", "A"));
  REQUIRE_NOTHROW(testBG.makeMove("D", "5"));
  REQUIRE_NOTHROW(testBG.makeMove("S", "3"));
  REQUIRE_NOTHROW(testBG.makeMove("S", "J"));

  BridgeGamestate defaultJsonAfterRuff =
      loadGamestate(TEST_BOARD_CONFIG_FILE, "test_board_config_after_ruff");

  compareBridgeGamestateMembers(testBG, defaultJsonAfterRuff);
}

TEST_CASE("BridgeGamestateTest -- DeclarerLostGameTest") {

  BridgeGamestate testBG =
      loadGamestate(TEST_BOARD_CONFIG_FILE, "test_board_config");

  REQUIRE_NOTHROW(testBG.makeMove("S", "A"));
  REQUIRE_NOTHROW(testBG.makeMove("D", "5"));
  REQUIRE_NOTHROW(testBG.makeMove("S", "3"));
  REQUIRE_NOTHROW(testBG.makeMove("S", "J"));

  REQUIRE(testBG.makeMove("S", "4") == "Defence");
}

TEST_CASE("BridgeGamestateTest -- DeclarerWonGameTest") {

  BridgeGamestate wonTestBG =
      loadGamestate(TEST_BOARD_CONFIG_FILE, "won_test_config");

  REQUIRE_NOTHROW(wonTestBG.makeMove("S", "A"));
  REQUIRE_NOTHROW(wonTestBG.makeMove("D", "J"));
  REQUIRE_NOTHROW(wonTestBG.makeMove("H", "3"));
  REQUIRE_NOTHROW(wonTestBG.makeMove("C", "J"));

  REQUIRE(wonTestBG.makeMove("S", "4") == "Declarer");
}


TEST_CASE("BridgeGamestateTest -- GameToCompletion") {

  BridgeGamestate wonTestBG =
      loadGamestate(TEST_BOARD_CONFIG_FILE, "default_board_config");

  REQUIRE_NOTHROW(wonTestBG.makeMove("S", "A"));
  REQUIRE_NOTHROW(wonTestBG.makeMove("C", "A"));
  REQUIRE_NOTHROW(wonTestBG.makeMove("S", "K"));
  REQUIRE_NOTHROW(wonTestBG.makeMove("S", "J"));

  REQUIRE_NOTHROW(wonTestBG.makeMove("S", "Q"));
  REQUIRE_NOTHROW(wonTestBG.makeMove("H", "Q"));
  REQUIRE_NOTHROW(wonTestBG.makeMove("S", "9"));
  REQUIRE_NOTHROW(wonTestBG.makeMove("S", "10"));

  REQUIRE_NOTHROW(wonTestBG.makeMove("S", "7"));
  REQUIRE_NOTHROW(wonTestBG.makeMove("H", "10"));
  REQUIRE_NOTHROW(wonTestBG.makeMove("S", "4"));
  REQUIRE_NOTHROW(wonTestBG.makeMove("S", "8"));
  
  REQUIRE_NOTHROW(wonTestBG.makeMove("S", "6"));
  REQUIRE_NOTHROW(wonTestBG.makeMove("D", "J"));
  REQUIRE_NOTHROW(wonTestBG.makeMove("S", "3"));
  REQUIRE_NOTHROW(wonTestBG.makeMove("C", "J"));

//  REQUIRE(wonTestBG.makeMove("S", "4") == "Declarer");
}

}  // namespace Bridge
