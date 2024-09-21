#include "bridgeCard.hpp"

#include "utils/bridgeUtils.hpp"

#include <stdexcept>
#include <string>
#include <tl/expected.hpp>

namespace Bridge {

namespace {

BridgeExpected<int> convertToValidCardSuit(const std::string suit) {
  if (suit == "NT") {
    return tl::make_unexpected("No Trump is not a valid suit for a Card");
  }

  return convertSuitStringToInt(suit);
}

}  // namespace

BridgeExpected<BridgeCard> BridgeCard::create(const std::string suit,
                                              const std::string rank) {

  auto expSuit = convertToValidCardSuit(suit);

  if (!expSuit) {
    return tl::make_unexpected(std::move(expSuit.error()));
  }

  return convertRankStringToInt(rank).map([&suitInt = *expSuit](int rankInt) {
    return BridgeCard{suitInt, rankInt};
  });
}

bool operator==(const BridgeCard& lhs, const BridgeCard& rhs) {

  return (lhs.mSuit == rhs.mSuit) && (lhs.mRank == rhs.mRank);
}

std::ostream& operator<<(std::ostream& os, const BridgeCard& bc) {
  os << "BridgeCard{" << bc.getRank() << bc.getSuit() << "}";
  return os;
}

bool BridgeCard::operator>(const BridgeCard& other) const {

  if ((mSuit > other.mSuit) ||
      ((mSuit == other.mSuit) && (mRank > other.mRank))) {
    return true;
  } else {
    return false;
  }
}

bool BridgeCard::operator<(const BridgeCard& other) const {

  if ((mSuit < other.mSuit) ||
      ((mSuit == other.mSuit) && (mRank < other.mRank))) {
    return true;
  } else {
    return false;
  }
}

const std::string BridgeCard::getSuit() const {
  return convertSuitIntToString(mSuit);
}

const std::string BridgeCard::getRank() const {
  return convertRankIntToString(mRank);
}

BridgeCard::BridgeCard(int suit, int rank) : mSuit(suit), mRank(rank){};

}  // namespace Bridge
