#ifndef BRIDGEGAMESTATE_LOADER_H2
#define BRIDGEGAMESTATE_LOADER_H2

#include "bridgeGamestate.hpp"

#include <string>

namespace Bridge {

using Board = std::vector<std::vector<BridgeCard>>;

struct TestCases {
  std::vector<std::pair<std::string, std::string>> moves;
  std::vector<CurrentTrickInfo> trickInfos;
  std::vector<Board> boards;
};

struct TestGame {
  BridgeGamestate initialGamestate;
  TestCases testCases;
};

BridgeExpected<TestGame> loadTestGame(const std::string &configFilepath);

} // namespace Bridge
#endif
