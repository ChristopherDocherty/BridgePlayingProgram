#include <string>
#include <map>



namespace Bridge {

const int convertSuitStringToInt(const std::string& suit) {
    
   const static std::map<std::string, int>  suitMap = {
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




}
