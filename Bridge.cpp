#include <iostream>
#include <sstream>
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



////////////////////////////////
    //Converting functions
////////////////////////////////

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
        return 0;
    }  else if (dir == "E"){
        return 1;
    }  else if (dir == "S"){
        return 2;
    }  else if (dir == "W"){
        return 3;
    }

}






void Bridge::initialiseBoard(){


    won = turn = tricksMade_Dec = 0;

    //Initialise round_record_card
    for(int i = 0; i !=4; ++i){
        Card blank;
        round_record_card.push_back(blank);
    }

    //Initialise hands vector

    for(int i =0; i !=4; ++i){
        vector<Card> empty;
        hands.push_back(empty);
    }


    cout << "Input the current board state, " << endl;
    

   for(int i=0; i !=4; ++i){ //Iterate over the hands

        cout << "Please enter " << dir[i] << "'s hand, in order of decreasing suit rank: " << endl;

        for(int j=0; j !=4; ++j){ //Iterate over the suits

            
            cout<< "Enter next suit: ";


            string input;

            cin >> input;

            if(input != "n"){
                stringstream ss(input);
                string sub_str;

                while(getline(ss,sub_str,',')){
                    Card newCard(sub_str,suits[j]);  //Should probablt change -- pointless doubel conversion
                    hands[i].push_back(newCard);
                }
            }
        }
        cout<<"one hand done" <<endl;
        printBoard();
    }

    cout << endl;

    cout << "Please enter the contract with the level and trump suit seperated by a space: ";

    int forCalc;
    string forSuitDeterm;
    cin >> forCalc >> forSuitDeterm;

    tricksToWin = 6 + forCalc;

    trumpSuit = forSuitDeterm;

    
    //Get declarer direction
    string dir_str;

    cout << "Which hand belongs to the declarer? ";

    cin >> dir_str;

    declarer = get_dir(dir_str);

    //Get computer direction
    cout << "Which hand is controlled by the computer? ";

    cin >> dir_str;

    int dir_int = get_dir(dir_str);
    comp_dir.push_back(dir_int);
    //Also push back opposite direction
    comp_dir.push_back( dir_int + 2 < 4 ? dir_int + 2 : dir_int -2 );

}




void Bridge::wonOrNot(){

    //Check if required trick count is made
    if(tricksMade_Dec == tricksToWin){
        won = (comp_dir[0] == declarer || comp_dir[1] == declarer ? 2:1);
    }

    //If its impossible ot win from this state i.e. too few moves left
    if(13- turn/4 < (tricksToWin - tricksMade_Dec)){
        won = (comp_dir[0] == declarer || comp_dir[1] == declarer ? 1:2);
    }
}





void Bridge::makeMove(int move){

    int player = round_record_player.back();    
    //Update to next player unless on last player
    if(round_record_player.size() !=4){
        round_record_player.push_back( (player + 1 < 4) ? player + 1 : 0);
    }


    //corresponding to move from hand 
    Card played = hands[player][move];
    round_record_card.push_back(played);

    //update gamestate by removing card from hand
    hands[player].erase(hands[player].begin() + move);

    ++turn;
    
    //Required to flush round_record_card and keep track of tricks made
    if(turn%4 ==0){
       trickWinner();
    }
  
}


bool Bridge::invalid(int move){

    //if the first card in a round then trivially valid
    if(round_record_player.size() ==1){
        return true;
    }

    int player = round_record_player.back();
    int suit = round_record_card[0].suit;

    //Otherwise check if able to follow suit
    bool can_follow = false;
    for(vector<Card>::iterator card = hands[player].begin(); card != hands[player].end(); ++card){
        if(card->suit == suit){
            can_follow == true;
        }
    }

    //If unable to follow suit then any card is allowed
    if(!can_follow){
        return true;
    }

    if(hands[player][move].suit == suit){
        return true;
    }

    //If all the above tests fail the move is invalid
    return false; 
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




void Bridge::trickWinner(){
    //Looks at current play cache and determines winner
    
    Card best_card = round_record_card[0];
    int best_index = 0;

    for(int i = 1; i != 4; ++i){

        if(round_record_card[i].suit == best_card.suit || trumpSuit =="NT"){
            if(round_record_card[i] > best_card){
            best_card = round_record_card[i];
            best_index = i;
            }
        } else if(intToSuit(round_record_card[i].suit) == trumpSuit){
            best_card = round_record_card[i];
            best_index = i;
        }
    }    

    //Update based on trick winner
    if(round_record_player[best_index] == declarer || round_record_player[best_index +2 < 4 ? best_index + 2 : best_index - 2]){
        ++tricksMade_Dec;
    }


    //Need to flush round_record's
    for(int i =0; i != 4; ++i){
        round_record_card.pop_back();
        round_record_player.pop_back();
    }

    //Initialise next round
    round_record_player.push_back(best_index);
}





//////////////////////////////
    //All printing functions
//////////////////////////////



void Bridge::printBoard(){

    /* Example layout:
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

    //To hold hands for final print
    vector<string> hand_strs;

    vector< vector<string> > hand_str_preprocess;
    //Initialise vector
    for(int i = 0; i != 4; ++i){
        vector<string> empty;
        hand_str_preprocess.push_back(empty);
    }



    int maxlen_W = 12; //For formatting later
    int hand_counter = 0; //To check when on East



    for(vector< vector<Card> >::iterator iter = hands.begin(); iter != hands.end(); ++iter){

        vector<string> suit_strs;

        string S = "S  ";
        suit_strs.push_back(S);
        string H = "H  ";
        suit_strs.push_back(H);
        string D = "D  ";
        suit_strs.push_back(D);
        string C = "C  ";
        suit_strs.push_back(C);

        for(vector<Card>::iterator card = iter->begin(); card != iter->end(); ++card){
            
            suit_strs[card->suit] += (intToRank(card->rank) + " ");

        }


            //Get max length held in vector suit_strs for East
        for(vector<string>::iterator suit_str = suit_strs.begin(); suit_str != suit_strs.end(); ++suit_str){

            //Add this suits string to the preprocessors bit for that hand
            hand_str_preprocess[hand_counter].push_back(*suit_str); //segmentation error

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
    hand_strs.push_back(print_string_make(hand_str_preprocess[0],maxlen_W)); //N's hand
    hand_strs.push_back(print_string_make(hand_str_preprocess[3],0)); //Middle row with EW hands & played cards
    hand_strs.push_back(print_string_make(hand_str_preprocess[2],maxlen_W)); //S's hand

    

    //Output all the strings

    cout << hand_strs[0] << "\n" << hand_strs[1] <<
                "\n" << hand_strs[2];
    
    //Also need to make sure partially populated hands can be displayed CAN!
    //for the the line marked 8 with n bookmarks

}


void Bridge::EW_vectorstring_make(vector<string>& W_preprocessed, vector<string> E_preprocessed, int maxlen){

    //pad W strings to be same length
    for(vector<string>::iterator str = W_preprocessed.begin(); str != W_preprocessed.end(); ++str){
        string spaces((maxlen - str->length()),' ');
        *str += spaces;
    }

    //From specification at start of printBoard function
    string spaces7(7,' ');
    W_preprocessed[0] += spaces7;
    if(round_record_card[0].suit != -1){
        W_preprocessed[0] += (intToRank(round_record_card[0].rank) + intToSuit(round_record_card[0].suit));
    }

    W_preprocessed[2] += spaces7;
    if(round_record_card[2].suit != -1){ 
        W_preprocessed[2] += (intToRank(round_record_card[2].rank) + intToSuit(round_record_card[2].suit));
    }


    //Dealing with row 1
    string spaces5(5,' ');
    W_preprocessed[1] += spaces5;
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

    W_preprocessed[1] += spaces5;

    //Get length for padding

    int for_pad = W_preprocessed[1].size();

    //SHOULD MAKE FUNCTION FOR READABILITY SAKE
    //pad W strings to be same length
    for(vector<string>::iterator str = W_preprocessed.begin(); str != W_preprocessed.end(); ++str){
        string spaces_pad((for_pad - str->length()),' ');
        *str += spaces_pad;
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
        hand_str +=  (spaces + suit_strs[i] + "\n");
    }

    return hand_str;
}




