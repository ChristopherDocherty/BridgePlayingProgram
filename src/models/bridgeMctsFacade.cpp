#include "bridgeMctsFacade.hpp"

#include <range/v3/range/conversion.hpp>
#include <range/v3/view/iota.hpp>

namespace Bridge {

BridgeMctsFacade::BridgeMctsFacade(BridgeGamestate bg)
    : d_gamestate(std::move(bg)) {}

std::vector<int> BridgeMctsFacade::getAvailableMoves() {

  int validMoves = d_gamestate.getValidMoveCnt();

  return ranges::views::ints(0, validMoves) | ranges::to<std::vector>;
}

std::string BridgeMctsFacade::makeMove(int validMoveNumber) {
  return d_gamestate.makeMoveMCTS(validMoveNumber);
}

bool BridgeMctsFacade::gameIsComplete() {
  return d_gamestate.getWinner() == "Declarer" ||
         d_gamestate.getWinner() == "Defence";
}

int BridgeMctsFacade::winner() {
  std::string winner = d_gamestate.getWinner();
  if (winner == "") {
    return -1;
  }
  return winner == "Declarer" ? 1 : 0;
}

}  // namespace Bridge
