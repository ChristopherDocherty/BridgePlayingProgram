#ifndef GUARD_MCTS_XO_h
#define GUARD_MCTS_XO_h

#include <list>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>



/* ///////////////////////////////////////////////
    Noughts and crosses part
*/ ///////////////////////////////////////////////






/* ///////////////////////////////////////////////
    Monte Carlo Search Tree part
*/ ///////////////////////////////////////////////





struct MCTS{


    //Must define game inside MCTS
    class XOBoard{
    public:
    void printBoard();
    void playGame();
    std::vector<int> moveset = {0,1,2,3,4,5,6,7,8};
    int won = 0;

    bool invalid(int);
    void wonOrNot();
    void makeMove(int);

    std::vector<std::string> board;
    std::vector< std::vector<int>> win_checks = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int turn = 0;

    void initialiseBoard();
    
    void playerTurn();
    };


    //Node strcture for building statistics tree
    struct node{
        //Attributes
        int visitCNT =0;
        int winCNT = 0;
        bool endgame = false;
        double exploreParam = 1.41;

        //reference for parent node
        node* IN;
        //List of child nodes' references
        std::list<node*> OUT;
        //Current board layout
        XOBoard localGamestate;
    
        //Methods
        double getComparisonNum(int parentSimCount);
    };

    node* root;
    XOBoard globalGamestate;


    //Constructor
    MCTS(); //Does nothing

    //Methods    

    void Initialise();
    void playGame();

    XOBoard runMCTS();

    node* Selection(node*, std::vector<int>&);

    void ESV(node*);

    node* Expand(node*, XOBoard, int);
    int Simulate(XOBoard);
    void Update(node*, int result);
};

#endif