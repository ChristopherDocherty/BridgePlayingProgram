#include "bridgeCard.hpp"
#include "utils/bridgeUtils.hpp"

#include <exception>
#include <string>


namespace Bridge{

BridgeCard::BridgeCard(const std::string suit, const std::string rank) :
    mSuit(convertToValidCardSuit(suit)), mRank(convertRankStringToInt(rank)) {} 


bool BridgeCard::operator == (const BridgeCard& other) {

    if ( (mSuit == other.mSuit) && (mRank == other.mRank) )  {
        return true;
    } else {
        return false;
    }

}

bool BridgeCard::operator > (const BridgeCard& other) {

    if ( (mSuit > other.mSuit) || ( (mSuit == other.mSuit) && (mRank > other.mRank)) ) {
        return true;
    } else {
        return false;
    }

}


bool BridgeCard::operator < (const BridgeCard& other) {

    if ( (mSuit < other.mSuit) || ( (mSuit == other.mSuit) && (mRank < other.mRank)) ) {
        return true;
    } else {
        return false;
    }

}


int BridgeCard::convertToValidCardSuit(const std::string suit) {

    if (suit == "NT") {
        throw std::invalid_argument("No Trump is not a valid suit for a Card");
    } else {
        return convertSuitStringToInt(suit);
    }

}


const std::string BridgeCard::getSuit() const {
    return convertSuitIntToString(mSuit);
}

const std::string BridgeCard::getRank() const {
    return convertRankIntToString(mRank);
}


}
