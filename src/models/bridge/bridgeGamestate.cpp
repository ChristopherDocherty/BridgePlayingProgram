#include "bridgeGamestate.hpp"
#include "bridgeCard.hpp"
#include "utils/bridgeUtils.hpp"

#include <string>
#include <vector>



namespace Bridge {

   
BridgeGamestate::BridgeGamestate(const BoardConf& conf) :
    declarerHand( convertDirStringToInt(conf.declarerDirection) ), 
    currentLeadHand( convertDirStringToInt(conf.declarerDirection) ), 
    currentHand( convertDirStringToInt(conf.declarerDirection) ), 
    trumpSuit( std::get<0>(convertContractString(conf.contractString)) ),
    declarerTricksRequired( std::get<1>(convertContractString(conf.contractString)) )
{
    auto handVector = {conf.northHand, conf.eastHand, conf.southHand, conf.westHand};
    hands = getBoard(handVector, conf.delimiter); 
}


std::string BridgeGamestate::getWinner() {


    if (declarerTricksMade >= declarerTricksRequired) {
        return "Declarer"; 
    } else if ( (totalTurns  - currentTrick) < (declarerTricksRequired - declarerTricksMade)) {
        return "Defence";
    } else {
        return "";
    }
    //possibly simulate till the end
} 

//got to change this name as I will be putting getters and setters on this
std::vector<std::vector<BridgeCard>> BridgeGamestate::getBoard(const std::vector<std::vector<std::string>>& handVectors, const std::string& delimiter) {

    std::vector<std::vector<BridgeCard>> board;

    for (auto handVector: handVectors) {

        std::vector<BridgeCard> currHandCards;

        for (auto handString : handVector) {

            std::string suitString = handString.substr(0,1);

            std::string rankString;
            size_t start = 1;
            auto end = handString.find(delimiter);
            while (end != std::string::npos) {

                rankString = handString.substr(start, end - start);
                currHandCards.push_back( BridgeCard(suitString, rankString) );

                start = end + delimiter.length();
                end = handString.find(delimiter, start);

            }

            
            rankString = handString.substr(start, end - start);
            currHandCards.push_back( BridgeCard(suitString, rankString) );

        }

        board.push_back(currHandCards);

    }

    return board;

}



}


