#ifndef BridgeUtils
#define BridgeUtils

#include "bridgeExpected.hpp"

#include <string>
#include <tuple>

namespace Bridge {

BridgeExpected<int> convertSuitStringToInt(std::string_view suit);
const std::string convertSuitIntToString(const int suitInt);

BridgeExpected<int> convertRankStringToInt(std::string_view rank);
const std::string convertRankIntToString(const int rankInt);

int convertDirStringToInt(std::string_view dir);
const std::string convertDirIntToString(const int dirInt);

BridgeExpected<std::tuple<int, int>>
convertContractString(const std::string &contractString);

} // namespace Bridge
#endif
