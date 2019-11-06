#include <iostream>
#include <string>
#include <vector>


using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector;


struct XOBoard {
    public:
    void populateBoard();
    void printBoard();

    private:
    std::vector<std::string> board;

};

void XOBoard::populateBoard(){

    cout << "wit do you want in here?";

    string temp;

    for(int i = 0; i != 9; i++){

        cin >> temp;
        board.push_back(temp);
        cout << "anuther" << endl;

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
            cout <<  " " << "|";
        }

    }
    

}



int main()
{

    XOBoard game1;

    game1.populateBoard();

    game1.printBoard();







    return 0;


}