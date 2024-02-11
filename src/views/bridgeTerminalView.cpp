#include "bridgeTerminalView.hpp"
#include "viewUtils.hpp"

#include <boost/json.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace Bridge {

void BridgeTerminalView::update(const std::string& gamestate) const {

  boost::json::object gamestateObject =
      (boost::json::parse(gamestate)).as_object();

  printToScreen(gamestateObject);
}

void BridgeTerminalView::printToScreen(
    boost::json::object gamestateObject) const {

  std::stringstream ss;

  ss << getContractAndTurnInfo(gamestateObject);
  ss << getNSHand(gamestateObject, "N");
  ss << getNSHand(gamestateObject, "S");

  std::cout << ss.str();
}

std::string BridgeTerminalView::getContractAndTurnInfo(
    boost::json::object gamestate) const {

  std::stringstream ss;

  ss << viewUtils::convertJsonToStr(gamestate["contract_level"]);
  ss << viewUtils::convertJsonToStr(gamestate["trumpSuit"]);
  ss << "by" << viewUtils::convertJsonToStr(gamestate["declarer_dir"]);

  ss << "\n"
     << viewUtils::convertJsonToStr(gamestate["current_lead_hand"])
     << " leads this trick\n";

  return ss.str();
}

std::string BridgeTerminalView::getNSHand(boost::json::object gamestate,
                                          const std::string& dir) const {

  boost::json::object board = gamestate["board"].as_object();
  const std::string hand = dir + "_hand";

  const std::string westWhitespaceFill(westWhitespaceFillLength, ' ');

  std::stringstream ss;

  for (auto suit : viewUtils::getSuits()) {

    ss << westWhitespaceFill << suit << getCardsOfSuitString(board, hand, suit)
       << "\n";
  }

  return ss.str();
}

std::string BridgeTerminalView::getCardsOfSuitString(
    boost::json::object board, const std::string& dir,
    const std::string& suit) const {

  boost::json::array hand = board[dir].as_array();

  const std::vector<std::string> ranks = extractAllRanksOfSuit(hand, suit);

  std::stringstream ss;

  ss << suit << " ";

  for (auto rank : ranks) {
    ss << " " << rank;
  }

  return ss.str();
}

std::vector<std::string> BridgeTerminalView::extractAllRanksOfSuit(
    boost::json::array& hand, const std::string& suit) const {

  std::vector<std::string> ranks;

  for (auto card : hand) {

    boost::json::array cardArr = card.as_array();

    if (viewUtils::convertJsonToStr(cardArr[0]) == suit) {
      ranks.push_back(viewUtils::convertJsonToStr(cardArr[1]));
    }
  }

  return ranks;
}

}  // namespace Bridge
