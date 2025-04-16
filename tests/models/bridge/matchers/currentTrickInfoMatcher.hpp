#include "models/bridge/bridgeGamestate.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <optional>
#include <string>
#include <vector>


namespace Bridge {

class CurrentTrickInfoMatcher
    : public Catch::Matchers::MatcherBase<CurrentTrickInfo> {
  CurrentTrickInfo expected;
  mutable std::optional<CurrentTrickInfo> actualOnFailure;

public:
  explicit CurrentTrickInfoMatcher(const CurrentTrickInfo &expected)
      : expected(expected) {}

  bool match(const CurrentTrickInfo &actual) const override {
    if (actual == expected)
      return true;
    actualOnFailure = actual;
    return false;
  }

  std::string describe() const override {
    if (!actualOnFailure.has_value()) {
      return "Matcher failed but no actual value was captured.";
    }

    const auto &actual = *actualOnFailure;
    std::string desc = "Mismatch in CurrentTrickInfo:\n";

    if (actual.leadHand != expected.leadHand)
      desc += fmt::format("  ✗ leadHand: expected {}, got {}\n",
                          expected.leadHand, actual.leadHand);
    if (actual.currHand != expected.currHand)
      desc += fmt::format("  ✗ currHand: expected {}, got {}\n",
                          expected.currHand, actual.currHand);
    if (actual.num != expected.num)
      desc += fmt::format("  ✗ num: expected {}, got {}\n", expected.num,
                          actual.num);

    if (actual.cardsPlayed != expected.cardsPlayed) {
      desc += "  ✗ cardsPlayed mismatch:\n";
      size_t maxLen =
          std::max(actual.cardsPlayed.size(), expected.cardsPlayed.size());

      for (size_t i = 0; i < maxLen; ++i) {
        std::string actualStr = i < actual.cardsPlayed.size()
                                    ? fmt::format("{}", actual.cardsPlayed[i])
                                    : "(none)";
        std::string expectedStr =
            i < expected.cardsPlayed.size()
                ? fmt::format("{}", expected.cardsPlayed[i])
                : "(none)";

        std::string prefix =
            (i < actual.cardsPlayed.size() && i < expected.cardsPlayed.size() &&
             actual.cardsPlayed[i] == expected.cardsPlayed[i])
                ? "    "
                : "  ✗ ";

        desc += fmt::format("{} for entry: [{}] expected {}, got {}\n", prefix, i,
                            expectedStr, actualStr);
      }
    }

    return desc;
  }
};

inline CurrentTrickInfoMatcher
MatchesCurrentTrickInfo(const CurrentTrickInfo &expected) {
  return CurrentTrickInfoMatcher(expected);
}
} // namespace Bridge
