#include "bridgeCard.h"
#include "utils/bridgeUtils.h"

namespace Bridge{


const int BridgeCard::validateSuitString(const std::string& suit) {
    
    auto suitMap = suitStringToIntMap();

    if (suitMap.find(suit) == suitMap.end()) {
        throw std::invalid_argument("Invalid suit string entered");
    }; 

    return suitMap[suit];

}


const int BridgeCard::validateRankString(const std::string& rank) {

    auto rankMap = rankStringToIntMap();

    if (rankMap.find(rank) == rankMap.end()) {
        throw std::invalid_argument("Invalid rank string entered");
    }; 

    return rankMap[rank];

}


const bool BridgeCard::operator > (const BridgeCard& other) {

    if (mSuit > other.mSuit || mSuit == other.mSuit && mRank > other.mRank) {
        return true;
    } else {
        return false;
    }

}


const bool BridgeCard::operator < (const BridgeCard& other) {

    if (mSuit < other.mSuit || mSuit == other.mSuit && mRank < other.mRank) {
        return true;
    } else {
        return false;
    }

}


}
