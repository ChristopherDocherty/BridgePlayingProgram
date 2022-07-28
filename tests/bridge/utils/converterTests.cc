#include <gtest/gtest.h>
#include "bridge/utils/bridgeUtils.h"



TEST(ConverterTests, SuitConverterTests) {

  EXPECT_EQ(4, Bridge::convertSuitStringToInt("S"));
  EXPECT_EQ("D", Bridge::convertSuitIntToString(2));

  EXPECT_EQ(0, Bridge::convertSuitStringToInt("NT"));


  EXPECT_THROW(Bridge::convertSuitStringToInt("J"), std::invalid_argument);
  EXPECT_THROW(Bridge::convertSuitIntToString(23), std::invalid_argument);

}

TEST(ConverterTests, RankConverterTests) {

  EXPECT_EQ(14, Bridge::convertRankStringToInt("A"));
  EXPECT_EQ("3", Bridge::convertRankIntToString(3));


  EXPECT_THROW(Bridge::convertRankStringToInt("H"), std::invalid_argument);
  EXPECT_THROW(Bridge::convertRankIntToString(23), std::invalid_argument);

}

TEST(ConverterTests, DirConverterTests) {

  EXPECT_EQ(2, Bridge::convertDirStringToInt("E"));
  EXPECT_EQ("S", Bridge::convertDirIntToString(3));


  EXPECT_THROW(Bridge::convertDirStringToInt("J"), std::invalid_argument);
  EXPECT_THROW(Bridge::convertDirIntToString(23), std::invalid_argument);

}



TEST(ConverterTests, ContractConverterTests) {

    EXPECT_EQ(std::make_tuple(4,12), Bridge::convertContractString("6S"));

    EXPECT_THROW(Bridge::convertContractString("TS"), std::invalid_argument);
    EXPECT_THROW(Bridge::convertContractString("5Y"), std::invalid_argument);
    EXPECT_THROW(Bridge::convertContractString("5NTT"), std::invalid_argument);
    
}
