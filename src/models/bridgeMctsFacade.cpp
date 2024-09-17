#include "bridgeMctsFacade.hpp"

#include <range/v3/range/conversion.hpp>
#include <range/v3/view/iota.hpp>

#include <iostream>

namespace Bridge {

BridgeMctsFacade::BridgeMctsFacade(BridgeGamestate bg, std::string playerTeam)
    : d_gamestate(std::move(bg)), d_playerTeam(std::move(playerTeam)) {}

std::vector<int> BridgeMctsFacade::getAvailableMoves() {

  int validMoves = d_gamestate.getValidMoveCnt();

  if (validMoves == 1) {
    return {0};
  }

  return ranges::views::ints(0, validMoves) | ranges::to<std::vector>;
}

std::string BridgeMctsFacade::makeMove(int validMoveNumber) {
  return d_gamestate.makeMoveMCTS(validMoveNumber)
      .map_error([&validMoveNumber](std::string&& err) {
        throw std::invalid_argument(
            "Invalid MCTS move attempted=" + std::to_string(validMoveNumber) +
            " - failing with error=" + err);
      })
      .value();
}

bool BridgeMctsFacade::gameIsComplete() {
  return !d_gamestate.getWinner().empty();
}

int BridgeMctsFacade::winner() {
  //contract is that 0 is computer win
  std::string winner = d_gamestate.getWinner();
  if (winner == "") {
    return -1;
  }
  return winner == d_playerTeam ? 1 : 0;
}

}  // namespace Bridge
