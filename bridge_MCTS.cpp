#include <iostream>
#include <cstring>
#include <string>
#include <list>
#include <vector>
#include "Bridge.h"
#include "MCTS.h"


using namespace std;


int main(){

    MCTS<Bridge> test;

    test.playGame();

    return 0;

}