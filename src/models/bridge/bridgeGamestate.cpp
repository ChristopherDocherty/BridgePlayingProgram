#include "bridgeGamestate.hpp"
#include "bridgeCard.hpp"
#include "utils/bridgeUtils.hpp"

#include <algorithm>
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
      d_declarerTricksMade(declarerTricksMade) {
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

std::string BridgeGamestate::makeMoveMCTS(int validMoveNumber) {
  BridgeCard cardPlayed = d_currentValidMoves[validMoveNumber];
  return makeMove(cardPlayed.getSuit(), cardPlayed.getRank());
}

std::string BridgeGamestate::makeMove(const std::string suit,
                                      const std::string rank) {

  if (getWinner() != "") {
    //probably cahnge this to return something else
    //basically jsut want a catch so you can't keep changing the gamestate once the gme is done
    //but this logic may end up in the controller
    return getWinner();
  }

  BridgeCard move(suit, rank);

  if (!moveIsValid(move)) {
    throw std::invalid_argument(
        "nope");  //boost::json::serialize(getGamestateJson())); //"This is an invalid move");
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

  d_currentValidMoves.clear();

  auto currentCards = d_board[d_currentHand];

  for (auto card : currentCards) {
    if (moveIsValid(card)) {
      d_currentValidMoves.push_back(card);
    }
  }
}

bool BridgeGamestate::moveIsValid(const BridgeCard& proposedMove) const {

  if (currentHandDoesNotHaveCard(proposedMove) ||
      moveShouldFollowSuitButDoesnt(proposedMove)) {
    return false;
  }

  return true;
}

bool BridgeGamestate::currentHandDoesNotHaveCard(
    const BridgeCard& proposedMove) const {

  auto currentCards = d_board[d_currentHand];

  if (find(currentCards.begin(), currentCards.end(), proposedMove) ==
      currentCards.end()) {
    return true;
  } else {
    return false;
  }
}

bool BridgeGamestate::moveShouldFollowSuitButDoesnt(
    const BridgeCard& proposedMove) const {

  //First card of a trick can be any suit
  if (d_currentTrickRecord.size() == 0) {
    return false;
  }

  auto currentCards = d_board[d_currentHand];

  const std::string leadSuit = d_currentTrickRecord[0].getSuit();

  if (proposedMove.getSuit() == leadSuit) {
    return false;
  }

  for (auto card : currentCards) {

    if (card.getSuit() == leadSuit) {
      return true;
    }
  }

  return false;
}
//std::vector<std::vector<BridgeCard>> BridgeGamestate::readBoardFromJson(boost::json::object& conf) {
//
//    auto boardJson = conf["board"].as_object();
//
//    std::vector<std::vector<BridgeCard>> boardVector;
//
//    std::vector<std::string> handJsonStrings = {"N_hand", "E_hand", "S_hand", "W_hand"};
//
//    for (auto handJsonString : handJsonStrings) {
//
//        std::vector<BridgeCard> handVector;
//
//        for (auto cardJson : boardJson[handJsonString].as_array()) {
//
//            auto cardSuitJson = cardJson.as_array()[0];
//            auto cardRankJson = cardJson.as_array()[1];
//
//            std::string cardSuit = boost::json::value_to<std::string>(cardSuitJson);
//            std::string cardRank = boost::json::value_to<std::string>(cardRankJson);
//
//            handVector.push_back(BridgeCard(cardSuit, cardRank));
//        }
//
//        boardVector.push_back(handVector);
//    }
//
//    return boardVector;
//
//}

//boost::json::object BridgeGamestate::getGamestateJson() const{
//
//
//    boost::json::object gamestateJson;
//
//    gamestateJson["contract_level"] = d_declarerTricksRequired - 6;
//    gamestateJson["trump_suit"] = convertSuitIntToString(trumpSuit);
//    gamestateJson["declarer_dir"] = convertDirIntToString(declarerHand);
//    gamestateJson["current_lead_hand"] = convertDirIntToString(d_currentLeadHand);
//    gamestateJson["current_trick"] = currentTrick;
//    gamestateJson["declarer_tricks_made"] = d_declarerTricksMade;
//
//
//    boost::json::object boardJson;
//
//    std::stack<std::string> handJsonNames({"W_hand", "S_hand", "E_hand", "N_hand"});
//
//    for (auto handVector : board) {
//
//        boost::json::array handJsonArr;
//
//        for (auto card : handVector) {
//            boost::json::array cardJsonArr = {card.getSuit(), card.getRank()};
//            handJsonArr.emplace_back(cardJsonArr);
//        }
//
//
//        std::string handJsonName = handJsonNames.top();
//        handJsonNames.pop();
//
//        boardJson[handJsonName] = handJsonArr;
//
//    }
//
//    gamestateJson["board"] = boardJson;
//
//
//    return gamestateJson;
//
//}

}  // namespace Bridge
