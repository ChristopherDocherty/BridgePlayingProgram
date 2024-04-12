#include <BridgeController.hpp>
#include <iostream>
#include <stdexcept>
#include "models/MCTree.hpp"
#include "models/bridge/bridgeGamestate.hpp"
#include "models/bridge/bridgeGamestateLoader.hpp"
#include "models/bridgeMctsFacade.hpp"
#include "views/bridge/bridgeTerminalView.hpp"

namespace Bridge {

void BridgeController::playGame() {

  BridgeGamestate bg =
      Bridge::loadGamestate("testBoards.json", "won_test_config");
  BridgeTerminalView view;

  std::string playerTeam = bg.declarerHand()%2 == bg.currentLeadHand()%2 ? "Declarer" : "Defense";

  int turnCnt = 0;

  while (true) {

    view.update(bg);

    if (turnCnt % 2 == 0) {
      std::cout << "Enter a card (e.g. 2H) or q to quit: " << std::endl;

      std::string input;
      std::cin >> input;

      if (input == "q") {
        break;
      }

      if (input.size() == 2) {
        std::string rank = input.substr(0, 1);
        std::string suit = input.substr(1, 1);
        try {

          auto t = bg.makeMove(suit, rank);
          std::cout << t << std::endl;
          ++turnCnt;

        } catch (std::invalid_argument& e) {
          std::cout << "Invalid move: " << e.what();
        }
      }
    } else {

      MCTree<BridgeMctsFacade> bridgeMcTree{BridgeMctsFacade{bg, playerTeam}};

      int bestMove = bridgeMcTree.findBestMove();

      bg.makeMoveMCTS(bestMove);
      ++turnCnt;
    }
  }
}

}  // namespace Bridge
