#include "models/bridge/bridgeGamestate.hpp"
#include "models/bridge/bridgeGamestateLoader.hpp"

#include <set>

#include <range/v3/range/conversion.hpp>
#include <range/v3/view/transform.hpp>

#include <catch2/catch_test_macros.hpp>

namespace Bridge {

namespace {

std::set<std::set<BridgeCard>>
convertBoardToSet(std::vector<std::vector<BridgeCard>> board) {
  return board | ranges::views::transform([](std::vector<BridgeCard> hand) {
           return hand | ranges::to<std::set>;
         }) |
         ranges::to<std::set>;
}

} // namespace

void compareBridgeGamestateMembers(const BridgeGamestate &lhs,
                                   const BridgeGamestate &rhs) {

  REQUIRE(convertBoardToSet(lhs.board()) == convertBoardToSet(rhs.board()));
  REQUIRE(lhs.declarerHand() == rhs.declarerHand());
  REQUIRE(lhs.currentLeadHand() == rhs.currentLeadHand());
  REQUIRE(lhs.trumpSuit() == rhs.trumpSuit());
  REQUIRE(lhs.declarerTricksRequired() == rhs.declarerTricksRequired());
  REQUIRE(lhs.currentTrick() == rhs.currentTrick());
  REQUIRE(lhs.declarerTricksMade() == rhs.declarerTricksMade());
  // REQUIRE(lhs.currentTrickRecord() == rhs.currentTrickRecord());
}

const std::string TEST_BOARD_CONFIG_FILE = "testBoards.json";

TEST_CASE("BridgeGamestateTest -- MCTSInterfaceTests") {

  auto expDefaultBG =
      loadGamestate(TEST_BOARD_CONFIG_FILE, "default_board_config");
  REQUIRE(expDefaultBG);
  BridgeGamestate defaultBG = *expDefaultBG;


}


} // namespace Bridge
