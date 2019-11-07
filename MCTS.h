#ifndef GUARD_node_h
#define GUARD_node_h

#include <list>
#include <math.h>
#include <vector>
#include "XOBoard.h"





class MCTS{

    private:
    public:
    //INtend this to be private but not now bcoz testing
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


    //Need to add a constructor to set globalGameState!!


    node* root;


    //NOW true PBLIC starts
    //Constructor
    MCTS(XOBoard currentGameState);



    XOBoard globalGamestate;

    //Methods
    node* createChild(node* parentPTR);

    /*This will be the main loop for MCTS which will run until it hits
    whatever th estop condition is - probably based on time
    */
    XOBoard runMCTS();



    node* Selection(node* nodeSelec, vector<int>&  paretnSimCount);

    void ESV(node*);

    node* Expand(node*);
    int Simulate(XOBoard);
    void Update(int result);






};









#endif