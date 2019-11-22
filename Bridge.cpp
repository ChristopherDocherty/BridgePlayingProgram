#include <iostream>
#include <cstring>
#include <string>
#include <list>
#include <vector>
#include "Bridge.h"

using namespace std;




Bridge::Card::Card(string rank_str, int suit_int){
    //method to construct card by changing string card
    //specifiers to integers

    suit = suit_int;


    //First check if non integer rank string

    if(rank_str == "A"){
        rank = 14;
    } else if(rank_str == "K"){
        rank = 13;
    } else if(rank_str == "Q"){
        rank = 12;
    } else if(rank_str == "J"){
        rank = 11;
    } else {
        rank = stoi(rank_str);
    }

    //Currently no error catching is user enters invalid card
    //Program will crash

}


//Overloading > operator
bool operator>(const Bridge::Card &c1,const Bridge::Card &c2){
    return c1.rank  > c2.rank;
}
//NB just check suit before comparisons - will do in trick winning method




int Bridge::suittoI(string suit_str){

    if(suit_str == "NT"){
        return 5;
    } else if (suit_str == "S"){
        return 4;
    }  else if (suit_str == "H"){
        return 3;
    }  else if (suit_str == "D"){
        return 2;
    }  else if (suit_str == "C"){
        return 1;
    }

}

int Bridge::get_dir(string dir){

    if (dir == "N"){
        return 1;
    }  else if (dir == "E"){
        return 2;
    }  else if (dir == "S"){
        return 3;
    }  else if (dir == "W"){
        return 4;
    }

}






void Bridge::initialiseBoard(){


    won, turn, tricksMade_Dec = 0;


    cout << "Input the current board state, " << endl;


    vector<string> dir = {"N","E","S","W"};

   for(int i=0; i !=4; ++i){ //Iterate over the hands

        cout << "Please enter " << dir[i] << "'s hand, in order of decreasing suit rank: " << endl;

        for(int j=1; j !=4; ++j){ //Iterate over the suits

            
            cout<< "Enter next suit: ";


            string input;

            char* cstr = new char [input.length() +1];
            strcpy(cstr,input.c_str());

            char* p  = strtok(cstr,",");

            //Add all card instances to hand
            while(p != 0){
                string rank_str = string(p); //Might complain about p not being const
                Card newCard(p,5-j); 
                hands[i].push_back(newCard);
            }

        }

    }

    cout << endl;

    cout << "Please enter the contract with the level and trump suit seperated by a space: ";

    int forCalc;
    string forSuitDeterm;
    cin >> forCalc >> forSuitDeterm;

    tricksToWin = 6 + forCalc;

    int trumpSuit = suittoI(forSuitDeterm);

    //TODO
    //Display and give chance to check inbetween each hand population
    printBoard();
    

    //Get computer direction
    cout << "Which hand is controlled by the computer? ";

    string dir_str;

    cin >> dir_str;

    comp_dir = get_dir(dir_str);
    

    //Get declarer direction
    cout << "Which hand belongs ot the declarer? ";

    cin >> dir_str;

    declarer = get_dir(dir_str);


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

/* 
                   S  K Q 9 4
                   H  10 7 2
                   D  8 7 5
                   C  Q 9 8


    S  6 5             AS       S  J 7 3
    H  K Q J 5 4    10D  KC     H  9 3
    D  9               10S      D  K 6 4 3 2
    C  J 7 6 4                  C  10 2


                   S  A 8 2
                   H  A 8 6
                   D  A Q J 
                   C  A 5 3


Specifications to get above layout:

2 spaces inbetween suit and first card, one space inbetween each card

2 Carriage returns between N and E & W

5 Spaces inbetween rightmost E's rightmost card and E played card unless
10 card in which case only 4 spaces

5 Spaces to west as well (same exception for 10)

7 spaces between rightmost E card and N played card (likewise for S played card)

3 spaces inbetween rightmost E card and S,H etc. of N & S (likewise with W on other side)


*/


    //General plan is to make 5 substrings - one for each hand
    //plus one for the centre

    //concatenate for print string





    //Also need to bmake sure partially populated hands can be displayed 
    //for the the line marked 8 with n bookmarks

}




int Bridge::trickWinner(){

    //called every 4 turns
    //Looks at current play cache and determines winner
    //Store two lists: one of cards played and one of player {N,E,S,W}
    
    //initialise on first position and compare with next -- need to override > method
    //if bigger then redefine to the larger card's position

    //Return 1 or 2 depending on whose trick it is


}


