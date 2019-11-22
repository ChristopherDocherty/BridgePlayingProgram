#ifndef GUARD_Bridge_h
#define GUARD_Bridge_h

#include <vector>
#include <string>





class Bridge{

    public:

    struct Card{

        int suit;
        int rank;

        Card(std::string,int);

        friend bool operator> (const Card &c1,const Card &c2);
        friend bool operator== (const Card &c1,const Card &c2);

    };


    const std::vector<std::string> dir = {"N","E","S","W"};

    std::vector<std::vector<Card>> hands; //Vector contains N,E,S,W in that order

    int won;
    int turn;
    int trumpSuit; //1-4 for C-S with 0->NT
    int tricksToWin;

    int tricksMade_Dec;

    int comp_dir;
    int declarer;


    //Need to flush eveyr 4 turns!
    std::vector<Card> roundRecord_Card; //For determining winning card
    std::vector<Card> roundRecord_Dir; //For matching the winning card with a hand

    int suittoI(std::string);
    int get_dir(std::string);





    //MCTS specific methods
    void initialiseBoard();
    bool invalid(int);
    void makeMove(int);
    void printBoard();
    void playerTurn();
    void wonOrNot();
    
    //Bridge class specific methods
    int trickWinner(); 


    






};





#endif