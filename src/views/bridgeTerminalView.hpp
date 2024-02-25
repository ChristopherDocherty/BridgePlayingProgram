#ifndef BRIDGE_TERM_VIEW_h
#define BRIDGE_TERM_VIEW_h

#include <models/bridge/bridgeGamestate.hpp>

#include <string>
#include <vector>

namespace Bridge {

class BridgeTerminalView {

 public:
  static void update(const BridgeGamestate& gamestate);

  static std::string getGamestateString(const BridgeGamestate& gamestate);

 private:
  constexpr static int westWhitespaceFillLength = 18;

  static std::string getContractAndTurnInfo(const BridgeGamestate& gamestate);

  static std::string getNSHand(const BridgeGamestate& gamestate,
                               const std::string& dir);

  static std::string getCardsOfSuitString(
      const std::vector<std::vector<BridgeCard>>& board, const std::string& dir,
      const std::string& suit);

  static std::vector<std::string> extractAllRanksOfSuit(
      const std::vector<BridgeCard>& hand, const std::string& suit);
};

}  // namespace Bridge
#endif
