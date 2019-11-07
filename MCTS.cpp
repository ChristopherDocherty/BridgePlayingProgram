#include <list>
#include <math.h>
#include "MCTS.h"


typedef MCTS::node node;


double node::getComparisonNum(int parentSimCount, double explor_param){

    return winCNT/visitCNT +
                 explor_param * sqrt(log(parentSimCount)/visitCNT);

}

node *MCTS::createChild(node* parentPTR){

    node* n = new node;

    parentPTR->OUT.push_back(n);

    n->IN = parentPTR;
}



node* Initialise(){

    
}





