#ifndef BridgeGamestate_h
#define BridgeGamestate_h

#include "bridgeCard.hpp"

#include <string>
#include <vector>

#include <boost/json.hpp>



namespace Bridge {

class BridgeGamestate {
    

    public:

        BridgeGamestate(boost::json::object& conf);

        std::string getWinner(); 

        //the instance of this a node holds will be ocnstant but is copied for making a new move and then maybe const cast?
        int makeMove(); //rc to indicate if move successful
        
        std::vector<int> getCurrentValidMoves();

        boost::json::object getGamestateJson();


    private:

        static const int totalTurns = 13;

        std::vector<std::vector<BridgeCard>> board;

        const int declarerHand;
        const int currentLeadHand;
        const int currentHand;

        const int trumpSuit;
        const int declarerTricksRequired;

        int currentTrick = 1;
        int declarerTricksMade = 0;

        std::vector<BridgeCard> currentTrickRecord;

        bool moveIsValid(int move);
        std::vector<int> currentValidMoves;

        int getTricksRequired(int contractLevel) {return contractLevel + 6;};
        std::vector<std::vector<BridgeCard>> readBoardFromJson(boost::json::object& conf);

    
};



}
#endif
