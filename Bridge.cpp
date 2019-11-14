#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Bridge.h"

using namespace std;




Bridge::Card::Card(int rank, int suit){


}



void Bridge::initialiseBoard(){


    won, turn, tricksMade_Dec = 0;


    cout << "Input the current board state, " << endl;


    vector<string> dir = {"N","E","S","W"};

   for(int i=0; i !=4; ++i){ //Iterate over the hands

        cout << "Please enter " << dir[i] << "'s hand: ";

        for(int j=1; j !=4; ++j){ //Iterate over the suits

            //get suit from cin

            //Make list<char> holding all the cards for this suit
            //If I can make a hash table/dictionary look-a-like
            //can simplify things a bit

            //End up with list<int>


            /*for(list<string>::const_iter rank = list<int>NAME.begin(); rank !=list<int>NAME.end(); ++ rank){

            Card newCard(*rank,suit); 

            hands[j].push_back(Card);

            }*/
        }

    }

    cout << endl;

    cout << "Please enter the contract with the level and trump suit seperated by a space: ";

    int forCalc;
    string forSuitDeterm;
    cin >> forCalc >> forSuitDeterm;

    tricksToWin = 6 + forCalc;

    //Use same method as in for loop (currently line 36) to turn
    //suit into integer


    //TODO
    //Display and give chance to check inbetween each hand population
    
    /*

    cout << "Which hand is controlled by the computer? ";

    cin >> something;

    f(something) gives number 1-4 indicating direction

    assign to attribute
    */

   /*

    cout << "Which hand belongs ot the declarer? ";

    cin >> something;

    f(something) gives number 1-4 indicating direction

    assign to attribute
   */
    

}



void Bridge::wonOrNot(){

    //check tricksMade_Dec == tricksToWin

    //If not satisified then check 13- turn//4 < (tricksToWin - tricksMade_Dec)
        //if this holds then not won
}





void Bridge::makeMove(int move){

    //update gamestate by removing card [OBJECT]
    //corresponding to move from hand 
    //Hand is determined by looking at %4 of 
    //turn counter

}


bool Bridge::invalid(int move){

    //Must follow suit
    //cache of cards played in current round kept
    //access first card

    //Iterate through all cards to see if able to follow suit
    //Everytime a card of lead suit is found add it to a temporary cache
//Extract lead suit from card object at the start of the vector
        //if cache is non empty:
        //Select random number from 0 to cache size (use vector)
        //if empty choose random number from 0 to hand size

}


void Bridge::playerTurn(){

    //Recieve input on which card to play from user
    //in format 10D , KH , 2S etc.
    //Create instance of card object using input
    //Check if in current hand - ask again if not -- need to override "==" method
    //From above method return an index to pass to valid move
    //Check if valid move - ask again if not -- call method

    //Update hand with new information

}



void Bridge::printBoard(){

    //Try and print in format similar to bridge hands 
    //For hand 1, calculate longest hand and add 1 for length
    //Then vertically list cards in each suit

    //For E W hands, seperate by 6 characters s.t. N S hands have buffer
    //Treat S as did N
    
    //Need to put the played cards out in the centre

}




int Bridge::trickWinner(){

    //called every 4 turns
    //Looks at current play cache and determines winner
    //Store two lists: one of cards played and one of player {N,E,S,W}
    
    //initialise on first position and compare with next -- need to override > method
    //if bigger then redefine to the larger card's position

    //Return 1 or 2 depending on whose trick it is


}


