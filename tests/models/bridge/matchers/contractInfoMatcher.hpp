#include "models/bridge/bridgeGamestate.hpp"

#include <optional>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <fmt/core.h>

namespace Bridge {

class ContractInfoMatcher : public Catch::Matchers::MatcherBase<ContractInfo> {
  ContractInfo expected;
  mutable std::optional<ContractInfo> actualOnFailure;

public:
  explicit ContractInfoMatcher(const ContractInfo &expected)
      : expected(expected) {}

  bool match(const ContractInfo &actual) const override {
    if (actual == expected)
      return true;
    actualOnFailure = actual;
    return false;
  }

  std::string describe() const override {
    if (!actualOnFailure.has_value()) {
      return "ContractInfo matcher failed, but no actual value was captured.";
    }

    const ContractInfo &actual = *actualOnFailure;

    std::string desc;
    desc += "Mismatch in ContractInfo fields:\n";

    if (actual.trumpSuit != expected.trumpSuit) {
      desc += fmt::format("  ✗ trumpSuit: expected {}, got {}\n",
                          expected.trumpSuit, actual.trumpSuit);
    }
    if (actual.declarerTricksRequired != expected.declarerTricksRequired) {
      desc += fmt::format("  ✗ declarerTricksRequired: expected {}, got {}\n",
                          expected.declarerTricksRequired,
                          actual.declarerTricksRequired);
    }
    if (actual.level != expected.level) {
      desc += fmt::format("  ✗ level: expected {}, got {}\n", expected.level,
                          actual.level);
    }
    if (actual.declarer != expected.declarer) {
      desc += fmt::format("  ✗ declarer: expected {}, got {}\n",
                          expected.declarer, actual.declarer);
    }

    return desc;
  }
};

inline ContractInfoMatcher MatchesContractInfo(const ContractInfo &expected) {
  return ContractInfoMatcher(expected);
}
} // namespace Bridge
