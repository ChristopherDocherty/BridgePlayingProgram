#include <gtest/gtest.h>
#include "bridge/bridgeCard.h"



TEST(BridgeCardTests, ConstructorTests) {

    EXPECT_THROW(Bridge::BridgeCard testCard("S", "0"), std::invalid_argument);
    EXPECT_THROW(Bridge::BridgeCard testCard("T", "4"), std::invalid_argument);


    EXPECT_THROW(Bridge::BridgeCard testCard("NT", "4"), std::invalid_argument);

}



TEST(BridgeCardTests, CopmarisonTests) {
   
    Bridge::BridgeCard fourSpade("S", "4"); 
    Bridge::BridgeCard fiveDiamond("D", "5"); 
    Bridge::BridgeCard queenDiamond("D", "Q"); 


    EXPECT_TRUE(fourSpade > queenDiamond);
    EXPECT_TRUE(queenDiamond > fiveDiamond);

    EXPECT_TRUE(fiveDiamond < queenDiamond);
    EXPECT_TRUE(queenDiamond < fourSpade);


}
