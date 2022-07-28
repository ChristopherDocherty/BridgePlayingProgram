#include "bridgeUtils.h"

#include <string>
#include <sstream>
#include <map>



namespace Bridge {

const int convertSuitStringToInt(const std::string& suit) {
    
   const static std::map<std::string, int>  suitMap = {
       {"NT", 0},
       {"C", 1},
       {"D", 2},
       {"H", 3},
       {"S", 4}
    };

    if (suitMap.find(suit) == suitMap.end()) {
        throw std::invalid_argument("Invalid suit string entered");
    }; 

    return suitMap.at(suit);

}

const std::string convertSuitIntToString(const int suitInt) {
    
    const static std::map<int, std::string> suitMap = {
        {0, "NT"},
        {1, "C"},
        {2, "D"},
        {3, "H"},
        {4, "S"}
    }; 

    if (suitMap.find(suitInt) == suitMap.end()) {
        throw std::invalid_argument("Invalid suit string entered");
    }; 

    return suitMap.at(suitInt);
};            





const int convertRankStringToInt(const std::string& rank) {

    const static std::map<std::string, int> rankMap = {
        {"1", 1},
        {"2", 2},
        {"3", 3},
        {"4", 4},
        {"5", 5},
        {"6", 6},
        {"7", 7},
        {"8", 8},
        {"9", 9},
        {"10", 10},
        {"J", 11},
        {"Q", 12},
        {"K", 13},
        {"A", 14}
    }; 

    if (rankMap.find(rank) == rankMap.end()) {
        throw std::invalid_argument("Invalid rank string entered");
    }; 

    return rankMap.at(rank);

}


const std::string convertRankIntToString(const int rankInt) {
    
    const static std::map<int, std::string> rankMap = {
        {1, "1"},
        {2, "2"},
        {3, "3"},
        {4, "4"},
        {5, "5"},
        {6, "6"},
        {7, "7"},
        {8, "8"},
        {9, "9"},
        {10, "10"},
        {11, "J"},
        {12, "Q"},
        {13, "K"},
        {14, "A"}
    }; 

    if (rankMap.find(rankInt) == rankMap.end()) {
        throw std::invalid_argument("Invalid rank string entered");
    }; 

    return rankMap.at(rankInt);
};           



const int convertDirStringToInt(const std::string& dir) {

   const static std::map<std::string, int>  dirMap = {
       {"N", 1},
       {"E", 2},
       {"S", 3},
       {"W", 4}
    };

    if (dirMap.find(dir) == dirMap.end()) {
        throw std::invalid_argument("Invalid direction string entered");
    }; 

    return dirMap.at(dir);


}





const std::string convertDirIntToString(const int dirInt) {

    const static std::map<int, std::string> dirMap = {
        {1, "N"},
        {2, "E"},
        {3, "S"},
        {4, "W"}
    }; 

    if (dirMap.find(dirInt) == dirMap.end()) {
        throw std::invalid_argument("Invalid direction string entered");
    }; 

    return dirMap.at(dirInt);

}


const std::tuple<int, int> convertContractString(const std::string& contractString) {

    std::stringstream contractStream(contractString);

    int contractNumber; 
    std::string contractSuit; 

    contractStream >> contractNumber >> contractSuit;

    if (contractStream.fail()) {
        throw std::invalid_argument("Invalid contract string entered: first char must be an valid integer.");
    }

    int tricksRequired = contractNumber + 6;

    int trumpSuitInt = convertSuitStringToInt(contractSuit); 


    return std::make_tuple(trumpSuitInt, tricksRequired);


}


}
