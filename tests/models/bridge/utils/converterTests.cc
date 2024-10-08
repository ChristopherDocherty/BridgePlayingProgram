#include <models/bridge/utils/bridgeUtils.hpp>

#include <catch2/catch_test_macros.hpp>

SCENARIO("Converters work as expected") {

  GIVEN("A valid suit strings") {

    WHEN("Converted to int") {

      THEN("The correct int is found") {
        //TODO: expected checks
        REQUIRE(*Bridge::convertSuitStringToInt("C") == 1);
        REQUIRE(*Bridge::convertSuitStringToInt("D") == 2);
        REQUIRE(*Bridge::convertSuitStringToInt("H") == 3);
        REQUIRE(*Bridge::convertSuitStringToInt("S") == 4);
        REQUIRE(*Bridge::convertSuitStringToInt("NT") == 0);
      }
    }
  }
  GIVEN("Invalid suit strings") {
    WHEN("Converted to int") {
      THEN("Unexpected returned") {
        REQUIRE_FALSE(Bridge::convertSuitStringToInt("J"));
        REQUIRE_FALSE(Bridge::convertSuitStringToInt("u"));
      }
    }
  }
  GIVEN("Valid suit integers") {

    WHEN("Converted to string") {

      THEN("Correct output") {
        REQUIRE(Bridge::convertSuitIntToString(0) == "NT");
        REQUIRE(Bridge::convertSuitIntToString(1) == "C");
        REQUIRE(Bridge::convertSuitIntToString(2) == "D");
        REQUIRE(Bridge::convertSuitIntToString(3) == "H");
        REQUIRE(Bridge::convertSuitIntToString(4) == "S");
      }
    }
  }
  GIVEN("Invalid suit integers") {

    WHEN("Converted to string") {

      THEN("Exception is thrown") {
        REQUIRE_THROWS_AS(Bridge::convertSuitIntToString(1000),
                          std::invalid_argument);
        REQUIRE_THROWS_AS(Bridge::convertSuitIntToString(-1000),
                          std::invalid_argument);
        REQUIRE_THROWS_AS(Bridge::convertSuitIntToString(28481),
                          std::invalid_argument);
      }
    }
  }

  GIVEN("Things to be converted") {
    WHEN("Converted") {
      THEN("correct") {

        auto expRankInt = Bridge::convertRankStringToInt("A");
        REQUIRE(expRankInt);
        REQUIRE(*expRankInt == 14);
        REQUIRE(Bridge::convertRankIntToString(3) == "3");

        REQUIRE_FALSE(Bridge::convertRankStringToInt("H"));
        REQUIRE_THROWS_AS(Bridge::convertRankIntToString(23),
                          std::invalid_argument);

        REQUIRE(Bridge::convertDirStringToInt("S") == 2);
        REQUIRE(Bridge::convertDirIntToString(1) == "E");

        REQUIRE_THROWS_AS(Bridge::convertDirStringToInt("J"),
                          std::invalid_argument);
        REQUIRE_THROWS_AS(Bridge::convertDirIntToString(23),
                          std::invalid_argument);

        REQUIRE(*Bridge::convertContractString("6S") == std::make_tuple(4, 12));
        REQUIRE(*Bridge::convertContractString("3NT") == std::make_tuple(0, 9));

        REQUIRE_FALSE(Bridge::convertContractString("TS"));
        REQUIRE_FALSE(Bridge::convertContractString("5Y"));
        REQUIRE_FALSE(Bridge::convertContractString("5NTT"));
      }
    }
  }
}
