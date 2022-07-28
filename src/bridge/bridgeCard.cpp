#include "bridgeCard.h"
#include "utils/bridgeUtils.h"

#include <string>

namespace Bridge{

BridgeCard::BridgeCard(std::string suit, std::string rank) :
    mSuit(convertSuitStringToInt(suit)), mRank(convertRankStringToInt(rank)) {}; 


const bool BridgeCard::operator > (const BridgeCard& other) {

    if (mSuit > other.mSuit || mSuit == other.mSuit && mRank > other.mRank) {
        return true;
    } else {
        return false;
    }

};


const bool BridgeCard::operator < (const BridgeCard& other) {

    if (mSuit < other.mSuit || mSuit == other.mSuit && mRank < other.mRank) {
        return true;
    } else {
        return false;
    }

};


}
