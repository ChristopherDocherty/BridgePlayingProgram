#include <iostream>
#include <cstring>
#include <string>
#include <list>
#include <vector>
#include "Bridge.h"
#include "MCTS.h"


using namespace std;


int main(){


    Bridge test;

    test.initialiseBoard();

    for(int i = 0; i != 5; ++i){
       test.playerTurn();
    }

    return 0;

}