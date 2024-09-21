#include "models/bridge/bridgeCard.hpp"

#include <catch2/catch_test_macros.hpp>

namespace Bridge {

TEST_CASE("BridgeCardTests --  ConstructorTests") {
  REQUIRE_FALSE(BridgeCard::create("S", "0"));
  REQUIRE_FALSE(BridgeCard::create("T", "4"));
  REQUIRE_FALSE(BridgeCard::create("NT", "4"));
}

TEST_CASE("BridgeCardTests -- ComparisonTests") {

  BridgeCard fourSpade = *BridgeCard::create("S", "4");
  BridgeCard fiveDiamond = *BridgeCard::create("D", "5");
  BridgeCard queenDiamond = *BridgeCard::create("D", "Q");

  REQUIRE(fourSpade > queenDiamond);
  REQUIRE(queenDiamond > fiveDiamond);

  REQUIRE(fiveDiamond < queenDiamond);
  REQUIRE(queenDiamond < fourSpade);

  BridgeCard fourSpade2 = *BridgeCard::create("S", "4");

  REQUIRE(fourSpade == fourSpade2);
}

TEST_CASE("BridgeCardTests --  getterTests") {

  BridgeCard fourSpade = *BridgeCard::create("S", "4");
  BridgeCard fiveDiamond = *BridgeCard::create("D", "5");
  BridgeCard queenDiamond = *BridgeCard::create("D", "Q");

  REQUIRE(fourSpade.getSuit() == "S");
  REQUIRE(fourSpade.getRank() == "4");

  REQUIRE(fiveDiamond.getSuit() == "D");
  REQUIRE(fiveDiamond.getRank() == "5");

  REQUIRE(queenDiamond.getSuit() == "D");
  REQUIRE(queenDiamond.getRank() == "Q");
}

}  // namespace Bridge
