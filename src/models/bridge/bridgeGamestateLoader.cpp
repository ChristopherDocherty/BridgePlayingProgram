#include "bridgeGamestateLoader.hpp"
#include "models/bridge/bridgeGamestate.hpp"

#include <fstream>
#include <string>
#include <vector>

#include <includes/json.hpp>

using json = nlohmann::json;

namespace Bridge {

BridgeGamestate loadGamestate(std::string configFilepath, std::string key) {

  std::ifstream f(configFilepath);

  json data = json::parse(f)[key];

  return BridgeGamestate{getBoard(data["board"]),     data["declarer_dir"],
                         data["current_lead_hand"],   data["trump_suit"],
                         data["contract_level"],      data["current_trick"],
                         data["declarer_tricks_made"]};
};

std::vector<std::vector<BridgeCard>> getBoard(json boardData) {

  std::vector<std::vector<BridgeCard>> board;

  for (json::iterator boardIter = boardData.begin();
       boardIter != boardData.end(); ++boardIter) {
    std::vector<BridgeCard>& hand = board.emplace_back();
    for (json::iterator it = boardIter->begin(); it != boardIter->end(); ++it) {
      std::string suit = (*it)[0];
      std::string rank = (*it)[1];
      hand.emplace_back(BridgeCard{suit, rank});
    }
  }
  return board;
};
}  // namespace Bridge
