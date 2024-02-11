#ifndef BridgeGamestate_h
#define BridgeGamestate_h

#include "bridgeCard.hpp"

#include <string>
#include <vector>

namespace Bridge {

constexpr int TOTAL_TURNS = 13;

class BridgeGamestate {

 public:
  BridgeGamestate(std::vector<std::vector<BridgeCard>> board,
                  std::string declarerHand, std::string currentLeadHand,
                  std::string trumpSuit, int contractLevel, int currentTrick,
                  int declarerTricksMade);

  std::string getWinner();

  //Required for controller (MCTS) functions
  std::string makeMoveMCTS(int validMoveNumber);
  //Requried for view functions
  std::string makeMove(const std::string suit, const std::string rank);

  int getValidMoveCnt() const { return d_currentValidMoves.size(); };

  //        boost::json::object getGamestateJson() const;

 private:
  std::vector<std::vector<BridgeCard>> d_board;

  int d_declarerHand;
  int d_currentLeadHand;
  int d_currentHand;

  int d_trumpSuit;
  int d_declarerTricksRequired;

  int d_currentTrick;
  int d_declarerTricksMade;

  std::vector<BridgeCard> d_currentTrickRecord;

  bool moveIsValid(const BridgeCard& proposedMove) const;
  bool currentHandDoesNotHaveCard(const BridgeCard& proposedMove) const;
  bool moveShouldFollowSuitButDoesnt(const BridgeCard& proposedMove) const;

  void updateCurrentValidMoves();
  std::vector<BridgeCard> d_currentValidMoves;

  int getTricksRequired(int contractLevel) const { return contractLevel + 6; };
  //       std::vector<std::vector<BridgeCard>> readBoardFromJson(boost::json::object& conf);

  int getTrickWinner() const;
};

}  // namespace Bridge
#endif
