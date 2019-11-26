#include <iostream>
#include <cstring>
#include <string>
#include <list>
#include <vector>
#include "Bridge.h"

using namespace std;




Bridge::Card::Card(string rank_str="-1", string suit_str="-1"){
    //method to construct card by changing string card
    //specifiers to integers

    suit = suitToInt(suit_str);
    rank = rankToInt(rank_str);

    //FOr default constructor both values will be -1

    //Currently no error catching is user enters invalid card
    //Program will crash
}



//Overloading > operator
bool operator>(const Bridge::Card &c1,const Bridge::Card &c2){
    return c1.rank  > c2.rank;
}
//NB just check suit before comparisons - will do in trick winning method



string Bridge::intToRank(int rank){

    if(rank == 14){
        return "A";
    } else if(rank == 13){
        return "K";
    } else if(rank == 12){
        return "Q";
    } else if(rank == 11){
        return"J";
    } else {
        return to_string(rank);
    }
}

int Bridge::rankToInt(string rank_str){
    
    if(rank_str == "A"){
        return 14;
    } else if(rank_str == "K"){
        return 13;
    } else if(rank_str == "Q"){
        return 12;
    } else if(rank_str == "J"){
        return 11;
    } else {
        return stoi(rank_str);
    }
}

string Bridge::intToSuit(int suit_int){

    if(suit_int == 0){
        return "S";
    } else if(suit_int == 1){
        return "H";
    } else if(suit_int == 2){
        return "D";
    } else if(suit_int == 3){
        return "C";
    } 

}

//Temporary measure until I leanr inheritance
int Bridge::Card::rankToInt(string rank_str){
    
    if(rank_str == "A"){
        return 14;
    } else if(rank_str == "K"){
        return 13;
    } else if(rank_str == "Q"){
        return 12;
    } else if(rank_str == "J"){
        return 11;
    } else {
        return stoi(rank_str);
    }
}

int Bridge::Card::suitToInt(string suit_str){

    if(suit_str == "S"){
        return 0;
    } else if(suit_str == "H"){
        return 1;
    } else if(suit_str == "D"){
        return 2;
    } else if(suit_str == "C"){
        return 3;
    } else {
        return -1;
    }
}

//May be redundant
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

    //Initialise round_record_card
    for(int i = 0; i !=4; ++i){
        Card blank;
        round_record_card.push_back(blank);
    }





    cout << "Input the current board state, " << endl;
    

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
                Card newCard(p,suits[j]);  //Should probablt change -- pointless doubel conversion
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

    trumpSuit = forSuitDeterm;

    //Display and give chance to check inbetween each hand population
    printBoard();
    

    //Get computer direction
    cout << "Which hand is controlled by the computer? ";

    string dir_str;

    cin >> dir_str;

    comp_dir = get_dir(dir_str);
    

    //Get declarer direction
    cout << "Which hand belongs to the declarer? ";

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
    return false; //temporary
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




int Bridge::trickWinner(){

    //called every 4 turns
    //Looks at current play cache and determines winner
    //Store two lists: one of cards played and one of player {N,E,S,W}
    
    //initialise on first position and compare with next -- need to override > method
    //if bigger then redefine to the larger card's position

    //Return 1 or 2 depending on whose trick it is

    return 9000; //temporary

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

2 spaces inbetween suit and first card, one space inbetween each card --DONE

2 Carriage returns between N and E & W

5 Spaces inbetween rightmost W's rightmost card and W played card unless
10 card in which case only 4 spaces //can implememt later//

5 Spaces to east as well (same exception for 10)

7 spaces between rightmost W card and N played card (likewise for S played card)

3 spaces inbetween rightmost W card and S,H etc. of N & S (likewise with W on other side)


*/


    //General plan is to make 5 substrings - one for each hand
    //plus one for the centre

    //Need to do middle row string first so that top row lenght is known

    //To hold hands for final print
    vector<string> hand_strs;

    vector< vector<string> > hand_str_preprocess;


    int maxlen_W = 0; //For formatting later
    int hand_counter = 0; //To check when on East



    for(vector< vector<Card> >::iterator iter = hands.begin(); iter != hands.end(); ++iter){

        vector<string> suit_strs;

        string C = "C  ";
        suit_strs.push_back(C);
        string D = "D  ";
        suit_strs.push_back(D);
        string H = "H  ";
        suit_strs.push_back(H);
        string S = "S  ";
        suit_strs.push_back(S);

        for(vector<Card>::iterator card = iter->begin(); card != iter->end(); ++card){
            
            suit_strs[card->suit] += (intToRank(card->rank) + " ");

        }


            //Get max length held in vector suit_strs for East
        for(vector<string>::iterator suit_str = suit_strs.begin(); suit_str != suit_strs.end(); ++suit_str){

            //Add this suits string to the preprocessors bit for that hand
            hand_str_preprocess[hand_counter].push_back(*suit_str);

            //When on West get max length
           if(hand_counter == 3){
                if(suit_str->length() > maxlen_W){
                    maxlen_W = suit_str->length();
                }
            }
        }

        ++hand_counter;
    }

    //For EW must be on same line so need ot comnbine differently
    //Aim to use same method as NS

    //Add cards played to east's preprocessing string
    //get EW vector strings -- saved in W as a side effect
    EW_vectorstring_make(hand_str_preprocess[3], hand_str_preprocess[1], maxlen_W);


    //Generate hand strings with given max distance
    
    //NS
    hand_strs[0] = print_string_make(hand_str_preprocess[0],maxlen_W);
    hand_strs[2] = print_string_make(hand_str_preprocess[0],maxlen_W);

    //EW
    hand_strs[1] = print_string_make(hand_str_preprocess[3],0);
    

    //Output all the strings

    cout << hand_strs[0] << "\n" << hand_strs[1] <<
                "\n" << hand_strs[2];
    
    //Also need to make sure partially populated hands can be displayed 
    //for the the line marked 8 with n bookmarks

}


void Bridge::EW_vectorstring_make(vector<string>& W_preprocessed, vector<string> E_preprocessed, int maxlen){

    //pad W strings to be same length
    for(vector<string>::iterator str = W_preprocessed.begin(); str != W_preprocessed.end(); ++str){
        string spaces((maxlen - str->length()),' ');
        *str += spaces;
    }

    //From specification at start of printBoard function
    string spaces(7,' ');
    W_preprocessed[0] += spaces;
    if(round_record_card[0].suit != -1){
        W_preprocessed[0] += (intToRank(round_record_card[0].rank) + intToSuit(round_record_card[0].suit));
    }

    W_preprocessed[2] += spaces;
    if(round_record_card[2].suit != -1){ 
        W_preprocessed[2] += (intToRank(round_record_card[2].rank) + intToSuit(round_record_card[2].suit));
    }


    //Dealing with row 1
    string spaces(5,' ');
    W_preprocessed[1] += spaces;
    if(round_record_card[1].suit != -1){ 
        W_preprocessed[1] += (intToRank(round_record_card[1].rank) + intToSuit(round_record_card[1].suit));
    } else {
        W_preprocessed[1] += "  ";
    }
    //Add space inbetween E & W played cards
    W_preprocessed[1] += "  ";

    //Add W played card if it exists
    if(round_record_card[3].suit != -1){ 
        W_preprocessed[1] += (intToRank(round_record_card[1].rank) + intToSuit(round_record_card[1].suit));
    } else {
        W_preprocessed[1] += "  ";
    }

    W_preprocessed[1] += spaces;

    //Get length for padding

    int for_pad = W_preprocessed[1].size();

    //SHOULD MAKE FUNCTION FOR READABILITY SAKE
    //pad W strings to be same length
    for(vector<string>::iterator str = W_preprocessed.begin(); str != W_preprocessed.end(); ++str){
        string spaces((for_pad - str->length()),' ');
        *str += spaces;
    }

    //Now to finally add wests cards
    for(int i =0; i != 4; ++i){
        W_preprocessed[i] += E_preprocessed[i];
    }

    //West now should be in desired form (without handling the case of 10's...)

}





string Bridge::print_string_make(vector<string> suit_strs, int maxlen){

    string hand_str;
    string spaces(maxlen,' '); //Make string holding maxlen spaces
    //CHeck this works when given 0

    for (int i = 0; i != suit_strs.size(); ++i){
        hand_str +=  (spaces + suit_strs[1] + "\n");
    }
}




