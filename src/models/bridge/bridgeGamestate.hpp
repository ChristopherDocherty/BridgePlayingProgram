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
        void makeMoveMCTS(int validMoveNumber); 
        //Requried for view functions
        void makeMove(const std::string suit, const std::string rank);
        
        int getValidMoveCount() const {return currentValidMoves.size();};

        boost::json::object getGamestateJson() const;


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

        bool moveIsValid(const BridgeCard& proposedMove) const;
        bool currentHandDoesNotHaveCard(const BridgeCard& proposedMove) const; 
        bool moveShouldFollowSuitButDoesnt(const BridgeCard& proposedMove) const; 

        void updateCurrentValidMoves();
        std::vector<BridgeCard> currentValidMoves;


        int getTricksRequired(int contractLevel) const {return contractLevel + 6;};
        std::vector<std::vector<BridgeCard>> readBoardFromJson(boost::json::object& conf);

};



}
#endif
