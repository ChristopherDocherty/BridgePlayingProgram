#include <list>
#include <math.h>
#include <vector>
#include <string>
#include <random>
#include <cstdlib>
#include "MCTS_XO.h"

using std::vector; using std::list;
using std::cout; using std::cin;
using std::endl; using std::string;
using std::rand; using std::srand;
using std::time;


/* ///////////////////////////////////////////////
    Functions for noughts and crosses part of game
*/ ///////////////////////////////////////////////




void MCTS::XOBoard::makeMove(int Move){

    string XorO;

    //Set the marker to whomevers turn it is
    if(turn%2 == 0){
        XorO = "X";
    } else {
        XorO = "O";
    }

    ++turn;

    board[Move] = XorO;
}



void MCTS::XOBoard::playerTurn(){
    //Players turn
    cout << "Enter which square you want to play in :) ";
    
    int input;
    cin >> input;

    while(invalid(input)){
        cout << "ye canny dae that";
        cin >> input;
    }

    //Allowing the user to exit on their own accord
    if(input == -1){
        cout << "well alllllrighty then";
        won = 3;
        return;
    }
    
    //Add user's choice and print to screen

    makeMove(input);
    printBoard();

    wonOrNot();
}




void MCTS::XOBoard::wonOrNot(){

    for(int i = 0; i < win_checks.size(); i ++){

        if(board[win_checks[i][0]] == "X" && board[win_checks[i][1]] == "X" && board[win_checks[i][2]] == "X"){
            won = 1;
        } else if (board[win_checks[i][0]] == "O" && board[win_checks[i][1]] == "O" && board[win_checks[i][2]] == "O"){
            won = 2;
        }
    }

    int spaceCNT = 0;

    for(int i = 0; i != board.size(); i ++){
        if(board[i] == " "){
            spaceCNT++;
        }
    }

    if(spaceCNT == 0 && won == 0){
        won = 3;
    }
}



bool MCTS::XOBoard::invalid(int index){

    //If the index is OOB or the square has already been played then you can't play
    if(index == -1 || (index > 8 || board[index] != " ")){
        return true;
    }
    return false;
}



void MCTS::XOBoard::initialiseBoard(){
    //Can probably just put space inside push_back statement...
    string space = " ";

    for(int i = 0; i != 9; i++){
        board.push_back(space);
    }
}


void MCTS::XOBoard::printBoard(){

   /*
   The board will be displayed as shown below 
    x | O | O
    O | x | O
    O | O | x   
   */

    for(int i = 0; i != board.size(); i++){

        if(i%3 == 2){
            cout << board[i] << endl;
        }else{
            cout <<  board[i] << "|";
        }

    }
}



/* ///////////////////////////////////////////////
                Functions for MCTS
*/ ///////////////////////////////////////////////

MCTS::MCTS(){}

void MCTS::playGame(){

    //Create a new game state
    XOBoard newGame;
    newGame.initialiseBoard();
    globalGamestate = newGame;

    Initialise();


    //Create game loop
    while(true){
        globalGamestate.playerTurn();
        //Check if game is completed     
        if(globalGamestate.won != 0) break;

        //Computers turn - makes decision through MCTS
        Initialise();
        XOBoard getUpdatedBoard = runMCTS();
        globalGamestate = getUpdatedBoard;
        globalGamestate.printBoard();
        if(globalGamestate.won != 0) break;
    }

    //Print the result of the game
    if(globalGamestate.won == 2){
        cout << "ya lost" << endl;
    } else if (globalGamestate.won == 1) {
        cout << "ya won" << endl;
    } else {
        cout <<"It's a cats game m8";
    }

    cout << "We are done...";
}




void MCTS::Initialise(){
    
    //Initialise the root node for this gamestate
    node* n = new node;
    n->IN = NULL;
    n->localGamestate = globalGamestate;

    root = n;
}





MCTS::XOBoard MCTS::runMCTS(){

    //Perform expansion to create first layer of child nodes
    ESV(root);


    //This is in place of a while loop with some time condition
    for(int counter=0; counter < 200;counter++){

        if(counter == 19){
            cout<<counter<<endl;
        }


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

    list<node*> child_list = root->OUT;

    int maxVisitCNT = 0;
    node* chosenPath;

    //find the most promising move
    for(list<node*>::const_iterator iter = child_list.begin(); iter != child_list.end(); ++iter){
        
        node* childNode = *iter;
        
        if(childNode->visitCNT > maxVisitCNT){
            maxVisitCNT = childNode->visitCNT;
            chosenPath = childNode;
        }
    }

    return chosenPath->localGamestate;
}


MCTS::node* MCTS::Selection(node* nodeSelec, vector<int>& parentSimCount){


    if(nodeSelec == 0x0){
        cout<< "whyyyyyyy" << endl;
    }


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
            parentSimCount.pop_back();
            /*recursively call selection on the original parent so another
              branch can be explored*/
            Selection((nodeSelec->IN), parentSimCount);
        } else {
            /*If this node has a child that isn't at endgame then
              add this child's visitCNT to parentSimCount and
              pass into Selection()*/
           

            parentSimCount.push_back(bestChildptr->visitCNT);
            cout << bestChildptr << endl;
            cout << "pause" << endl;
            node* temp;
            temp = Selection(bestChildptr,parentSimCount);
            nodeSelec = temp;
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

    //If none of the moves were valid then the endgame is reached.
    //Might be unecessary but shouldn't hurt to be here
    if(counter == parentGstate.moveset.size()){
        psuedoroot->endgame = true;
    }

    }
    /* At this point all children will have been updated and now either
    a new node will be selected or the computers time is up and it has 
    to make it's move*/
}


MCTS::node* MCTS::Expand(MCTS::node* psuedoroot, MCTS::XOBoard prevGstate, int move){ 

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
int MCTS::Simulate(MCTS::XOBoard childGamestate){

    //While not won
    while(childGamestate.won == 0){

        int move;
        bool valid = false;
        //Continue to generate random move choices until a valid move is found
        srand(time(NULL));
            while(valid == false){
            //Monte Carlo!!!!!!
            move = rand()%9;
            valid = !childGamestate.invalid(move);
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







