#ifndef GUARD_XOBoard_h
#define GUARD_XOBoard_h

//Header for for XOBoard class
#include <iostream>
#include <string>
#include <vector>


class XOBoard {
    public:
    void printBoard();
    void playGame();
    std::vector<int> moveset = {0,1,2,3,4,5,6,7,8};
    int won = 0;

    bool invalid(int);
    void wonOrNot();
    void makeMove(int);

    private:
    std::vector<std::string> board;
    std::vector< std::vector<int>> win_checks = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int turn = 0;

    void initialiseBoard();
    
    void playerTurn();
    void computerTurn();
};







#endif