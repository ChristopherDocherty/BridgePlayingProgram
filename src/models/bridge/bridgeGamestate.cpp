#include "bridgeGamestate.hpp"
#include "bridgeCard.hpp"
#include "utils/bridgeUtils.hpp"

#include <string>
#include <vector>



namespace Bridge {


BridgeGamestate::BridgeGamestate(boost::json::object& conf) :
    declarerHand( convertDirStringToInt(boost::json::value_to<std::string>(conf["declarer_dir"])) ), 
    currentLeadHand( convertDirStringToInt(boost::json::value_to<std::string>(conf["declarer_dir"])) ), 
    currentHand( convertDirStringToInt(boost::json::value_to<std::string>(conf["declarer_dir"])) ), 
    trumpSuit( convertSuitStringToInt(boost::json::value_to<std::string>(conf["trump_suit"])) ),
    declarerTricksRequired( getTricksRequired(boost::json::value_to<int>(conf["contract_level"])) )
{
    board = readBoardFromJson(conf);
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
  


}


