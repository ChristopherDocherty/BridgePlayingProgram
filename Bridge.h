#ifndef GUARD_Bridge_h
#define GUARD_Bridge_h

#include <vector>
#include <string>





class Bridge{

    public:

    struct Card{

        int suit;
        int rank;

        Card(std::string,std::string);

        int rankToInt(std::string);
        int suitToInt(std::string);
        
        friend bool operator> (const Card &c1,const Card &c2);
        friend bool operator== (const Card &c1,const Card &c2);

    };

    const std::vector<std::string> dir = {"N","E","S","W"};
    const std::vector<std::string> suits = {"S","H","D","C"};

    std::vector<std::vector<Card>> hands; //Vector contains N,E,S,W in that order

    int won;
    int turn;
    std::string trumpSuit;
    int tricksToWin;

    int tricksMade_Dec;

    std::vector<int> comp_dir;
    int declarer;


    
    std::vector<Card> round_record_card; //For determining winning card
    std::vector<int>  round_record_player; //For matching card to player and get next turn

    std::string intToRank(int);
    int rankToInt(std::string);
    std::string intToSuit(int);
    int get_dir(std::string);





    //MCTS specific methods
    void initialiseBoard();
    bool invalid(int);
    void makeMove(int);
    
    
    void printBoard();
    void EW_vectorstring_make(std::vector<std::string>&, std::vector<std::string>, int);
    std::string print_string_make(std::vector<std::string>, int);


    void playerTurn();
    void wonOrNot();
    
    //Bridge class specific methods
    void trickWinner(); 

};





#endif