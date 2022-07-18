#include "bridge/bridgeCard.h"

#include <iostream>


int main() {

    Bridge::BridgeCard c1("S","1");
    Bridge::BridgeCard c2("S","3");


    std::cout << (c1 > c2) << std::endl;
    std::cout << (c1 < c2) << std::endl;
    std::cout << (c2 > c1) << std::endl;

}
