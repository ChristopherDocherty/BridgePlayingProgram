#include "bridgeTerminalView.hpp"

#include <views/viewUtils.hpp>
#include "models/bridge/bridgeCard.hpp"
#include "models/bridge/bridgeGamestate.hpp"
#include "models/bridge/utils/bridgeUtils.hpp"

#include "range/v3/iterator/operations.hpp"
#include "range/v3/view/cartesian_product.hpp"
#include "range/v3/view/for_each.hpp"
#include <range/v3/view/enumerate.hpp>
#include <range/v3/view/zip.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/chunk.hpp>

#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

namespace Bridge {

std::optional<BridgeCard> getCardForDir(
    const std::vector<BridgeCard>& currentTrickRecord, int leadDir, int dir) {

  size_t cardLocation = (4 - (leadDir - dir)) % 4;

  if (cardLocation >= currentTrickRecord.size()) {
    return {};
  }
  return currentTrickRecord[cardLocation];
}

std::string getNSPlayedCard(const std::optional<BridgeCard>& card) {
  if (card) {
    std::stringstream ss;
    ss << std::string(4, ' ') << card->getSuit() << " " << card->getRank()
       << std::string(5, ' ');
    return ss.str();
  } else {
    return std::string(12, ' ');
  }
}
std::string getEWPlayedCards(const std::optional<BridgeCard>& eCard,
                             const std::optional<BridgeCard>& wCard) {
  std::stringstream ss;

  auto addCard = [&ss](const std::optional<BridgeCard>& card) {
    if (card) {
      ss << card->getSuit() << " " << card->getRank() << " ";
    } else {
      ss << std::string(4, ' ');
    }
  };

  addCard(wCard);
  ss << std::string(4, ' ');
  addCard(eCard);

  return ss.str();
}

std::vector<std::string> getPlayedCards(const BridgeGamestate& bg) {
  std::vector<BridgeCard> currentTrickRecord = bg.currentTrickRecord();
  int leadDir = bg.currentLeadHand();
  std::vector<std::string> playedCards;

  auto nCard = getCardForDir(currentTrickRecord, leadDir, 0);
  playedCards.emplace_back(getNSPlayedCard(nCard));

  auto eCard = getCardForDir(currentTrickRecord, leadDir, 1);
  auto wCard = getCardForDir(currentTrickRecord, leadDir, 3);
  playedCards.emplace_back(getEWPlayedCards(eCard, wCard));

  auto sCard = getCardForDir(currentTrickRecord, leadDir, 2);
  playedCards.emplace_back(getNSPlayedCard(sCard));

  playedCards.emplace_back(std::string(12, ' '));

  return playedCards;
}

void BridgeTerminalView::update(const BridgeGamestate& bg) {
  std::cout << getGamestateString(bg) << std::endl;
}

std::string BridgeTerminalView::getGamestateString(const BridgeGamestate& bg) {

  auto handStr = getHandStrings(bg);

  std::stringstream ss;
  ss << getContractAndTurnInfo(bg) << getNSHand(handStr["N"]) << "\n"
     << getEWHand(handStr["E"], handStr["W"], bg) << "\n"
     << getNSHand(handStr["S"]);

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

std::string BridgeTerminalView::getNSHand(
    const std::vector<std::string>& handStrings) {
  const std::string westWhitespaceFill(westWhitespaceFillLength, ' ');

  std::stringstream ss;
  for (const auto& suitStr : handStrings) {
    ss << westWhitespaceFill << suitStr << "\n";
  }
  return ss.str();
}

std::string BridgeTerminalView::getEWHand(const std::vector<std::string>& eHand,
                                          const std::vector<std::string>& wHand,
                                          const BridgeGamestate& bg) {

  std::vector<BridgeCard> currPlayedCards = bg.currentTrickRecord();
  std::vector<std::string> playedCards = getPlayedCards(bg);

  std::stringstream ss;
  for (auto [i, cards] :
       ranges::views::enumerate(ranges::views::zip(eHand, wHand))) {
    const auto& [eCards, wCards] = cards;
    auto playedCard =
        i < playedCards.size() ? playedCards[i] : std::string(12, ' ');

    int westPad = westWhitespaceFillLength - wCards.size() + 1;

    ss << wCards << std::string(westPad, ' ');
    ss << playedCard;
    ss << eCards << "\n";
  }

  return ss.str();
}

std::vector<std::string> BridgeTerminalView::getCardsOfSuitString(
    const std::vector<std::vector<BridgeCard>>& board, const std::string& dir,
    const std::string& suit) {

  int dirInt = convertDirStringToInt(dir);
  const std::vector<BridgeCard> hand = board[dirInt];

  auto extractAllRanksOfSuit = [](auto hand, std::string suit) {
    return hand | ranges::views::filter([&suit](const BridgeCard& card) {
             return card.getSuit() == suit;
           }) |
           ranges::views::transform(&BridgeCard::getRank);
  };

  auto rankRows = extractAllRanksOfSuit(hand, suit) | ranges::views::chunk(4) |
                  ranges::views::transform(ranges::views::join(' ')) |
                  ranges::views::enumerate |
                  ranges::views::transform([&suit](auto s) {
                    auto [i, r] = s;
                    if (i == 0) {
                      return suit + "  " + ranges::to<std::string>(r);
                    }
                    return "   " + ranges::to<std::string>(r);
                  }) |
                  ranges::to<std::vector>;

  return rankRows.size() > 0 ? rankRows : std::vector<std::string>{suit};
}

std::unordered_map<std::string, std::vector<std::string>>
BridgeTerminalView::getHandStrings(BridgeGamestate bg) {

  auto suits = viewUtils::getSuits();
  std::vector<std::string> dirStrs = {"N", "E", "S", "W"};

  return ranges::views::zip(
             dirStrs,
             ranges::views::cartesian_product(dirStrs, suits) |
                 ranges::views::transform(
                     [&board = bg.board()](
                         std::tuple<std::string, std::string> dirAndSuit) {
                       auto [dir, suit] = dirAndSuit;
                       return getCardsOfSuitString(board, dir, suit);
                     }) |
                 ranges::views::chunk(4) |
                 ranges::views::transform([](auto chunk) {
                   return chunk | ranges::views::join | ranges::to<std::vector>;
                 })) |
         ranges::to<std::unordered_map>;
}

}  // namespace Bridge
