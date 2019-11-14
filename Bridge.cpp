#include "Bridge.h"





void Bridge::initialiseBoard(){


    //Takes in input from the user to fill current hands
    //Take in format:
    //Dealer S{2,5,K} H{4,6,10} ...
    //Display and give chance to check inbetween each hand population
    //Clockwise next player...
    //again...
    //again...

    //Enter the contract
    //Calculate number of tricks needed to win

    //Enter which player is the computer

    //All stored in attributes of class instance

}



void Bridge::wonOrNot(){

    //check attribute "tricks made" against win condition
    //return == result

}





void Bridge::makeMove(int move){

    //update gamestate by removing card 
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
    
    //initialise on first card in vector and compare with next -- need to override > method
    //if bigger then redefine to the larger card

    //


}


