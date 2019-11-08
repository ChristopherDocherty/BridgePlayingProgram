#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <list>
#include "MCTS.h"
#include "XOBoard.h"


using namespace std;





int main()
{
    MCTS<XOBoard> letsPlay;

    letsPlay.playGame();

    
    return 0;

}