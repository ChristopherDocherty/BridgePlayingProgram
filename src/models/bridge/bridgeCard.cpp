#include "bridgeCard.h"
#include "utils/bridgeUtils.h"

#include <string>
#include <exception>


namespace Bridge{

BridgeCard::BridgeCard(const std::string suit, const std::string rank) :
    mSuit(convertToValidCardSuit(suit)), mRank(convertRankStringToInt(rank)) {}; 


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


const int BridgeCard::convertToValidCardSuit(const std::string suit) {

    if (suit == "NT") {
        throw std::invalid_argument("No Trump is not a valid suit for a Card");
    } else {
        return convertSuitStringToInt(suit);
    }

}


}
