#include "bridgeGamestate.hpp"
#include "bridgeCard.hpp"
#include "utils/bridgeUtils.hpp"

#include <string>
#include <vector>
#include <stack>
#include <algorithm>



namespace Bridge {


BridgeGamestate::BridgeGamestate(boost::json::object& conf) :
    declarerHand( convertDirStringToInt(boost::json::value_to<std::string>(conf["declarer_dir"])) ), 
    currentLeadHand( convertDirStringToInt(boost::json::value_to<std::string>(conf["declarer_dir"])) ), 
    currentHand( convertDirStringToInt(boost::json::value_to<std::string>(conf["declarer_dir"])) ), 
    trumpSuit( convertSuitStringToInt(boost::json::value_to<std::string>(conf["trump_suit"])) ),
    declarerTricksRequired( getTricksRequired(boost::json::value_to<int>(conf["contract_level"])) )
{
    board = readBoardFromJson(conf);
    
//    updateCurrentValidMoves();
}



std::vector<std::vector<BridgeCard>> BridgeGamestate::readBoardFromJson(boost::json::object& conf) {
    
    auto boardJson = conf["board"].as_object(); 

    std::vector<std::vector<BridgeCard>> boardVector;

    std::vector<std::string> handJsonStrings = {"N_hand", "E_hand", "S_hand", "W_hand"};

    for (auto handJsonString : handJsonStrings) {

        std::vector<BridgeCard> handVector;

        for (auto cardJson : boardJson[handJsonString].as_array()) {

            auto cardSuitJson = cardJson.as_array()[0];
            auto cardRankJson = cardJson.as_array()[1];

            std::string cardSuit = boost::json::value_to<std::string>(cardSuitJson);
            std::string cardRank = boost::json::value_to<std::string>(cardRankJson);

            handVector.push_back(BridgeCard(cardSuit, cardRank));
        }

        boardVector.push_back(handVector);
    }     

    return boardVector;

}
  

boost::json::object BridgeGamestate::getGamestateJson() const{


    boost::json::object gamestateJson;

    gamestateJson["contract_level"] = declarerTricksRequired - 6; 
    gamestateJson["trump_suit"] = convertSuitIntToString(trumpSuit);
    gamestateJson["declarer_dir"] = convertDirIntToString(declarerHand);
    
    boost::json::object boardJson;

    std::stack<std::string> handJsonNames({"W_hand", "S_hand", "E_hand", "N_hand"});

    for (auto handVector : board) {

        boost::json::array handJsonArr;

        for (auto card : handVector) {
            boost::json::array cardJsonArr = {card.getSuit(), card.getRank()};
            handJsonArr.emplace_back(cardJsonArr);
        }


        std::string handJsonName = handJsonNames.top();
        handJsonNames.pop();

        boardJson[handJsonName] = handJsonArr;
        
    }

    gamestateJson["board"] = boardJson;


    return gamestateJson;
    
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

//void BridgeGamestate::makeMoveMCTS(int validMoveNumber) {
//    BridgeCard cardPlayed = currentValidMoves[validMoveNumber];
//    makeMove(cardPlayed.getSuit(), cardPlayed.getRank());
//} 

//void BridgeGamestate::makeMove(const std::string suit, const std::string rank){}
//
//void BridgeGamestate::updateCurrentValidMoves(){}

bool BridgeGamestate::moveIsValid(const BridgeCard& proposedMove) const {

    if ( currentHandDoesNotHaveCard(proposedMove) || moveShouldFollowSuitButDoesnt(proposedMove)) {
        return false;
    }

    return true;
}

bool BridgeGamestate::currentHandDoesNotHaveCard(const BridgeCard& proposedMove) const {

    auto currentCards = board[currentHand];

    if ( find( currentCards.begin(), currentCards.end(), proposedMove) == currentCards.end() ) {
        return true;    
    } else {
        return false;
    }
}


bool BridgeGamestate::moveShouldFollowSuitButDoesnt(const BridgeCard& proposedMove) const {
    
    //First card of a trick can be any suit
    if (currentTrickRecord.size() == 0) {
        return false;
    }


    auto currentCards = board[currentHand];

    const std::string leadSuit = currentTrickRecord[0].getSuit();

    if (proposedMove.getSuit() == leadSuit) {
        return false;
    }


    for (auto card : currentCards) {

        if (card.getSuit() == convertSuitIntToString(trumpSuit)) {
            return true;
        }
    }


    return false;
}






}
