#include "bridgeGamestate.hpp"
#include "bridgeCard.hpp"
#include "utils/bridgeUtils.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

namespace Bridge {

BridgeGamestate::BridgeGamestate(std::vector<std::vector<BridgeCard>> board,
                                 std::string declarerHand,
                                 std::string currentLeadHand,
                                 std::string trumpSuit, int contractLevel,
                                 int currentTrick, int declarerTricksMade)
    : d_board(board),
      d_declarerHand(convertDirStringToInt(declarerHand)),
      d_currentLeadHand(convertDirStringToInt(currentLeadHand)),
      d_currentHand(convertDirStringToInt(currentLeadHand)),
      d_trumpSuit(convertSuitStringToInt(trumpSuit)),
      d_declarerTricksRequired(getTricksRequired(contractLevel)),
      d_currentTrick(currentTrick),
      d_declarerTricksMade(declarerTricksMade),
      d_contractLevel(contractLevel) {
  updateCurrentValidMoves();
}

std::string BridgeGamestate::getWinner() {

  if (d_declarerTricksMade >= d_declarerTricksRequired) {
    return "Declarer";
  } else if ((TOTAL_TURNS + 1 - d_currentTrick) <
             (d_declarerTricksRequired - d_declarerTricksMade)) {
    return "Defence";
  } else {
    return "";
  }
  //possibly simulate till the end
  //just do simple check of if there is only one valid card to play - no reason to go through the last obvious move
}

BridgeExpected<std::string> BridgeGamestate::makeMoveMCTS(int validMoveNumber) {

  if (static_cast<size_t>(validMoveNumber) >= d_currentValidMoves.size()) {
    std::stringstream ss;
    ss << "Invalid MCTS move number given - there are only"
       << d_currentValidMoves.size() << " many moves";
    return tl::make_unexpected(ss.str());
  }
  BridgeCard cardPlayed = d_currentValidMoves[validMoveNumber];
  return makeMove(cardPlayed.getSuit(), cardPlayed.getRank());
}

BridgeExpected<std::string> BridgeGamestate::makeMove(const std::string suit,
                                                      const std::string rank) {

  if (getWinner() != "") {
    //probably cahnge this to return something else
    //basically jsut want a catch so you can't keep changing the gamestate once the gme is done
    //but this logic may end up in the controller
    //TODO: think about returning an unexpected state
    return getWinner();
  }

  BridgeCard move(suit, rank);

  if (auto isValid = moveIsValid(move); !isValid) {
    return tl::make_unexpected(isValid.error());
  }

  auto iterToErase = std::find(d_board[d_currentHand].begin(),
                               d_board[d_currentHand].end(), move);
  d_board[d_currentHand].erase(iterToErase);

  d_currentTrickRecord.push_back(move);

  if (d_currentTrickRecord.size() == 4) {

    ++d_currentTrick;

    const int trickWinnerDir = getTrickWinner();

    d_currentHand = trickWinnerDir;
    d_currentLeadHand = trickWinnerDir;

    //Declarer wins trick if they or the dummy wins, hence %2
    if (trickWinnerDir % 2 == d_declarerHand % 2) {
      ++d_declarerTricksMade;
    }
    d_currentTrickRecord.clear();

  } else {
    d_currentHand = (d_currentHand + 1) % 4;
  }

  updateCurrentValidMoves();

  return getWinner();
}

int BridgeGamestate::getTrickWinner() const {

  BridgeCard bestCard = d_currentTrickRecord[0];
  int bestCardDir = d_currentLeadHand;

  for (size_t i = 1; i != d_currentTrickRecord.size(); ++i) {

    auto currentCard = d_currentTrickRecord[i];

    if (currentCard.getSuit() == bestCard.getSuit() && currentCard > bestCard) {
      bestCard = currentCard;
      bestCardDir = (d_currentLeadHand + i) % 4;
    } else if (currentCard.getSuit() != bestCard.getSuit() &&
               currentCard.getSuit() == convertSuitIntToString(d_trumpSuit)) {
      bestCard = currentCard;
      bestCardDir = (d_currentLeadHand + i) % 4;
    }
  }

  return bestCardDir;
}

void BridgeGamestate::updateCurrentValidMoves() {

  auto currentCards = d_board[d_currentHand];

  d_currentValidMoves.clear();
  for (auto card : currentCards) {
    if (moveIsValid(card)) {
      //     std::cout << card << " is considered valid,";
      d_currentValidMoves.push_back(card);
    }
  }
  //  std::cout << "\n";
}

BridgeExpected<void> BridgeGamestate::moveIsValid(
    const BridgeCard& proposedMove) const {
  if (auto ret = currentHandHasCard(proposedMove); !ret) {
    return ret;
  }
  if (auto ret = moveFollowsSuitCorrectly(proposedMove); !ret) {
    return ret;
  }
  return {};
}

BridgeExpected<void> BridgeGamestate::currentHandHasCard(
    const BridgeCard& proposedMove) const {

  auto currentCards = d_board[d_currentHand];

  if (find(currentCards.begin(), currentCards.end(), proposedMove) ==
      currentCards.end()) {
    std::stringstream ss;
    ss << "Current hand " << convertDirIntToString(d_currentHand)
       << " does not have the card " << proposedMove;
    return tl::make_unexpected(ss.str());
  }

  return {};
}

BridgeExpected<void> BridgeGamestate::moveFollowsSuitCorrectly(
    const BridgeCard& proposedMove) const {

  //First card of a trick can be any suit
  if (d_currentTrickRecord.size() == 0) {
    return {};
  }

  auto currentCards = d_board[d_currentHand];

  const std::string leadSuit = d_currentTrickRecord[0].getSuit();

  if (proposedMove.getSuit() == leadSuit) {
    return {};
  }

  for (auto card : currentCards) {

    if (card.getSuit() == leadSuit) {
      return tl::make_unexpected("Move does not follow suit");
    }
  }

  return {};
}
bool operator==(const BridgeGamestate& lhs, const BridgeGamestate& rhs) {
  return lhs.d_board == rhs.d_board &&
         lhs.d_declarerHand == rhs.d_declarerHand &&
         lhs.d_currentLeadHand == rhs.d_currentLeadHand &&
         lhs.d_trumpSuit == rhs.d_trumpSuit &&
         lhs.d_declarerTricksRequired == rhs.d_declarerTricksRequired &&
         lhs.d_currentTrick == rhs.d_currentTrick &&
         lhs.d_declarerTricksMade == rhs.d_declarerTricksMade &&
         lhs.d_currentTrickRecord == rhs.d_currentTrickRecord;
}

const std::vector<std::vector<BridgeCard>>& BridgeGamestate::board() const {
  return d_board;
}

int BridgeGamestate::declarerHand() const {
  return d_declarerHand;
}
int BridgeGamestate::currentLeadHand() const {
  return d_currentLeadHand;
}
int BridgeGamestate::currentHand() const {
  return d_currentHand;
}

int BridgeGamestate::trumpSuit() const {
  return d_trumpSuit;
}
int BridgeGamestate::declarerTricksRequired() const {
  return d_declarerTricksRequired;
}

int BridgeGamestate::currentTrick() const {
  return d_currentTrick;
}
int BridgeGamestate::declarerTricksMade() const {
  return d_declarerTricksMade;
}

std::vector<BridgeCard> BridgeGamestate::currentTrickRecord() const {
  return d_currentTrickRecord;
}

int BridgeGamestate::contractLevel() const {
  return d_contractLevel;
}

}  // namespace Bridge
