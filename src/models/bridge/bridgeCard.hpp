#ifndef bridgeCard_h
#define bridgeCard_h

#include "utils/bridgeExpected.hpp"

#include <fmt/core.h>

#include <ostream>
#include <string>
#include <string_view>

namespace Bridge {

class BridgeCard {

public:
  friend bool operator==(const BridgeCard &lhs, const BridgeCard &rhs);
  friend std::ostream &operator<<(std::ostream &os, const BridgeCard &bc);
  bool operator>(const BridgeCard &other) const;
  bool operator<(const BridgeCard &other) const;

  const std::string getSuit() const;
  const std::string getRank() const;

  static BridgeExpected<BridgeCard> create(std::string_view suit,
                                           std::string_view rank);

private:
  int mSuit;
  int mRank;

  BridgeCard(const int suit, const int rank);
};

using Board = std::vector<std::vector<BridgeCard>>;

} // namespace Bridge

template <> struct fmt::formatter<Bridge::BridgeCard> {
  constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }

  template <typename FormatContext>
  auto format(const Bridge::BridgeCard &card, FormatContext &ctx) const {
    return format_to(ctx.out(), "{{suit: {}, rank: {}}}", card.getSuit(),
                     card.getRank());
  }
};

#endif
