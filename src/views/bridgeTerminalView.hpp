#ifndef BRIDGE_TERM_VIEW_h
#define BRIDGE_TERM_VIEW_h

#include "interfaces/IObserver.hpp"

#include <boost/json.hpp>

#include <string>
#include <vector>

namespace Bridge {

class BridgeTerminalView : IObserver {

 public:
  void update(const std::string& gamestate) const override;

 private:
  constexpr static int westWhitespaceFillLength = 18;

  boost::json::object getGamestateJson(const std::string& gamestateStr) const;

  void printToScreen(boost::json::object gamestate) const;

  std::string getContractAndTurnInfo(boost::json::object gamestate) const;

  std::string getNSHand(boost::json::object gamestate,
                        const std::string& dir) const;

  std::string getCardsOfSuitString(boost::json::object board,
                                   const std::string& dir,
                                   const std::string& suit) const;
  std::vector<std::string> extractAllRanksOfSuit(boost::json::array& hand,
                                                 const std::string& suit) const;
};

}  // namespace Bridge
#endif
