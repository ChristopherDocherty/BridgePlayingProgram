#include "bridgeTerminalView.hpp"
#include <range/v3/view/zip.hpp>
#include <views/viewUtils.hpp>
#include "models/bridge/utils/bridgeUtils.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace Bridge {

namespace {
std::unordered_map<std::string, std::string> getSuitStringsForHand(
    const std::vector<BridgeCard>& hand) {
  std::vector<std::string> suits = viewUtils::getSuits();

  auto t = ranges::views::zip(suits, hand);
  (void)t;
  return {};
}
}  // namespace

void BridgeTerminalView::update(const BridgeGamestate& bg) {
  std::cout << getGamestateString(bg) << std::endl;
}

std::string BridgeTerminalView::getGamestateString(const BridgeGamestate& bg) {

  std::stringstream ss;

  ss << getContractAndTurnInfo(bg) << getNSHand(bg, "N") << "\n\n\n\n"
     << getNSHand(bg, "S");

  return ss.str();
}

std::string BridgeTerminalView::getContractAndTurnInfo(
    const BridgeGamestate& bg) {
  std::stringstream ss;

  ss << std::to_string(bg.contractLevel())
     << convertSuitIntToString(bg.trumpSuit()) << " by "
     << convertDirIntToString(bg.declarerHand()) << "\n"
     << convertDirIntToString(bg.currentLeadHand()) << " leads this trick\n";

  return ss.str();
}

std::string BridgeTerminalView::getNSHand(const BridgeGamestate& bg,
                                          const std::string& dir) {

  std::vector<std::vector<BridgeCard>> board = bg.board();
  const std::string hand = dir;

  const std::string westWhitespaceFill(westWhitespaceFillLength, ' ');

  std::stringstream ss;

  for (auto suit : viewUtils::getSuits()) {

    ss << westWhitespaceFill << suit << getCardsOfSuitString(board, hand, suit)
       << "\n";
  }

  return ss.str();
}

std::string BridgeTerminalView::getCardsOfSuitString(
    const std::vector<std::vector<BridgeCard>>& board, const std::string& dir,
    const std::string& suit) {

  int dirInt = convertDirStringToInt(dir);
  const std::vector<BridgeCard> hand = board[dirInt];

  const std::vector<std::string> ranks = extractAllRanksOfSuit(hand, suit);

  std::stringstream ss;

  ss << " ";

  for (auto rank : ranks) {
    ss << " " << rank;
  }

  return ss.str();
}

std::vector<std::string> BridgeTerminalView::extractAllRanksOfSuit(
    const std::vector<BridgeCard>& hand, const std::string& suit) {

  std::vector<std::string> ranks;

  for (auto card : hand) {
    if (card.getSuit() == suit) {
      ranks.push_back(card.getRank());
    }
  }

  return ranks;
}

}  // namespace Bridge
