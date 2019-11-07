#include <list>
#include <math.h>
#include <vector>
#include "XOBoard.h"
#include "MCTS.h"

using std::vector; using std::list;




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


    //Probably need to call ESV() on the first node so I don't 
    //have divide by zero errors




    //This is in place of a while loop with some time condition
     for(int counter=0; counter < 1;counter++){


        vector<int> parentSimCount;
        //get count from root and add to vector
        int rootSimCount = root->visitCNT;
        parentSimCount.push_back(rootSimCount);


        node* selectedNode = Selection(root, parentSimCount);

        ESV(selectedNode);

     }

     //Look at all children of node and select one with most simulations
     //just set the stat of the board to be this state
     //Return this state



}


MCTS::node* MCTS::Selection(node* nodeSelec, vector<int>& parentSimCount){

    node n = *nodeSelec;

    //Check if this node is at the farthest reach of the tree
    if(n.OUT.size() != 0){

        //initialise for comparison with other nodes
        double maxValue = 0;
        node* bestChildptr;

        bool EndgameNode = true;

        //Iterate through all the out nodes
        for(list<node*>::const_iterator iter = n.OUT.begin(); iter != n.OUT.end(); ++iter){

            node* currentCheckNode = *iter;

            //CHECK FOR ENDGAME
            if(currentCheckNode->endgame == false){

                if(currentCheckNode->getComparisonNum(parentSimCount.back()) > maxValue){
                    //Mark this node as having a least one child that isn't in endgame
                    EndgameNode = false;
                    //Update the max value found 
                    maxValue = currentCheckNode->getComparisonNum(parentSimCount.back());
                    bestChildptr = currentCheckNode;
                }
            }
        }

        /*If after iteration all children are found to be endgame nodes
          so to muse be the current node
        */
        if(EndgameNode){
            nodeSelec->endgame = true;
            //Remove the current
            parentSimCount.pop_back;
            /*recursively call selection on the original parent so another
              branch can be explored*/
            Selection((nodeSelec->IN), parentSimCount);
        } else {
            /*If this node has a child that isn't at endgame then
              add this child's visitCNT to parentSimCount and
              pass into Selection()*/

            parentSimCount.push_back(bestChildptr->visitCNT);
            Selection(bestChildptr,parentSimCount);
        }
    }

    /*When the OUT vector is found to be empty this means the node is
      at the furthest outreach of the tree, this node (PTR) is then returned s.t.
      all the recursive calls return it all the way to the initial call of
      Selection()*/

    return nodeSelec;

    








}



void MCTS::ESV(MCTS::node* psuedoroot){


    //Get the game state from parent
    XOBoard parentGstate = psuedoroot->localGamestate;

    //initialise a counter for checking if endgame is reached
    int counter = 0;

    //Maybe think about making teh moveset an attribute of MCTS?
    //Iterate over the moveset
    for(vector<int>::const_iterator iter = parentGstate.moveset.begin();iter != parentGstate.moveset.end(); ++iter){

        int move = *iter;

        //If move is invalid just increment the counter
        if(parentGstate.invalid(move)){
            ++counter;
        } else{

            //if the move is valid, expand and make a child node
            //The board is updated in Expand()
            node* newChild = Expand(psuedoroot, parentGstate, move);

            //Check if the newChild is already in a winning state
            XOBoard childGstate = newChild->localGamestate;
            childGstate.wonOrNot(); //MAYBE MOVE THIS INTO EXPAND?
            if(childGstate.won != 0){
                /*If the newChild has finished the game
                  mark it as having done so and
                  call Update() to update the visit count for all lesser nodes
                  not sure if I should actually do that though... I think it's
                  technically a simulation so I should*/
                newChild->endgame = true;
                Update(newChild,childGstate.won); //Consider if I should do this or not!

            }
            
            /*If the childNode hasn't finished the game simulations must occur until
            the end*/
            else {

            //Simulate the rest of the game
            int result = Simulate(childGstate);

            //Update the results of the simulated game
            Update(newChild, result);
            }
        }
    }
    /* At this point all children will have been updated and now either
    a new node will be selected or the computers time is up and it has 
    to make it's move*/
}


MCTS::node* MCTS::Expand(MCTS::node* psuedoroot, XOBoard prevGstate, int move){ 

    MCTS::node* childNode = new MCTS::node;
        
    //Initialise new node
    childNode->IN = psuedoroot;
        
    //Validity has already been checked in ESV()
    //Will not affect gamestate of parent ndoe as a copy is passed in
    prevGstate.makeMove(move);
    childNode->localGamestate = prevGstate;

    //Update parent node's out vector
    psuedoroot->OUT.push_back(childNode);

    return childNode;        
}

        



//Need to take in a copy so changes aren't preserved
int MCTS::Simulate(XOBoard childGamestate){

    //While not won
    while(childGamestate.wonOrNot == 0){

        int move;
        bool valid = false;
        //Continue to generate random move choices until a valid move is found
        while(valid == false){
            //Monte Carlo!!!!!!

            valid = childGamestate.invalid(move);
        }
        childGamestate.makeMove(move);
        childGamestate.wonOrNot();

    }

    //Outside the loop means he end of the game has been reached return result
    return childGamestate.won;
}



void MCTS::Update(node* outerNode, int result){

    ++outerNode->visitCNT;

    //If result is the integer for comp winning increment win counter
    if(result ==2){
    ++outerNode->winCNT;
    }

    node n = *outerNode;

    if(n.IN != NULL){
        Update(n.IN,result);
    }
}





double MCTS::node::getComparisonNum(int parentSimCount){

    return winCNT/visitCNT +
                 exploreParam * sqrt(log(parentSimCount)/visitCNT);

}







