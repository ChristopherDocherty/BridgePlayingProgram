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

        //Required for controller (MCTS) functions
        std::string makeMoveMCTS(int validMoveNumber); 
        //Requried for view functions
        std::string makeMove(const std::string suit, const std::string rank);
        
        int getValidMoveCnt() const {return currentValidMoves.size();};

        boost::json::object getGamestateJson() const;


    private:

        static const int totalTurns = 13;

        std::vector<std::vector<BridgeCard>> board;

        int declarerHand;
        int currentLeadHand;
        int currentHand;

        int trumpSuit;
        int declarerTricksRequired;

        int currentTrick;
        int declarerTricksMade;

        std::vector<BridgeCard> currentTrickRecord;

        bool moveIsValid(const BridgeCard& proposedMove) const;
        bool currentHandDoesNotHaveCard(const BridgeCard& proposedMove) const; 
        bool moveShouldFollowSuitButDoesnt(const BridgeCard& proposedMove) const; 

        void updateCurrentValidMoves();
        std::vector<BridgeCard> currentValidMoves;


        int getTricksRequired(int contractLevel) const {return contractLevel + 6;};
        std::vector<std::vector<BridgeCard>> readBoardFromJson(boost::json::object& conf);


        int getTrickWinner() const;


};



}
#endif
