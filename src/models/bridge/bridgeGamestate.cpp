#include "bridgeGamestate.hpp"

#include "bridgeCard.hpp"
#include "utils/bridgeUtils.hpp"

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

#include <fmt/format.h>

namespace Bridge {

std::string CurrentTrickInfo::leadSuit() const {
  return cardsPlayed[0].getSuit();
};

BridgeGamestate::BridgeGamestate(std::vector<std::vector<BridgeCard>> board,
                                 std::string declarerHand,
                                 std::string currentLeadHand,
                                 std::string trumpSuit, int contractLevel,
                                 int currentTrick, int declarerTricksMade)
    : d_board(board),
      // TODO: fix this vvv
      d_contract(*convertSuitStringToInt(trumpSuit),
                 getTricksRequired(contractLevel), contractLevel,
                 convertDirStringToInt(declarerHand)),
      d_currentTrick(convertDirStringToInt(currentLeadHand),
                     convertDirStringToInt(currentLeadHand), currentTrick, {}),
      d_declarerTricksMade(declarerTricksMade) {
  updateCurrentValidMoves();
}

std::string BridgeGamestate::getWinner() {

  if (d_declarerTricksMade >= d_contract.declarerTricksRequired) {
    return "Declarer";
  } else if ((TOTAL_TURNS + 1 - d_currentTrick.num) <
             (d_contract.declarerTricksRequired - d_declarerTricksMade)) {
    return "Defence";
  } else {
    return "";
  }
  // possibly simulate till the end
  // just do simple check of if there is only one valid card to play - no reason
  // to go through the last obvious move
}

BridgeExpected<std::string> BridgeGamestate::makeMoveMCTS(int validMoveNumber) {

  if (static_cast<size_t>(validMoveNumber) >= d_currentValidMoves.size()) {
    return tl::make_unexpected(fmt::format(
        "Invalid MCTS move number given - there are only {} many moves",
        d_currentValidMoves.size()));
  }
  BridgeCard cardPlayed = d_currentValidMoves[validMoveNumber];
  return makeMove(cardPlayed.getSuit(), cardPlayed.getRank());
}

BridgeExpected<std::string> BridgeGamestate::makeMove(const std::string suit,
                                                      const std::string rank) {
  // TODO: mabe needs to be a more distinct return type
  if (getWinner() != "") {
    return tl::make_unexpected(
        fmt::format("The game is over! The winner is: {}", getWinner()));
  }

  return BridgeCard::create(suit, rank)
      .and_then([this](BridgeCard &&move) -> BridgeExpected<BridgeCard> {
        if (auto isValid = moveIsValid(move); !isValid) {
          return tl::make_unexpected(isValid.error());
        }
        return move;
      })
      .map([this](BridgeCard &&move) {
        auto iterToErase =
            std::find(d_board[d_currentTrick.currHand].begin(),
                      d_board[d_currentTrick.currHand].end(), move);
        d_board[d_currentTrick.currHand].erase(iterToErase);

        d_currentTrick.cardsPlayed.push_back(move);

        if (d_currentTrick.cardsPlayed.size() == 4) {

          ++d_currentTrick.num;

          const int trickWinnerDir = getTrickWinner();

          d_currentTrick.currHand = trickWinnerDir;
          d_currentTrick.leadHand = trickWinnerDir;

          // Declarer wins trick if they or the dummy wins, hence %2
          if (trickWinnerDir % 2 == d_contract.declarer % 2) {
            ++d_declarerTricksMade;
          }
          d_currentTrick.cardsPlayed.clear();

        } else {
          d_currentTrick.currHand = (d_currentTrick.currHand + 1) % 4;
        }

        updateCurrentValidMoves();

        return getWinner();
      });
}

int BridgeGamestate::getTrickWinner() const {

  BridgeCard bestCard = d_currentTrick.cardsPlayed[0];
  int bestCardDir = d_currentTrick.leadHand;

  for (size_t i = 1; i != d_currentTrick.cardsPlayed.size(); ++i) {

    auto currentCard = d_currentTrick.cardsPlayed[i];

    if (currentCard.getSuit() == bestCard.getSuit() && currentCard > bestCard) {
      bestCard = currentCard;
      bestCardDir = (d_currentTrick.leadHand + i) % 4;
    } else if (currentCard.getSuit() != bestCard.getSuit() &&
               currentCard.getSuit() ==
                   convertSuitIntToString(d_contract.trumpSuit)) {
      bestCard = currentCard;
      bestCardDir = (d_currentTrick.leadHand + i) % 4;
    }
  }

  return bestCardDir;
}

void BridgeGamestate::updateCurrentValidMoves() {

  auto currentCards = d_board[d_currentTrick.currHand];

  d_currentValidMoves.clear();
  for (auto card : currentCards) {
    if (moveIsValid(card)) {
      //     std::cout << card << " is considered valid,";
      d_currentValidMoves.push_back(card);
    }
  }
  //  std::cout << "\n";
}

BridgeExpected<void>
BridgeGamestate::moveIsValid(const BridgeCard &proposedMove) const {
  if (auto ret = currentHandHasCard(proposedMove); !ret) {
    return ret;
  }
  if (auto ret = moveFollowsSuitCorrectly(proposedMove); !ret) {
    return ret;
  }
  return {};
}

BridgeExpected<void>
BridgeGamestate::currentHandHasCard(const BridgeCard &proposedMove) const {

  auto currentCards = d_board[d_currentTrick.currHand];

  if (find(currentCards.begin(), currentCards.end(), proposedMove) ==
      currentCards.end()) {
    std::stringstream ss;
    ss << "Current hand " << convertDirIntToString(d_currentTrick.currHand)
       << " does not have the card " << proposedMove;
    return tl::make_unexpected(ss.str());
  }

  return {};
}

BridgeExpected<void> BridgeGamestate::moveFollowsSuitCorrectly(
    const BridgeCard &proposedMove) const {

  bool isFirstMove = d_currentTrick.cardsPlayed.empty();
  // First card of a trick can be any suit
  if (isFirstMove) {
    return {};
  }

  // TODO: maybe get leadSuit once?
  bool cardIsSameSuitAsLead =
      proposedMove.getSuit() == d_currentTrick.leadSuit();
  if (cardIsSameSuitAsLead) {
    return {};
  }

  auto currentCards = d_board[d_currentTrick.currHand];
  for (auto card : currentCards) {
    if (card.getSuit() == d_currentTrick.leadSuit()) {
      return tl::make_unexpected("Move does not follow suit");
    }
  }

  return {};
}

bool operator==(const BridgeGamestate &lhs, const BridgeGamestate &rhs) {
  return lhs.d_board == rhs.d_board && lhs.d_contract == rhs.d_contract &&
         lhs.d_currentTrick == rhs.d_currentTrick &&
         lhs.d_declarerTricksMade == rhs.d_declarerTricksMade;
}

const std::vector<std::vector<BridgeCard>> &BridgeGamestate::board() const {
  return d_board;
}

int BridgeGamestate::declarerHand() const { return d_contract.declarer; }
int BridgeGamestate::currentLeadHand() const { return d_currentTrick.leadHand; }
int BridgeGamestate::currentHand() const { return d_currentTrick.currHand; }

int BridgeGamestate::trumpSuit() const { return d_contract.trumpSuit; }
int BridgeGamestate::declarerTricksRequired() const {
  return d_contract.declarerTricksRequired;
}

int BridgeGamestate::currentTrick() const { return d_currentTrick.num; }
int BridgeGamestate::declarerTricksMade() const { return d_declarerTricksMade; }

std::vector<BridgeCard> BridgeGamestate::currentTrickRecord() const {
  return d_currentTrick.cardsPlayed;
}

int BridgeGamestate::contractLevel() const { return d_contract.level; }

ContractInfo BridgeGamestate::contractInfo() const { return d_contract; }

CurrentTrickInfo BridgeGamestate::currentTrickInfo() const {
  return d_currentTrick;
}

} // namespace Bridge
