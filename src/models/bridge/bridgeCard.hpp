#ifndef bridgeCard_h 
#define bridgeCard_h 

#include <string>


namespace Bridge{

class BridgeCard {

    public: 

        BridgeCard(const std::string suit, const std::string rank); 

        bool operator > (const BridgeCard& other);
        bool operator < (const BridgeCard& other);

        const std::string getSuit();
        const std::string getRank();


    private:

        const int mSuit;
        const int mRank;

        int convertToValidCardSuit(const std::string suit);

};




}

#endif
