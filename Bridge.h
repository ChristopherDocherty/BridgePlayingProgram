#ifndef GUARD_Bridge_h
#define GUARD_Bridge_h

#include <vector>
#include <string>





class Bridge{

    public:

    struct Card{

        int suit;
        int rank;

        Card(int,int);

        //method for overriding ">" operator
        //method for overriding "==" operator

    };


    std::vector<std::vector<int>> hands; //Vector contains N,E,S,W in that order

    int won;
    int turn;
    int trumpSuit; //1-4 for C-S with 0->NT
    int tricksToWin;

    int tricksMade_Dec;

    int compDir;
    int Delcarer;


    //Need to flush eveyr 4 turns!
    std::vector<Card> roundRecord_Card; //For determining winning card
    std::vector<Card> roundRecord_Dir; //For matching the winning card with a hand





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