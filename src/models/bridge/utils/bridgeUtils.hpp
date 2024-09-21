#ifndef BridgeUtils
#define BridgeUtils

#include "bridgeExpected.hpp"

#include <string>
#include <tuple>

namespace Bridge {

BridgeExpected<int> convertSuitStringToInt(const std::string& suit);
const std::string convertSuitIntToString(const int suitInt);

BridgeExpected<int> convertRankStringToInt(const std::string& rank);
const std::string convertRankIntToString(const int rankInt);

int convertDirStringToInt(const std::string& dir);
const std::string convertDirIntToString(const int dirInt);

BridgeExpected<std::tuple<int, int>> convertContractString(
    const std::string& contractString);

}  // namespace Bridge
#endif
