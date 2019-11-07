#include <list>
#include <math.h>
#include "XOBoard.h"
#include "MCTS.h"




MCTS::MCTS(XOBoard currentGameState){

    //Given the board every time its the computers turn 
    globalGamestate = currentGameState;


    //Initialise the root node for this gamestate
    node* n = new node;
    n->IN = NULL;
    n->localGamestate = globalGamestate; 

    root = n;
}


XOBoard MCTS::runMCTS(){

    //This is in place of a while loop with some time condition
     for(int counter=0; counter < 1;counter++){

        node* selectedNode = Selection();

        ESV(selectedNode);

     }

     //Look at all children of node and select one with most simulations
     //just set the stat of the board to be this state
     //Return this state



}


MCTS::node* MCTS::Selection(){



}


void MCTS::ESV(MCTS::node* psuedoroot){


}


MCTS::node* MCTS::Expand(MCTS::node* psuedoroot){


}

//Need to take in a copy so changes aren't preserved
int MCTS::Simulate(XOBoard childGamestate){


}

void MCTS::Update(int result){


}







double MCTS::node::getComparisonNum(int parentSimCount, double explor_param){

    return winCNT/visitCNT +
                 explor_param * sqrt(log(parentSimCount)/visitCNT);

}


//I think this is now depreciated but will keep in this commit anyway
MCTS::node* MCTS::createChild(MCTS::node* parentPTR){

    MCTS::node* n = new MCTS::node;

    parentPTR->OUT.push_back(n);

    n->IN = parentPTR;
}






