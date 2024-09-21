#include "models/bridge/bridgeGamestateLoader.hpp"

#include "models/bridge/bridgeGamestate.hpp"

#include <fstream>
#include <sstream>

#include <catch2/catch_test_macros.hpp>

namespace Bridge {

TEST_CASE("bridgGamestateLoader loads correctly") {
  auto expGamestate = loadGamestate("testBoards.json", "default_board_config");
  BridgeGamestate gamestate = *expGamestate;
  REQUIRE(gamestate.getWinner() == "");
}

}  // namespace Bridge
