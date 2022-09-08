#include "bridgeCard.hpp"
#include "bridgeGamestate.hpp"
#include "utils/bridgeUtils.hpp"

#include <algorithm>
#include <stack>
#include <string>
#include <vector>


namespace Bridge {


BridgeGamestate::BridgeGamestate(boost::json::object& conf) :
    declarerHand( convertDirStringToInt(boost::json::value_to<std::string>(conf["declarer_dir"])) ), 
    currentLeadHand( convertDirStringToInt(boost::json::value_to<std::string>(conf["current_lead_hand"])) ), 
    currentHand( convertDirStringToInt(boost::json::value_to<std::string>(conf["current_lead_hand"])) ), 
    trumpSuit( convertSuitStringToInt(boost::json::value_to<std::string>(conf["trump_suit"])) ),
    declarerTricksRequired( getTricksRequired(boost::json::value_to<int>(conf["contract_level"])) ),
    currentTrick( boost::json::value_to<int>(conf["current_trick"]) ),
    declarerTricksMade( boost::json::value_to<int>(conf["declarer_tricks_made"]) )
{
    board = readBoardFromJson(conf);
    
    updateCurrentValidMoves();
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
    gamestateJson["current_lead_hand"] = convertDirIntToString(currentLeadHand);
    gamestateJson["current_trick"] = currentTrick;
    gamestateJson["declarer_tricks_made"] = declarerTricksMade;
    
    
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
    } else if ( (totalTurns + 1 - currentTrick) < (declarerTricksRequired - declarerTricksMade)) {
        return "Defence";
    } else {
        return "";
    }
    //possibly simulate till the end
    //just do simple check of if there is only one valid card to play - no reason to go through the last obvious move
} 


std::string BridgeGamestate::makeMoveMCTS(int validMoveNumber) {
    BridgeCard cardPlayed = currentValidMoves[validMoveNumber];
    return makeMove(cardPlayed.getSuit(), cardPlayed.getRank());
} 


std::string BridgeGamestate::makeMove(const std::string suit, const std::string rank) {
    
    if (getWinner() != "") {
        //probably cahnge this to return something else
        //basically jsut want a catch so you can't keep changing the gamestate once the gme is done
        //but this logic may end up in the controller
        return getWinner(); 
    }
    
    BridgeCard move(suit, rank);

    if ( !moveIsValid(move)) {
        throw std::invalid_argument(boost::json::serialize(getGamestateJson())); //"This is an invalid move");
    } 


    auto iterToErase = std::find(board[currentHand].begin(), board[currentHand].end(), move);
    board[currentHand].erase(iterToErase);

    currentTrickRecord.push_back(move);

    if (currentTrickRecord.size() == 4) {

        ++currentTrick;

        const int trickWinnerDir = getTrickWinner();

        currentHand = trickWinnerDir;
        currentLeadHand = trickWinnerDir;


        //Declarer wins trick if they or the dummy wins, hence %2
        if ( trickWinnerDir % 2 == declarerHand % 2) {
            ++declarerTricksMade;
        }

    } else {
        currentHand = (currentHand + 1) % 4;
    }

    updateCurrentValidMoves();

    return getWinner(); 

}


int BridgeGamestate::getTrickWinner() const {

    BridgeCard bestCard = currentTrickRecord[0];
    int bestCardDir = currentLeadHand;

    for (size_t i = 1; i != currentTrickRecord.size(); ++i) {
        
        auto currentCard = currentTrickRecord[i];

        if (currentCard.getSuit() == bestCard.getSuit() && currentCard> bestCard) {
            bestCard = currentCard;
            bestCardDir = (currentLeadHand + i) % 4;
        } else if (currentCard.getSuit() != bestCard.getSuit() && currentCard.getSuit() == convertSuitIntToString(trumpSuit)) {
            bestCard = currentCard;
            bestCardDir = (currentLeadHand + i) % 4;
        }
    }

    return bestCardDir;
}




void BridgeGamestate::updateCurrentValidMoves() {

    currentValidMoves.clear();

    auto currentCards = board[currentHand];


    for (auto card : currentCards) {
        if (moveIsValid(card)) {
            currentValidMoves.push_back(card);
        }
    }

}




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

        if (card.getSuit() == leadSuit) {
            return true;
        }
    }


    return false;
}






}
