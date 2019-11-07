#include "XOBoard.h"


using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector;



void XOBoard::playGame(){

    //Get starting blank board
    initialiseBoard();


    //Create game loop
    while(true){
        playerTurn();
        //Check if game is completed     
        if(won != 0) break;

        computerTurn();
        if(won != 0) break;
    }

    //Print the result of the game
    if(won == 2){
        cout << "ya lost" << endl;
    } else if (won == 1) {
        cout << "ya won" << endl;
    } else {
        cout <<"It's a cats game m8";
    }

    cout << "We are done...";

}


void XOBoard::makeMove(int Move){

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



void XOBoard::computerTurn(){

    //Computers turn

    //Here is where MCTS will be called


    //Generate random number and check if valid
    int rng = rand() % 9;
    while(invalid(rng) ){
        rng = rand() % 9;
    }

    makeMove(rng);
    printBoard();
    
    wonOrNot();
}


void XOBoard::playerTurn(){
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




void XOBoard::wonOrNot(){

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



bool XOBoard::invalid(int index){

    //If the index is OOB or the square has already been played then you can't play
    if(index == -1 || (index > 8 || board[index] != " ")){
        return true;
    }
    return false;
}



void XOBoard::initialiseBoard(){
    //Can probably just put space inside push_back statement...
    string space = " ";

    for(int i = 0; i != 9; i++){
        board.push_back(space);
    }
}


void XOBoard::printBoard(){

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
