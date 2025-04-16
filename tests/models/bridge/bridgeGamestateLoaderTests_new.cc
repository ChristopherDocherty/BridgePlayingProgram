#include "models/bridge/bridgeCard.hpp"
#include "models/bridge/bridgeGamestateLoader_new.hpp"

#include "models/bridge/bridgeGamestate.hpp"

#include "matchers/boardMatcher.hpp"
#include "matchers/contractInfoMatcher.hpp"
#include "matchers/currentTrickInfoMatcher.hpp"
#include "models/bridge/utils/bridgeExpected.hpp"

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <pthread.h>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/to_container.hpp>
#include <range/v3/view/transform.hpp>
#include <tl/expected.hpp>

namespace Bridge {

namespace {

Board buildBoard(
    const std::vector<std::vector<std::pair<std::string, std::string>>>
        &preBoard) {
  auto expBoard =
      preBoard |
      ranges::views::transform(
          [](const auto &hand) -> BridgeExpected<std::vector<BridgeCard>> {
            auto expHand =
                hand | ranges::views::transform([](const auto &preCard) {
                  const auto &[suit, rank] = preCard;
                  return BridgeCard::create(suit, rank);
                });

            if (ranges::any_of(expHand,
                               [](const auto &expCard) { return !expCard; })) {
              return tl::make_unexpected("");
            }

            return expHand | ranges::views::transform([](auto &&expCard) {
                     return *expCard;
                   }) |
                   ranges::to<std::vector>;
          });

  if (ranges::any_of(expBoard, [](const auto &expHand) { return !expHand; })) {
    std::cout << "Failed";
  }

  return expBoard |
         ranges::views::transform([](auto &&expHand) { return *expHand; }) |
         ranges::to<std::vector>;
}

} // namespace

TEST_CASE("new loader works") {

  auto expTestGame = loadTestGame("test_1.json");

  REQUIRE(expTestGame);

  auto testGame = *expTestGame;

  GIVEN("A test file and an expected initial gamestate") {

    const ContractInfo EXPECTED_CONTRACT_INFO = {.trumpSuit = 4,
                                                 .declarerTricksRequired = 12,
                                                 .level = 6,
                                                 .declarer = 2};

    const CurrentTrickInfo EXPECTED_TRICK_INFO = {
        .leadHand = 2, .currHand = 2, .num = 1, .cardsPlayed = {}};

    const Board EXPECTED_BOARD = buildBoard({{{"S", "K"},
                                              {"S", "9"},
                                              {"S", "4"},
                                              {"S", "3"},
                                              {"H", "7"},
                                              {"H", "3"},
                                              {"D", "Q"},
                                              {"D", "8"},
                                              {"D", "7"},
                                              {"D", "2"},
                                              {"C", "Q"},
                                              {"C", "8"},
                                              {"C", "2"}},
                                             {{"S", "J"},
                                              {"S", "10"},
                                              {"S", "8"},
                                              {"H", "J"},
                                              {"H", "6"},
                                              {"D", "A"},
                                              {"D", "K"},
                                              {"D", "9"},
                                              {"D", "6"},
                                              {"D", "3"},
                                              {"C", "J"},
                                              {"C", "9"},
                                              {"C", "4"}},
                                             {{"S", "A"},
                                              {"S", "Q"},
                                              {"S", "7"},
                                              {"S", "6"},
                                              {"S", "5"},
                                              {"S", "2"},
                                              {"H", "A"},
                                              {"H", "K"},
                                              {"H", "9"},
                                              {"D", "4"},
                                              {"C", "K"},
                                              {"C", "6"},
                                              {"C", "5"}},
                                             {{"H", "Q"},
                                              {"H", "10"},
                                              {"H", "8"},
                                              {"H", "5"},
                                              {"H", "4"},
                                              {"H", "2"},
                                              {"D", "J"},
                                              {"D", "10"},
                                              {"D", "5"},
                                              {"C", "A"},
                                              {"C", "10"},
                                              {"C", "7"},
                                              {"C", "3"}}});

    REQUIRE_THAT(testGame.initialGamestate.contractInfo(),
                 MatchesContractInfo(EXPECTED_CONTRACT_INFO));

    REQUIRE_THAT(testGame.initialGamestate.currentTrickInfo(),
                 MatchesCurrentTrickInfo(EXPECTED_TRICK_INFO));

    REQUIRE_THAT(testGame.initialGamestate.board(),
                 MatchesBoard(EXPECTED_BOARD));
  }

  GIVEN("an expected moveset") {
    std::vector<std::pair<std::string, std::string>> EXPECTED_MOVES = {
        {"S", "A"}};
    REQUIRE(testGame.testCases.moves == EXPECTED_MOVES);
  }

  GIVEN("an expected subsequent trick info") {
    // TODO: support reading cardsplayed
    const CurrentTrickInfo EXPECTED_SUBSEQUENT_TRICK_INFO = {
        .leadHand = 2, .currHand = 3, .num = 1, .cardsPlayed = {}};
    REQUIRE(testGame.testCases.trickInfos.size() == 1);
    REQUIRE_THAT(testGame.testCases.trickInfos.front(),
                 MatchesCurrentTrickInfo(EXPECTED_SUBSEQUENT_TRICK_INFO));
  }

  GIVEN("an expected subsequent board") {
    const Board EXPECTED_SUBSEQUENT_BOARD = buildBoard({{{"S", "K"},
                                                         {"S", "9"},
                                                         {"S", "4"},
                                                         {"S", "3"},
                                                         {"H", "7"},
                                                         {"H", "3"},
                                                         {"D", "Q"},
                                                         {"D", "8"},
                                                         {"D", "7"},
                                                         {"D", "2"},
                                                         {"C", "Q"},
                                                         {"C", "8"},
                                                         {"C", "2"}},
                                                        {{"S", "J"},
                                                         {"S", "10"},
                                                         {"S", "8"},
                                                         {"H", "J"},
                                                         {"H", "6"},
                                                         {"D", "A"},
                                                         {"D", "K"},
                                                         {"D", "9"},
                                                         {"D", "6"},
                                                         {"D", "3"},
                                                         {"C", "J"},
                                                         {"C", "9"},
                                                         {"C", "4"}},
                                                        {{"S", "Q"},
                                                         {"S", "7"},
                                                         {"S", "6"},
                                                         {"S", "5"},
                                                         {"S", "2"},
                                                         {"H", "A"},
                                                         {"H", "K"},
                                                         {"H", "9"},
                                                         {"D", "4"},
                                                         {"C", "K"},
                                                         {"C", "6"},
                                                         {"C", "5"}},
                                                        {{"H", "Q"},
                                                         {"H", "10"},
                                                         {"H", "8"},
                                                         {"H", "5"},
                                                         {"H", "4"},
                                                         {"H", "2"},
                                                         {"D", "J"},
                                                         {"D", "10"},
                                                         {"D", "5"},
                                                         {"C", "A"},
                                                         {"C", "10"},
                                                         {"C", "7"},
                                                         {"C", "3"}}});

    REQUIRE(testGame.testCases.boards.size() == 1);
    REQUIRE_THAT(testGame.testCases.boards.front(),
                 MatchesBoard(EXPECTED_SUBSEQUENT_BOARD));
  }
}

} // namespace Bridge
