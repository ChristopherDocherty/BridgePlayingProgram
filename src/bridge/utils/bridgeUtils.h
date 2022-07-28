#ifndef BridgeUtils
#define BridgeUtils

#include <string>


namespace Bridge {


const int convertSuitStringToInt(const std::string& suit);
const std::string convertSuitIntToString(const int suitInt); 
 

const int convertRankStringToInt(const std::string& rank); 
const std::string convertRankIntToString(const int rankInt); 


const int convertDirStringToInt(const std::string& dir);
const std::string convertDirIntToString(const int dirInt);


const std::tuple<int, int> convertContractString(const std::string& contractString); 

}
#endif
