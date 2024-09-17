#include <BridgeController.hpp>

#include <iostream>
#include <set>
#include <stdexcept>

#include "models/MCTree.hpp"
#include "models/bridge/bridgeGamestate.hpp"
#include "models/bridge/bridgeGamestateLoader.hpp"
#include "models/bridge/utils/bridgeUtils.hpp"
#include "models/bridgeMctsFacade.hpp"
#include "views/bridge/bridgeTerminalView.hpp"

namespace Bridge {

namespace {
const std::set<std::string> VALID_DESIRED_DIRS{"N", "E"};
}

void BridgeController::playGame() {

  BridgeGamestate bg = Bridge::loadGamestate("testBoards.json", "squeeze");
  BridgeTerminalView view;

  std::string desiredDir{};
  while (!VALID_DESIRED_DIRS.contains(desiredDir)) {
    std::cout << "Enter N to play NS or E to play EW: " << std::endl;
    std::cin >> desiredDir;
  }

  int desiredDirInt = convertDirStringToInt(desiredDir);
  std::string playerTeam =
      bg.declarerHand() % 2 == desiredDirInt ? "Declarer" : "Defence";

  while (bg.getWinner() == "") {

    view.update(bg);

    if (bg.currentHand() % 2 == desiredDirInt) {
      std::cout << "Enter a card (e.g. 2H) or q to quit: " << std::endl;

      std::string input;
      std::cin >> input;

      if (input == "q") {
        break;
      }

      if (input.size() == 2) {
        std::string rank = input.substr(0, 1);
        std::string suit = input.substr(1, 1);

        bg.makeMove(suit, rank)
            .map_error([](std::string&& err) {
              std::cout << "Invalid move entered: " << err << std::endl;
            });
      } 
    } else {

      MCTree<BridgeMctsFacade> bridgeMcTree{BridgeMctsFacade{bg, playerTeam}};

      int bestMove = bridgeMcTree.findBestMove();

      bg.makeMoveMCTS(bestMove);
    }
  }

  std::cout << "Winner is: " << bg.getWinner();
}

}  // namespace Bridge
