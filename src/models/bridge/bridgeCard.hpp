#ifndef bridgeCard_h
#define bridgeCard_h

#include "utils/bridgeExpected.hpp"

#include <ostream>
#include <string>

namespace Bridge {

class BridgeCard {

 public:

  friend bool operator==(const BridgeCard& lhs, const BridgeCard& rhs);
  friend std::ostream& operator<<(std::ostream& os, const BridgeCard& bc);
  bool operator>(const BridgeCard& other) const;
  bool operator<(const BridgeCard& other) const;

  const std::string getSuit() const;
  const std::string getRank() const;

  static BridgeExpected<BridgeCard> create(const std::string suit, const std::string rank);

 private:
  int mSuit;
  int mRank;

  BridgeCard(int suit, int rank);
};

}  // namespace Bridge

#endif
