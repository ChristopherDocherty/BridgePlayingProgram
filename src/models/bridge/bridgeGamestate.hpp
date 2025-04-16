#ifndef BridgeGamestate_h
#define BridgeGamestate_h

#include "bridgeCard.hpp"

#include <string>
#include <vector>

namespace Bridge {

constexpr int TOTAL_TURNS = 13;

struct ContractInfo {
  int trumpSuit;
  int declarerTricksRequired;
  int level;
  int declarer;

  auto operator<=>(const ContractInfo &) const = default;
};

struct CurrentTrickInfo {
  int leadHand;
  int currHand;
  int num;
  std::vector<BridgeCard> cardsPlayed;

  std::string leadSuit() const;

  auto operator<=>(const CurrentTrickInfo &) const = default;
};

class BridgeGamestate {

public:
  BridgeGamestate(std::vector<std::vector<BridgeCard>> board,
                  std::string declarerHand, std::string currentLeadHand,
                  std::string trumpSuit, int contractLevel, int currentTrick,
                  int declarerTricksMade);

  BridgeGamestate(const BridgeGamestate &) = default;

  std::string getWinner();

  // Required for controller (MCTS) functions
  BridgeExpected<std::string> makeMoveMCTS(int validMoveNumber);
  // Requried for view functions
  BridgeExpected<std::string> makeMove(const std::string suit,
                                       const std::string rank);

  int getValidMoveCnt() const { return d_currentValidMoves.size(); };

  friend bool operator==(const BridgeGamestate &lhs,
                         const BridgeGamestate &rhs);

  const std::vector<std::vector<BridgeCard>> &board() const;

  int declarerHand() const;
  int currentLeadHand() const;
  int currentHand() const;

  int trumpSuit() const;
  int declarerTricksRequired() const;

  int currentTrick() const;
  int declarerTricksMade() const;

  std::vector<BridgeCard> currentTrickRecord() const;

  int contractLevel() const;

  ContractInfo contractInfo() const;
  CurrentTrickInfo currentTrickInfo() const;

private:
  std::vector<std::vector<BridgeCard>> d_board;

  ContractInfo d_contract;
  CurrentTrickInfo d_currentTrick;

  int d_declarerTricksMade;

  BridgeExpected<void> moveIsValid(const BridgeCard &proposedMove) const;
  BridgeExpected<void> currentHandHasCard(const BridgeCard &proposedMove) const;
  BridgeExpected<void>
  moveFollowsSuitCorrectly(const BridgeCard &proposedMove) const;

  void updateCurrentValidMoves();
  std::vector<BridgeCard> d_currentValidMoves;

  int getTricksRequired(int contractLevel) const { return contractLevel + 6; };

  int getTrickWinner() const;
};

} // namespace Bridge
#endif
