#ifndef BridgeGamestate_h
#define BridgeGamestate_h

#include "bridgeCard.hpp"

#include <includes/tl/expected.hpp>
#include <string>
#include <vector>

namespace Bridge {

template <typename T>
using BridgeExpected = tl::expected<T, std::string>;

constexpr int TOTAL_TURNS = 13;

class BridgeGamestate {

 public:
  BridgeGamestate(std::vector<std::vector<BridgeCard>> board,
                  std::string declarerHand, std::string currentLeadHand,
                  std::string trumpSuit, int contractLevel, int currentTrick,
                  int declarerTricksMade);

  BridgeGamestate(const BridgeGamestate&) = default;

  std::string getWinner();

  //Required for controller (MCTS) functions
  BridgeExpected<std::string> makeMoveMCTS(int validMoveNumber);
  //Requried for view functions
  BridgeExpected<std::string> makeMove(const std::string suit,
                                       const std::string rank);

  int getValidMoveCnt() const { return d_currentValidMoves.size(); };

  friend bool operator==(const BridgeGamestate& lhs,
                         const BridgeGamestate& rhs);

  const std::vector<std::vector<BridgeCard>>& board() const;

  int declarerHand() const;
  int currentLeadHand() const;
  int currentHand() const;

  int trumpSuit() const;
  int declarerTricksRequired() const;

  int currentTrick() const;
  int declarerTricksMade() const;

  std::vector<BridgeCard> currentTrickRecord() const;

  int contractLevel() const;

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

  int d_contractLevel;

  BridgeExpected<void> moveIsValid(const BridgeCard& proposedMove) const;
  BridgeExpected<void> currentHandHasCard(const BridgeCard& proposedMove) const;
  BridgeExpected<void> moveFollowsSuitCorrectly(
      const BridgeCard& proposedMove) const;

  void updateCurrentValidMoves();
  std::vector<BridgeCard> d_currentValidMoves;

  int getTricksRequired(int contractLevel) const { return contractLevel + 6; };
  //       std::vector<std::vector<BridgeCard>> readBoardFromJson(boost::json::object& conf);

  int getTrickWinner() const;
};

}  // namespace Bridge
#endif
