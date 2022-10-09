#ifndef TERMVIEWUTILS_H
#define TERMVIEWUTILS_H

#include <boost/json.hpp>

#include <string>

namespace viewUtils {


std::vector<std::string> getSuits() { 

    const static std::vector<std::string> suits = {"S","H","D","C"};

    return suits;
}

std::string convertJsonToStr(boost::json::value& json) { return boost::json::value_to<std::string>(json); }

}

#endif
