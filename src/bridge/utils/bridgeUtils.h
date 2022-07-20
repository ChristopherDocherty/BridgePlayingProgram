#ifndef BridgeGamestate_h
#define BridgeGamestate_h

#include <string>


namespace Bridge {


const int convertSuitStringToInt(const std::string& suit);
const std::string convertSuitIntToString(const int suitInt); 
 

const int convertRankStringToInt(const std::string& rank); 
const std::string convertRankIntToString(const int rankInt); 


}
#endif
