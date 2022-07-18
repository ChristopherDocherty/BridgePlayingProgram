#include <string>
#include <map>



namespace Bridge {

const std::map<std::string, int> suitStringToIntMap() {

   const static std::map<std::string, int>  suitStringToInt = {
       {"C", 1},
       {"D", 2},
       {"H", 3},
       {"S", 4}
    };

   return suitStringToInt;
};



const std::map<int, std::string> suitIntToStringMap() {
    
    const static std::map<int, std::string> suitIntToString = {
        {1, "C"},
        {2, "D"},
        {3, "H"},
        {4, "S"}
    }; 

    return suitIntToString;
};            


const std::map<std::string, int> rankStringToIntMap() {

    const static std::map<std::string, int> rankStringToInt = {
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

    return rankStringToInt;
};



const std::map<int, std::string> rankIntToStringMap() {
    
    const static std::map<int, std::string> rankIntToString = {
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

    return rankIntToString;
};           




}
