#ifndef GUARD_MCTS_h
#define GUARD_MCTS_h

#include <list>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>

using std::vector; using std::list;
using std::cout; using std::cin;
using std::endl; using std::string;
using std::rand; using std::srand;



/* T must have the methods:
    T.won holds 0 if not ended or an integer depending on who won
    T.wonorNot() updates won with correct value
    T.playerTurn() lets player make a move
    T.makeMove() updaes a given state with the move passed in
    T.initialiseBoard() Puts a given gamestate into the starting position
    T.getValidMoves() returns vector<int> of available moveset
    T.getTurn() returns string indiciating player or comp turn
*/



template <class T>
    class MCTS{

        public:

        //Node strcture for building statistics tree
        struct node{


            int visitCNT =0;
            int winCNT = 0;
            double exploreParam = 1.41;
            
            node* IN;
            std::list<node*> OUT;

            T localGamestate;

            //Methods
            double getComparisonNum(int parentSimCount);
        };

        
        int computeTimeInterval = 35;

        node* root;
        T globalGamestate;

        //Constructor
        MCTS(); 

        //Methods    

        void Initialise();
        void playGame();

        T runMCTS();

        node* Selection(node*, std::vector<int>&);

        //Will return NULL unless a created state has won
        node* ESV(node*);

        node* Expand(node*, T, int);
        int Simulate(T);
        void Update(node*, int result); //Might need ot remove recursion from this
        void cleanMemory();
    };




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

        if(globalGamestate.getTurn() == "player"){
            
            globalGamestate.playerTurn();

            //Check if game is completed
            globalGamestate.wonOrNot();
            if(globalGamestate.won != 0) break;
        } else {
            cout << "Computer's turn!"<<endl;
            //Computers turn - makes decision through MCTS
            Initialise();
            T getUpdatedBoard = runMCTS();
            globalGamestate = getUpdatedBoard;
            globalGamestate.printBoard();
            globalGamestate.wonOrNot();
            if(globalGamestate.won != 0) break;
        }
    }

    //Print the result of the game
    if(globalGamestate.won == 2){
        cout << "Copmuter wins!" << endl;
    } else if (globalGamestate.won == 1) {
        cout << "You win!" << endl;
    } else {
        cout <<"It's a cats game" << endl;
    }

    cout << "\nEnd of program" << endl;
    system("pause"); 
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

    //pointer for a potential winning move
    node* potentialWin = NULL;

    //Perform expansion to create first layer of child nodes
    potentialWin = ESV(root);

    if(potentialWin != NULL){
        return potentialWin->localGamestate;
    }

    //Change simulation time depending on number of cards available to play
    //The more cards there are to play th more difficult the choice and hence
    //the more time that should be spent thinkning
    //currently just have copmutation time scale linearly with card count

    vector<int> moveset = globalGamestate.getValidMoves();
    int computeTime;
    if(moveset.size() == 1){
        computeTime = 1; //simlulating for one choice is redundant 
    } else if(moveset.size() < 8) {
        computeTime = computeTimeInterval/4 * moveset.size();
    } else {
        computeTime = computeTimeInterval * moveset.size();
    }
    
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

    //This is in place of a while loop with some time condition
    while(std::chrono::system_clock::now() - start < std::chrono::seconds(computeTime)){

        vector<int> parentSimCount;
        //get count from root and add to vector
        int rootSimCount = root->visitCNT;
        parentSimCount.push_back(rootSimCount);


        node* selectedNode = Selection(root, parentSimCount);

        //SHOUDL BE OKAY TO REMOVE
        //if(selectedNode == NULL){break;}

        potentialWin = ESV(selectedNode);
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
        node* bestChildptr = NULL;

        //Iterate through all the out nodes to find most suitable
        for(typename list<node*>::const_iterator iter = nodeSelec->OUT.begin(); iter != nodeSelec->OUT.end(); ++iter){

            node* currentCheckNode = *iter;

            if(currentCheckNode->getComparisonNum(parentSimCount.back()) > maxValue){  
                //Update the max value found 
                maxValue = currentCheckNode->getComparisonNum(parentSimCount.back());
                bestChildptr = currentCheckNode;
            }  
        }

        //Should be a one pass through the tree
        parentSimCount.push_back(bestChildptr->visitCNT);        
        nodeSelec = bestChildptr;
    }

    return nodeSelec;
}





template <class T>
typename MCTS<T>::node* MCTS<T>::ESV(MCTS::node* psuedoroot){

    //Get the game state from parent
    T parentGstate = psuedoroot->localGamestate;

    parentGstate.wonOrNot();

    //Can't keep trying to expand when teh given gamestate has already won
    if(parentGstate.won == 0){
        //Find the valid moves

        vector<int> moveset = parentGstate.getValidMoves();


        //Iterate over the moveset
        for(vector<int>::const_iterator iter = moveset.begin();iter != moveset.end(); ++iter){

            int move = *iter;


            //The board is updated in Expand()
            node* newChild = Expand(psuedoroot, parentGstate, move);

            //Check if the newChild is already in a winning state
            T childGstate = newChild->localGamestate;
            childGstate.wonOrNot(); 


            int result;
            //Only simulate if th result is not already known
            if(childGstate.won == 0){
                result = Simulate(childGstate);
            } else{
                result = childGstate.won;
            }

            //Update the results of the simulated game
            Update(newChild, result);

        }
    } else{
        Update(psuedoroot,parentGstate.won);
    }


        /* At this point all children will have been updated and now either
        a new node will be selected or the computers time is up and it has 
        to make it's move*/
    node* placeholderPTR = NULL;
    return placeholderPTR;
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

    string turn = childGamestate.getTurn();

    //While not won
    while(childGamestate.won == 0){

        //Get avaialable moveset
        vector<int> moveset = childGamestate.getValidMoves();
        int move_cnt = moveset.size();
        //seed RNG
        srand(time(NULL));
        int move = moveset[rand()%move_cnt];
        
        childGamestate.makeMove(move);
        childGamestate.wonOrNot();

    }
    return childGamestate.won;
}


template <class T>
void MCTS<T>::Update(MCTS<T>::node* outerNode, int result){

    ++outerNode->visitCNT;

    T gamestate = outerNode->localGamestate;

    //Updates node according to player who last played
    if(result == 1 && gamestate.getTurn() == "computer" || result == 2 && gamestate.getTurn() == "player" ){
    ++outerNode->winCNT;
    }


    if(outerNode->IN != NULL){
        Update(outerNode->IN,result);
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