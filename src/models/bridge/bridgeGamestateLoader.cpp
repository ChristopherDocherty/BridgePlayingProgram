#include "bridgeGamestateLoader.hpp"
#include "models/bridge/bridgeGamestate.hpp"
#include "models/bridge/utils/bridgeExpected.hpp"

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
}

BridgeExpected<BridgeGamestate> loadGamestate(std::string configFilepath,
                                              std::string key) {

  std::ifstream f(configFilepath);

  json data = json::parse(f)[key];

  return getBoard(data["board"]).map([&data](auto&& board) {
    return BridgeGamestate{board,
                           data["declarer_dir"],
                           data["current_lead_hand"],
                           data["trump_suit"],
                           data["contract_level"],
                           data["current_trick"],
                           data["declarer_tricks_made"]};
  });
}

BridgeExpected<std::vector<std::vector<BridgeCard>>> getBoard(json boardData) {
  auto bridgeBoard =
      HAND_JSON_KEYS |
      ranges::views::transform([&boardData](const std::string& hand) {
        return boardData[hand] | ranges::views::transform([](const auto& card) {
                 std::string suit = card[0];
                 std::string rank = card[1];
                 return BridgeCard::create(suit, rank);
               });
      });

  if (ranges::any_of(bridgeBoard | ranges::views::join,
                     [](const auto& card) { return !card.has_value(); })) {
    return tl::make_unexpected("An invalid card was given in the board json");
  };

  return bridgeBoard | ranges::views::transform([](auto&& hand) {
           return hand |
                  ranges::views::transform([](auto&& card) { return *card; }) |
                  ranges::to<std::vector>;
         }) |
         ranges::to<std::vector>;
}
}  // namespace Bridge
