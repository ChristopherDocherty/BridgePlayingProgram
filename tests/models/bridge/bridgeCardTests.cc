#include <gtest/gtest.h>
#include "models/bridge/bridgeCard.hpp"



TEST(BridgeCardTests, ConstructorTests) {

    EXPECT_THROW(Bridge::BridgeCard testCard("S", "0"), std::invalid_argument);
    EXPECT_THROW(Bridge::BridgeCard testCard("T", "4"), std::invalid_argument);


    EXPECT_THROW(Bridge::BridgeCard testCard("NT", "4"), std::invalid_argument);

}



TEST(BridgeCardTests, ComparisonTests) {
   
    Bridge::BridgeCard fourSpade("S", "4"); 
    Bridge::BridgeCard fiveDiamond("D", "5"); 
    Bridge::BridgeCard queenDiamond("D", "Q"); 


    EXPECT_TRUE(fourSpade > queenDiamond);
    EXPECT_TRUE(queenDiamond > fiveDiamond);

    EXPECT_TRUE(fiveDiamond < queenDiamond);
    EXPECT_TRUE(queenDiamond < fourSpade);


}


TEST(BridgeCardTests, getterTests) {

    Bridge::BridgeCard fourSpade("S", "4"); 
    Bridge::BridgeCard fiveDiamond("D", "5"); 
    Bridge::BridgeCard queenDiamond("D", "Q"); 

    EXPECT_EQ(fourSpade.getSuit(), "S");
    EXPECT_EQ(fourSpade.getRank(), "4");

    EXPECT_EQ(fiveDiamond.getSuit(), "D");
    EXPECT_EQ(fiveDiamond.getRank(), "5");

    EXPECT_EQ(queenDiamond.getSuit(), "D");
    EXPECT_EQ(queenDiamond.getRank(), "Q");


}
