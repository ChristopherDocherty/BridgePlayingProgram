#include "bridgeGamestateLoader_new.hpp"
#include "models/bridge/bridgeGamestate.hpp"
#include "models/bridge/utils/bridgeExpected.hpp"
#include "utils/bridgeUtils.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <tl/expected.hpp>
#include <vector>

#include <nlohmann/json.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/transform.hpp>

using json = nlohmann::json;

namespace Bridge {

namespace {
const std::vector<std::string> HAND_JSON_KEYS = {"N_hand", "E_hand", "S_hand",
                                                 "W_hand"};

BridgeExpected<Board> getBoard(json boardData) {
  auto bridgeBoard =
      HAND_JSON_KEYS |
      ranges::views::transform([&boardData](const std::string &hand) {
        return boardData[hand] | ranges::views::transform([](const auto &card) {
                 std::string suit = card[0];
                 std::string rank = card[1];
                 return BridgeCard::create(suit, rank);
               });
      });

  if (ranges::any_of(bridgeBoard | ranges::views::join,
                     [](const auto &card) { return !card.has_value(); })) {
    return tl::make_unexpected("An invalid card was given in the board json");
  };

  return bridgeBoard | ranges::views::transform([](auto &&hand) {
           return hand |
                  ranges::views::transform([](auto &&card) { return *card; }) |
                  ranges::to<std::vector>;
         }) |
         ranges::to<std::vector>;
}

std::vector<std::pair<std::string, std::string>>
extractMoves(const json::array_t &movesJson) {
  return movesJson | ranges::views::transform([](const auto &move) {
           return std::pair{std::string{move[0]}, std::string{move[1]}};
         }) |
         ranges::to<std::vector>;
}

std::vector<CurrentTrickInfo>
extractTrickInfos(const json::array_t &trickInfosJson) {
  return trickInfosJson | ranges::views::transform([](const auto &trickInfo) {
           std::cout << "in here2";
           auto t =
               CurrentTrickInfo{.leadHand = convertDirStringToInt(std::string{
                                    trickInfo["current_lead_hand"]}),
                                .currHand = convertDirStringToInt(
                                    std::string{trickInfo["current_hand"]}),
                                .num = trickInfo["current_trick"],
                                .cardsPlayed = {}};

           std::cout << "in here3";
           return t;
         }) |
         ranges::to<std::vector>;
}

BridgeExpected<std::vector<Board>>
extractBoards(const json::array_t &boardsJson) {
  auto boards = boardsJson | ranges::views::transform([](const auto &board) {
                  return getBoard(board);
                });

  if (ranges ::any_of(boards, [](auto expBoard) { return !expBoard; })) {
    return tl::make_unexpected("failed");
  }

  return boards |
         ranges::views::transform([](auto expBoard) { return *expBoard; }) |
         ranges::to<std::vector>;
}

} // namespace

BridgeExpected<TestGame> loadTestGame(const std::string &configFilepath) {
  std::ifstream f(configFilepath);

  json data = json::parse(f);

  json contractInfo = data["contract_info"];
  json trickInfo = data["trick_info"];

  auto initialGamestate =
      getBoard(data["initial_board_state"]).map([&contractInfo, &trickInfo](auto &&board) {
        return BridgeGamestate{board,
                               contractInfo["declarer_dir"],
                               trickInfo["current_lead_hand"],
                               contractInfo["trump_suit"],
                               contractInfo["contract_level"],
                               trickInfo["current_trick"],
                               trickInfo["declarer_tricks_made"]};
      });

  if (!initialGamestate) {
    return tl::make_unexpected("Failed to get initial gamestate with errror:" +
                               initialGamestate.error());
  }

  auto testCases =
      extractBoards(data["subsequent_board_states"]).map([&data](auto boards) {
        return TestCases{.moves = extractMoves(data["moves"]),
                         .trickInfos =
                             extractTrickInfos(data["subsequent_trick_infos"]),
                         .boards = boards};
      });

  if (!testCases) {
    return tl::make_unexpected("Failed to get test Cases with errror:" +
                               testCases.error());
  }

  return TestGame{.initialGamestate = *initialGamestate,
                  .testCases = *testCases};
}

} // namespace Bridge
