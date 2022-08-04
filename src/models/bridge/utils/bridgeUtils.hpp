#ifndef BridgeUtils
#define BridgeUtils

#include <string>
#include <tuple>


namespace Bridge {


int convertSuitStringToInt(const std::string& suit);
const std::string convertSuitIntToString(const int suitInt); 
 

int convertRankStringToInt(const std::string& rank); 
const std::string convertRankIntToString(const int rankInt); 


int convertDirStringToInt(const std::string& dir);
const std::string convertDirIntToString(const int dirInt);


const std::tuple<int, int> convertContractString(const std::string& contractString); 

}
#endif
