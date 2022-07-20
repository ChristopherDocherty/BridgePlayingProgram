#ifndef bridgeCard_h 
#define bridgeCard_h 

#include <string>


namespace Bridge{

class BridgeCard {

    public: 

        BridgeCard(std::string suit, std::string rank); 

        const bool operator > (const BridgeCard& other);
        const bool operator < (const BridgeCard& other);


    private:

        const int mSuit;
        const int mRank;


};




}

#endif
