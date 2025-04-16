#include "models/bridge/bridgeCard.hpp"

#include <catch2/matchers/catch_matchers.hpp>
#include <optional>

namespace Bridge {

class BoardMatcher : public Catch::Matchers::MatcherBase<Board> {
  using Card = Bridge::BridgeCard;
  using Board = std::vector<std::vector<Card>>;
  Board expected;
  mutable std::optional<Board> actualOnFailure;

public:
  explicit BoardMatcher(const Board &expected) : expected(expected) {}

  bool match(const Board &actual) const override {
    if (actual == expected)
      return true;
    actualOnFailure = actual;
    return false;
  }

  std::string describe() const override {
    if (!actualOnFailure.has_value()) {
      return "CardMatrix matcher failed, but no actual value was captured.";
    }

    const auto &actual = *actualOnFailure;
    std::string desc = "Mismatch in card matrix:\n";

    size_t rowCount = std::max(expected.size(), actual.size());
    for (size_t i = 0; i < rowCount; ++i) {
      const auto &expectedRow =
          i < expected.size() ? expected[i] : std::vector<Card>{};
      const auto &actualRow =
          i < actual.size() ? actual[i] : std::vector<Card>{};
      size_t colCount = std::max(expectedRow.size(), actualRow.size());

      for (size_t j = 0; j < colCount; ++j) {
        std::string expectedStr = j < expectedRow.size()
                                      ? fmt::format("{}", expectedRow[j])
                                      : "(missing)";
        std::string actualStr = j < actualRow.size()
                                    ? fmt::format("{}", actualRow[j])
                                    : "(missing)";
        bool match = j < expectedRow.size() && j < actualRow.size() &&
                     expectedRow[j] == actualRow[j];

        // TODO: fix matching logic here
        std::string prefix = match ? "    " : "  ✗ ";
        desc += fmt::format("{}[{}][{}] expected {}, got {}\n", prefix, i, j,
                            expectedStr, actualStr);
      }
    }

    return desc;
  }
};

inline BoardMatcher MatchesBoard(const Board &expected) {
  return BoardMatcher(expected);
}

} // namespace Bridge
