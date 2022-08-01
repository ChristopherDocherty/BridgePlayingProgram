#ifndef BridgeGamestate_h
#define BridgeGamestate_h

#include "bridgeCard.hpp"

#include <string>
#include <vector>



namespace Bridge {


//for quick dev use 
struct BoardConf {

    //card string should be of the form "[suit] [cards]" e.g. "S 10,J,K"
    std::vector<std::string> northHand;
    std::vector<std::string> eastHand;
    std::vector<std::string> southHand;
    std::vector<std::string> westHand;

    //should be in the form "[number] [suit]" e.g. "4 S"
    std::string contractString;
    std::string declarerDirection;

    std::string delimiter = ","; 

};



class BridgeGamestate {
    

    public:

        //TODO: Need to add version of this constructor that takes no arguments 
        //so that user input can be used instead
        BridgeGamestate(const BoardConf& conf);
        

        std::string getWinner(); 

        //the instance of this a node holds will be ocnstant but is copied for making a new move and then maybe const cast?
        int makeMove(); //rc to indicate if move successful
        
        std::vector<int> getCurrentValidMoves();

        void printBoard();
        void printContractInfo();


    private:

        static const int totalTurns = 13;

        //HAve to come back here and decouple BridgeCard - perhaps using pimpl
        std::vector<std::vector<BridgeCard>> hands;

        const int declarerHand;
        const int currentLeadHand;
        const int currentHand;

        const int trumpSuit;
        const int declarerTricksRequired;

        int currentTrick = 1;
        int declarerTricksMade = 0;

        std::vector<BridgeCard> currentTrickRecord;

        std::vector<int> currentValidMoves;


        const bool moveIsValid(int move);

        std::vector<std::vector<BridgeCard>> getBoard(const std::vector<std::vector<std::string>>& handStrings, const std::string& delimiter);
        //abstract the reading of a hand away into some private function
    
};



}
#endif
