#ifndef BRIDGE_TERM_VIEW_h
#define BRIDGE_TERM_VIEW_h

#include <models/bridge/bridgeGamestate.hpp>

#include <string>
#include <vector>

namespace Bridge {

namespace detail {

template <typename T>
std::pair<std::vector<T>, std::vector<T>> padVectorsToBeSameLength(
    std::vector<T>&& leftHand, std::vector<T>&& rightHand,
    const T& valueToPadWith) {
  size_t lSize = leftHand.size();
  size_t rSize = rightHand.size();

  if (lSize > rSize) {
    rightHand.resize(lSize, valueToPadWith);
  }

  if (lSize < rSize) {
    leftHand.resize(rSize, valueToPadWith);
  }
  return std::pair{leftHand, rightHand};
}
}  // namespace detail

class BridgeTerminalView {

 public:
  void update(const BridgeGamestate& gamestate);

  static std::string getGamestateString(const BridgeGamestate& gamestate);

 private:
  constexpr static int westWhitespaceFillLength = 18;

  static std::string getContractAndTurnInfo(const BridgeGamestate& gamestate);

  static std::string getEWHand(std::vector<std::string>&& eHand,
                               std::vector<std::string>&& wHand,
                               const BridgeGamestate& bg);

  static std::vector<std::string> getCardsOfSuitString(
      const std::vector<std::vector<BridgeCard>>& board, const std::string& dir,
      const std::string& suit);

  static std::unordered_map<std::string, std::vector<std::string>>
  getHandStrings(BridgeGamestate bg);
  static std::string getNSHand(
      const std::vector<std::string>& northHandStrings);
};

}  // namespace Bridge
#endif
