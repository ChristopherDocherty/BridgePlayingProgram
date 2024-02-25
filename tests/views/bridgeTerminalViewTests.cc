#include "views/bridgeTerminalView.hpp"

#include "models/bridge/bridgeGamestateLoader.hpp"

#include <catch2/catch_test_macros.hpp>

#include <iostream>

namespace Bridge {

TEST_CASE("Gamestate is displayed correctly") {

  BridgeGamestate gamestate =
      loadGamestate("testBoards.json", "default_board_config");

  std::string expectedView = "  ";
  std::cout << BridgeTerminalView::getGamestateString(gamestate);
  REQUIRE(""== expectedView);
}

}  // namespace Bridge
