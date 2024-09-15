#ifndef BRIDGE_MCTS_FACADE_H
#define BRIDGE_MCTS_FACADE_H

#include "bridge/bridgeGamestate.hpp"

namespace Bridge {

class BridgeMctsFacade {

 public:
  BridgeMctsFacade(BridgeGamestate bg, std::string playerTeam);

  std::vector<int> getAvailableMoves();

  std::string makeMove(int validMoveNumber);
  bool gameIsComplete();

  int winner();

 private:
  BridgeGamestate d_gamestate;
  std::string d_playerTeam;
};

}  // namespace Bridge
#endif
