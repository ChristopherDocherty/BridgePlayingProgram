#include "models/bridge/bridgeGamestate.hpp"
#include "models/bridge/bridgeGamestateLoader.hpp"

#include <fstream>
#include <iostream>
#include <set>
#include <sstream>

#include <range/v3/range/conversion.hpp>
#include <range/v3/view/transform.hpp>

#include <catch2/catch_test_macros.hpp>

namespace Bridge {

namespace {

std::set<std::set<BridgeCard>> convertBoardToSet(
    std::vector<std::vector<BridgeCard>> board) {
  return board | ranges::views::transform([](std::vector<BridgeCard> hand) {
           return hand | ranges::to<std::set>;
         }) |
         ranges::to<std::set>;
}

}  // namespace

void compareBridgeGamestateMembers(const BridgeGamestate& lhs,
                                   const BridgeGamestate& rhs) {

  REQUIRE(convertBoardToSet(lhs.board()) == convertBoardToSet(rhs.board()));
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

  auto expDefaultBG =
      loadGamestate(TEST_BOARD_CONFIG_FILE, "default_board_config");
  REQUIRE(expDefaultBG);
  BridgeGamestate defaultBG = *expDefaultBG;

  REQUIRE(defaultBG.getValidMoveCnt() == 13);

  REQUIRE(defaultBG.makeMoveMCTS(3));
}

TEST_CASE("BridgeGamestateTest -- MakeMoveTests") {

  auto expDefaultBG =
      loadGamestate(TEST_BOARD_CONFIG_FILE, "default_board_config");
  REQUIRE(expDefaultBG);
  BridgeGamestate defaultBG = *expDefaultBG;

  REQUIRE_FALSE(defaultBG.makeMove("D", "2"));
  REQUIRE_FALSE(defaultBG.makeMove("C", "2"));

  REQUIRE(defaultBG.makeMove("S", "A"));

  auto expDefaultAfterMoveBG =
      loadGamestate(TEST_BOARD_CONFIG_FILE, "default_board_config_after_move");
  REQUIRE(expDefaultAfterMoveBG);
  BridgeGamestate defaultAfterMove = *expDefaultAfterMoveBG;

  compareBridgeGamestateMembers(defaultBG, defaultAfterMove);
}

TEST_CASE("BridgeGamestateTest -- FollowSuitTests") {

  auto expDefaultBG =
      loadGamestate(TEST_BOARD_CONFIG_FILE, "default_board_config");
  REQUIRE(expDefaultBG);
  BridgeGamestate defaultBG = *expDefaultBG;

  REQUIRE(defaultBG.makeMove("C", "K"));
  REQUIRE_FALSE(defaultBG.makeMove("D", "5"));
  REQUIRE(defaultBG.makeMove("C", "A"));
  REQUIRE(defaultBG.makeMove("C", "Q"));
}

TEST_CASE("BridgeGamestateTest -- DeclarerLosesTrick") {

  auto expDefaultBG =
      loadGamestate(TEST_BOARD_CONFIG_FILE, "default_board_config");
  REQUIRE(expDefaultBG);
  BridgeGamestate defaultBG = *expDefaultBG;

  REQUIRE(defaultBG.makeMove("C", "K"));
  REQUIRE(defaultBG.makeMove("C", "A"));
  REQUIRE(defaultBG.makeMove("C", "Q"));
  REQUIRE(defaultBG.makeMove("C", "J"));

  auto expDefaultAfterLostTrick = loadGamestate(
      TEST_BOARD_CONFIG_FILE, "default_board_config_after_lost_trick");
  REQUIRE(expDefaultBG);
  BridgeGamestate defaultAfterLostTrick = *expDefaultAfterLostTrick;

  compareBridgeGamestateMembers(defaultBG, defaultAfterLostTrick);
}

TEST_CASE("BridgeGamestateTest -- DeclarerWinsTrick") {

  auto expDefaultBG =
      loadGamestate(TEST_BOARD_CONFIG_FILE, "default_board_config");
  REQUIRE(expDefaultBG);
  BridgeGamestate defaultBG = *expDefaultBG;

  REQUIRE(defaultBG.makeMove("S", "A"));
  REQUIRE(defaultBG.makeMove("C", "A"));
  REQUIRE(defaultBG.makeMove("S", "3"));
  REQUIRE(defaultBG.makeMove("S", "J"));

  auto expDefaultAfterWonTrick = loadGamestate(
      TEST_BOARD_CONFIG_FILE, "default_board_config_after_won_trick");
  REQUIRE(expDefaultBG);
  BridgeGamestate defaultAfterWonTrick = *expDefaultAfterWonTrick;

  compareBridgeGamestateMembers(defaultBG, defaultAfterWonTrick);
}

TEST_CASE("BridgeGamestateTest -- TrickWonByRuffing") {
  auto expTestBG = loadGamestate(TEST_BOARD_CONFIG_FILE, "test_board_config");
  REQUIRE(expTestBG);
  BridgeGamestate testBG = *expTestBG;

  REQUIRE(testBG.makeMove("S", "A"));
  REQUIRE(testBG.makeMove("D", "5"));
  REQUIRE(testBG.makeMove("S", "3"));
  REQUIRE(testBG.makeMove("S", "J"));

  auto expDefaultJsonAfterRuff =
      loadGamestate(TEST_BOARD_CONFIG_FILE, "test_board_config_after_ruff");
  REQUIRE(expDefaultJsonAfterRuff);
  BridgeGamestate defaultJsonAfterRuff = *expDefaultJsonAfterRuff;

  compareBridgeGamestateMembers(testBG, defaultJsonAfterRuff);
}

TEST_CASE("BridgeGamestateTest -- DeclarerLostGameTest") {

  auto expTestBG = loadGamestate(TEST_BOARD_CONFIG_FILE, "test_board_config");
  REQUIRE(expTestBG);
  BridgeGamestate testBG = *expTestBG;

  REQUIRE(testBG.makeMove("S", "A"));
  REQUIRE(testBG.makeMove("D", "5"));
  REQUIRE(testBG.makeMove("S", "3"));
  auto finalMove = testBG.makeMove("S", "J");
  REQUIRE(finalMove);
  REQUIRE(*finalMove == "Defence");

  auto invalidMove = testBG.makeMove("S", "4");
  REQUIRE_FALSE(invalidMove);
  REQUIRE(invalidMove.error() == "The game is over! The winner is: Defence");
}

TEST_CASE("BridgeGamestateTest -- DeclarerWonGameTest") {

  auto expWonTestBG = loadGamestate(TEST_BOARD_CONFIG_FILE, "won_test_config");
  REQUIRE(expWonTestBG);
  BridgeGamestate wonTestBG = *expWonTestBG;

  REQUIRE(wonTestBG.makeMove("S", "A"));
  REQUIRE(wonTestBG.makeMove("D", "J"));
  REQUIRE(wonTestBG.makeMove("H", "3"));
  auto finalMove = wonTestBG.makeMove("C", "J");
  REQUIRE(finalMove);
  REQUIRE(*finalMove == "Declarer");

  auto invalidMove = wonTestBG.makeMove("S", "4");
  REQUIRE_FALSE(invalidMove);
  REQUIRE(invalidMove.error() == "The game is over! The winner is: Declarer");
}

TEST_CASE("BridgeGamestateTest -- GameToCompletion") {

  auto expWonTestBG =
      loadGamestate(TEST_BOARD_CONFIG_FILE, "default_board_config");
  REQUIRE(expWonTestBG);
  BridgeGamestate wonTestBG = *expWonTestBG;

  REQUIRE(wonTestBG.makeMove("S", "A"));
  REQUIRE(wonTestBG.makeMove("C", "A"));
  REQUIRE(wonTestBG.makeMove("S", "K"));
  REQUIRE(wonTestBG.makeMove("S", "J"));

  REQUIRE(wonTestBG.makeMove("S", "Q"));
  REQUIRE(wonTestBG.makeMove("H", "Q"));
  REQUIRE(wonTestBG.makeMove("S", "9"));
  REQUIRE(wonTestBG.makeMove("S", "10"));

  REQUIRE(wonTestBG.makeMove("S", "7"));
  REQUIRE(wonTestBG.makeMove("H", "10"));
  REQUIRE(wonTestBG.makeMove("S", "4"));
  REQUIRE(wonTestBG.makeMove("S", "8"));

  //TODO: finish
}

}  // namespace Bridge
