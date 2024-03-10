#include <BridgeController.hpp>
#include <iostream>
#include "models/bridge/bridgeGamestate.hpp"
#include "models/bridge/bridgeGamestateLoader.hpp"
#include "views/bridgeTerminalView.hpp"

namespace Bridge {

void BridgeController::playGame() {

  BridgeGamestate bg =
      Bridge::loadGamestate("testBoards.json", "default_board_config");

  BridgeTerminalView view;

  while (true) {

    view.update(bg);

    std::string suit;
    std::string rank;
    std::cin >> suit >> rank;

    if (rank == "q") {
      break;
    }
    auto t = bg.makeMove(suit, rank);
    std::cout << t << std::endl;
  }
}

}  // namespace Bridge
