#include "bridgeUtils.hpp"

#include "models/bridge/utils/bridgeExpected.hpp"

#include <map>
#include <sstream>
#include <string>
#include <tuple>

#include <fmt/format.h>
#include <tl/expected.hpp>

namespace Bridge {

namespace {
const std::map<std::string, int, std::less<>> SUIT_MAP = {
    {"NT", 0}, {"C", 1}, {"D", 2}, {"H", 3}, {"S", 4}};

const std::map<int, std::string> INT_TO_SUIT = {
    {0, "NT"}, {1, "C"}, {2, "D"}, {3, "H"}, {4, "S"}};

const std::map<std::string, int, std::less<>> RANK_TO_NUMBER = {
    {"1", 1}, {"2", 2}, {"3", 3},   {"4", 4},  {"5", 5},  {"6", 6},  {"7", 7},
    {"8", 8}, {"9", 9}, {"10", 10}, {"J", 11}, {"Q", 12}, {"K", 13}, {"A", 14}};

const std::map<int, std::string> INT_TO_RANK = {
    {1, "1"}, {2, "2"}, {3, "3"},   {4, "4"},  {5, "5"},  {6, "6"},  {7, "7"},
    {8, "8"}, {9, "9"}, {10, "10"}, {11, "J"}, {12, "Q"}, {13, "K"}, {14, "A"}};

const std::map<std::string, int, std::less<>> DIR_TO_INT = {
    {"N", 0}, {"E", 1}, {"S", 2}, {"W", 3}};

const std::map<int, std::string> INT_TO_DIR = {
    {0, "N"}, {1, "E"}, {2, "S"}, {3, "W"}};

} // namespace

BridgeExpected<int> convertSuitStringToInt(std::string_view suit) {

  auto findSuit = SUIT_MAP.find(suit);
  if (findSuit == SUIT_MAP.end()) {
    return tl::make_unexpected("Invalid suit string entered");
  };

  return findSuit->second;
}

const std::string convertSuitIntToString(const int suitInt) {

  auto findSuit = INT_TO_SUIT.find(suitInt);
  if (findSuit == INT_TO_SUIT.end()) {
    throw std::invalid_argument("Invalid suit string entered");
  };

  return findSuit->second;
}

BridgeExpected<int> convertRankStringToInt(std::string_view rank) {

  auto findRank = RANK_TO_NUMBER.find(rank);
  if (findRank == RANK_TO_NUMBER.end()) {
    return tl::make_unexpected(
        fmt::format("Invalid rank string entered=\"{}\"", rank));
  };

  return findRank->second;
}

const std::string convertRankIntToString(const int rankInt) {

  auto findRank = INT_TO_RANK.find(rankInt);
  if (findRank == INT_TO_RANK.end()) {
    throw std::invalid_argument(
        fmt::format("Invalid rank int entered={}", rankInt));
  };

  return findRank->second;
}

int convertDirStringToInt(std::string_view dir) {

  auto findDir = DIR_TO_INT.find(dir);
  if (findDir == DIR_TO_INT.end()) {
    throw std::invalid_argument("Invalid direction string entered");
  };

  return findDir->second;
}

const std::string convertDirIntToString(const int dirInt) {

  auto findDir = INT_TO_DIR.find(dirInt);
  if (findDir == INT_TO_DIR.end()) {
    throw std::invalid_argument("Invalid direction string entered");
  };

  return findDir->second;
}

BridgeExpected<std::tuple<int, int>>
convertContractString(const std::string &contractString) {

  std::stringstream contractStream(contractString);

  int contractNumber;
  std::string contractSuit;

  contractStream >> contractNumber >> contractSuit;

  if (contractStream.fail()) {
    return tl::make_unexpected(fmt::format(
        "Invalid contract string \"{}\" entered: first char must be an valid "
        "integer.",
        contractString));
  }

  int tricksRequired = contractNumber + 6;

  return convertSuitStringToInt(contractSuit)
      .map([&tricksRequired](int trumpSuitInt) {
        return std::make_tuple(trumpSuitInt, tricksRequired);
      });
}

} // namespace Bridge
