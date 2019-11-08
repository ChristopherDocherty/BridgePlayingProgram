#ifndef GUARD_MCTS_h
#define GUARD_MCTS_h

#include <list>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using std::vector; using std::list;
using std::cout; using std::cin;
using std::endl; using std::string;
using std::rand; using std::srand;
using std::time;



/* T must have the methods:
    T.won holds 0 if not ended or an integer depending on who won
    T.wonorNot() updates won with correct value
    T.playerTurn() lets player make a move
    T.makeMove() updaes a given state with the move passed in
    T.initialiseBoard() Puts a given gamestate into the starting position
*/



template <class T>
    class MCTS{

        public:

        //Node strcture for building statistics tree
        struct node{


            int visitCNT =0;
            int winCNT = 0;
            bool endgame = false;
            double exploreParam = 1.41;
            
            node* IN;
            std::list<node*> OUT;

            T localGamestate;

            //Methods
            double getComparisonNum(int parentSimCount);
        };


        node* root;
        T globalGamestate;

        //Constructor
        MCTS(); 

        //Methods    

        void Initialise();
        void playGame();

        T runMCTS();

        node* Selection(node*, std::vector<int>&);

        void ESV(node*);

        node* Expand(node*, T, int);
        int Simulate(T);
        void Update(node*, int result); //Might need ot remove recursion from this
        void cleanMemory();
    };






using namespace std;


template <class T>
MCTS<T>::MCTS(){}


template <class T>
void MCTS<T>::playGame(){

    //Create a new game state
    T newGame;
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
        T getUpdatedBoard = runMCTS();
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
        cout <<"It's a cats game";
    }

    cout << "We are done...";
}



template <class T>
void MCTS<T>::Initialise(){
    
    //Initialise the root node for this gamestate
    node* n = new node;
    n->IN = NULL;
    n->localGamestate = globalGamestate;

    root = n;
}




template <class T>
T MCTS<T>::runMCTS(){

    //Perform expansion to create first layer of child nodes
    ESV(root);

    //This is in place of a while loop with some time condition
    for(int counter=0; counter < 6000;counter++){



        vector<int> parentSimCount;
        //get count from root and add to vector
        int rootSimCount = root->visitCNT;
        parentSimCount.push_back(rootSimCount);


        node* selectedNode = Selection(root, parentSimCount);

        if(selectedNode == NULL){break;}

        ESV(selectedNode);

    }

     //Look at all children of node and select one with most simulations
     //just set the stat of the board to be this state
     //Return this state

    list<node*> child_list = root->OUT;

    int maxVisitCNT = -1;
    int maxWinCNT = -1;
    node* chosenPath;

    //find the most promising move
    for(typename list<node*>::const_iterator iter = child_list.begin(); iter != child_list.end(); ++iter){
        
        node* childNode = *iter;
        
        if(childNode->visitCNT >= maxVisitCNT){
            if(childNode->winCNT >maxWinCNT){
                maxVisitCNT = childNode->visitCNT;
                maxWinCNT = childNode->winCNT;
                chosenPath = childNode;
            }
        }
    }

    T nextMove = chosenPath->localGamestate;

    cleanMemory();


    return nextMove;
}

template <class T>
typename MCTS<T>::node* MCTS<T>::Selection(node* nodeSelec, vector<int>& parentSimCount){


    //Loop until terminal node is reached
    while(nodeSelec->OUT.size() != 0){


        //initialise for comparison with other nodes
        double maxValue = -5;
        node* bestChildptr;

        bool EndgameNode = true;

        //Iterate through all the out nodes
        for(typename list<node*>::const_iterator iter = nodeSelec->OUT.begin(); iter != nodeSelec->OUT.end(); ++iter){

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
            //As this ndoe was found to be invalid need to assign nodeSelec to its parent

            if(nodeSelec->IN == NULL){
                return NULL;
            }
            nodeSelec = nodeSelec->IN; 

        } else {
            /*If this node has a child that isn't at endgame then
              add this child's visitCNT to parentSimCount and
              reassign nodeSelec*/
           

            parentSimCount.push_back(bestChildptr->visitCNT);
            
            nodeSelec = bestChildptr;
        }
    }

    /*When the OUT vector is found to be empty this means the node is
      at the furthest outreach of the tree, this node (PTR) is then returned*/

    return nodeSelec;
}





template <class T>
void MCTS<T>::ESV(MCTS::node* psuedoroot){

    //Get the game state from parent
    T parentGstate = psuedoroot->localGamestate;

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
            T childGstate = newChild->localGamestate;
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

template <class T>
typename MCTS<T>::node* MCTS<T>::Expand(MCTS<T>::node* psuedoroot, T prevGstate, int move){ 

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
template <class T>
int MCTS<T>::Simulate(T childGamestate){

    //While not won
    while(childGamestate.won == 0){

        int move;
        bool valid = false;
        //Continue to generate random move choices until a valid move is found
        srand(time(NULL));
            while(valid == false){
            move = rand()%9;
            valid = !childGamestate.invalid(move);
        }
        childGamestate.makeMove(move);
        childGamestate.wonOrNot();

    }

    //Outside the loop means he end of the game has been reached return result
    return childGamestate.won;
}


template <class T>
void MCTS<T>::Update(MCTS<T>::node* outerNode, int result){

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


template <class T>
void MCTS<T>::cleanMemory(){
    //This starts after a search has occurred 
    //All the nodes need to be deleted in order to start over again
    //Need efficient way to traverse tree

    node* currentnode = root;
    
    while (root->OUT.size() != 0){   
        if (currentnode->OUT.size() !=0)
        {
            currentnode = currentnode->OUT.front();
        }
        else 
        {
            //set current node to parent node when terminus reached
            currentnode = currentnode->IN;
            
            //get the pointer from the start of list
            //then delete it
            node* ptrForDelete = currentnode->OUT.front();
            currentnode->OUT.pop_front();
            delete ptrForDelete;
        }
    }
}











template <class T>
double MCTS<T>::node::getComparisonNum(int parentSimCount){

    return winCNT/(double)visitCNT + exploreParam * sqrt(log(parentSimCount)/visitCNT);

}




#endif