#ifndef bridgeCard_h
#define bridgeCard_h

#include <string>

namespace Bridge {

class BridgeCard {

 public:
  BridgeCard(const std::string suit, const std::string rank);

  friend bool operator==(const BridgeCard& lhs, const BridgeCard& rhs);
  bool operator>(const BridgeCard& other);
  bool operator<(const BridgeCard& other);

  const std::string getSuit() const;
  const std::string getRank() const;

 private:
  int mSuit;
  int mRank;

  int convertToValidCardSuit(const std::string suit);
};

}  // namespace Bridge

#endif
