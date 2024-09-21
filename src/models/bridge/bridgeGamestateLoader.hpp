#ifndef BRIDGEGAMESTATE_LOADER_H
#define BRIDGEGAMESTATE_LOADER_H

#include "bridgeGamestate.hpp"

#include <string>
#include <vector>

#include <nlohmann/json_fwd.hpp>

using json = nlohmann::json;

namespace Bridge {

BridgeExpected<BridgeGamestate> loadGamestate(std::string configFilepath,
                                              std::string key);
BridgeExpected<std::vector<std::vector<BridgeCard>>> getBoard(json boardData);

}  // namespace Bridge
#endif
