#ifndef BridgeGamestate_h
#define BridgeGamestate_h

#include <map>
#include <string>


namespace Bridge {


 
const std::map<std::string, int> suitStringToIntMap(); 
const std::map<int, std::string> suitIntToStringMap(); 
const std::map<std::string, int> rankStringToIntMap(); 
const std::map<int, std::string> rankIntToStringMap(); 



}
#endif
