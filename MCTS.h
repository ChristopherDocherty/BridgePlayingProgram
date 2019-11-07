#ifndef GUARD_node_h
#define GUARD_node_h

#include <list>
#include <math.h>
#include "XOBoard.h"





class MCTS{

    private:
    struct node{

        //Attributes
        int visitCNT =0;
        int winCNT = 0;
        bool endgame = false;

        //reference for parent node
        node* IN;
        //List of child nodes' references
        std::list<node*> OUT;
        //Current board layout
        XOBoard localGamestate;
    
        //Methods
        double getComparisonNum(int parentSimCount, double explor_param);

    };

    node* root;
    XOBoard globalGamestate;

    //Need to add a constructor to set globalGameState!!

    public:
    //Methods
    node* createRoot();
    node* createChild(node* parentPTR);

    /*This will be the main loop for MCTS which will run until it hits
    whatever th estop condition is - probably based on time
    */
    XOBoard runMCTS();



    //Initialise using XOBoard built in functions
    node* Initialise();
    node* Selection();

    void ESV();
    //Maybe put vv in ^^
    void setpsuedoRoot();
    node* psuedoRoot;

    void Expand();
    void Simulate();
    void Update();






};









#endif