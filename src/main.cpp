#include <cstddef>
#include <models/bridge/bridgeGamestateLoader.hpp>
#include <range/v3/all.hpp>
#include <string_view>
#include <views/bridgeTerminalView.hpp>

#include <iostream>
#include "range/v3/algorithm/for_each.hpp"
#include "range/v3/view/cartesian_product.hpp"
#include "range/v3/view/transform.hpp"

int main() {

  Bridge::BridgeGamestate gamestate =
      Bridge::loadGamestate("testBoards.json", "default_board_config");

  gamestate.makeMove("S", "A");
  gamestate.makeMove("H", "Q");
  gamestate.makeMove("S", "9");

  std::cout << Bridge::BridgeTerminalView::getGamestateString(gamestate) << std::endl;

  return 0;
}
