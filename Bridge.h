#ifndef GUARD_Bridge_h
#define GUARD_Bridge_h







class Bridge{

    public:



    //MCTS specific methods
    void initialiseBoard();
    bool invalid(int);
    void makeMove(int);
    void printBoard();
    void playerTurn();
    void wonOrNot();
    
    //Bridge calss specifici methods
    int trickWinner(); 


    






};





#endif