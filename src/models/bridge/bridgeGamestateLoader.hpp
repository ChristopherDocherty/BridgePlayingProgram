#ifndef BRIDGEGAMESTATE_LOADER_H
#define BRIDGEGAMESTATE_LOADER_H

#include "bridgeGamestate.hpp"

#include <string>
#include <vector>

#include <includes/json_fwd.hpp>

using json = nlohmann::json;

namespace Bridge {

BridgeGamestate loadGamestate(std::string configFilepath, std::string key);
std::vector<std::vector<BridgeCard>> getBoard(json boardData);

}  // namespace Bridge
#endif
