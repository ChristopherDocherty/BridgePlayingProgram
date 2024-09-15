#include "models/bridge/bridgeCard.hpp"

#include <catch2/catch_test_macros.hpp>

namespace Bridge {

TEST_CASE("BridgeCardTests --  ConstructorTests") {
  REQUIRE_THROWS_AS(BridgeCard("S", "0"), std::invalid_argument);
  REQUIRE_THROWS_AS(BridgeCard("T", "4"), std::invalid_argument);
  REQUIRE_THROWS_AS(BridgeCard("NT", "4"), std::invalid_argument);
}

TEST_CASE("BridgeCardTests -- ComparisonTests") {

  BridgeCard fourSpade("S", "4");
  BridgeCard fiveDiamond("D", "5");
  BridgeCard queenDiamond("D", "Q");

  REQUIRE(fourSpade > queenDiamond);
  REQUIRE(queenDiamond > fiveDiamond);

  REQUIRE(fiveDiamond < queenDiamond);
  REQUIRE(queenDiamond < fourSpade);

  BridgeCard fourSpade2("S", "4");

  REQUIRE(fourSpade == fourSpade2);
}

TEST_CASE("BridgeCardTests --  getterTests") {

  BridgeCard fourSpade("S", "4");
  BridgeCard fiveDiamond("D", "5");
  BridgeCard queenDiamond("D", "Q");

  REQUIRE(fourSpade.getSuit() == "S");
  REQUIRE(fourSpade.getRank() == "4");

  REQUIRE(fiveDiamond.getSuit() == "D");
  REQUIRE(fiveDiamond.getRank() == "5");

  REQUIRE(queenDiamond.getSuit() == "D");
  REQUIRE(queenDiamond.getRank() == "Q");
}

}  // namespace Bridge
