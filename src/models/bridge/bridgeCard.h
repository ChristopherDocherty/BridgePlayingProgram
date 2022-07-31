#ifndef bridgeCard_h 
#define bridgeCard_h 

#include <string>


namespace Bridge{

class BridgeCard {

    public: 

        BridgeCard(const std::string suit, const std::string rank); 

        const bool operator > (const BridgeCard& other);
        const bool operator < (const BridgeCard& other);


    private:

        const int mSuit;
        const int mRank;

        const int convertToValidCardSuit(const std::string suit);

};




}

#endif
