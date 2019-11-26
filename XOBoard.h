#ifndef GUARD_XOBoard_h
#define GUARD_XOBoard_h

#include <vector>
#include <iostream>
#include <string>
#include <ctime>

 
 class XOBoard{
    public:
    std::vector<int> moveset = {0,1,2,3,4,5,6,7,8};
    int won = 0;

    bool invalid(int);
    void wonOrNot();
    void makeMove(int);

    std::vector<std::string> board;
    std::vector<std::vector<int>> win_checks = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int turn = 0;

    void initialiseBoard();
    void printBoard();
    
    void playerTurn();
};


#endif