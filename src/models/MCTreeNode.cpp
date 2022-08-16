#include "MCTreeNode.hpp"

#include <cmath>


float MCTreeNode::getComparisonNum(float parentSimCnt) {

        float winCntFloat = static_cast<float>(winCnt);
        float visitCntFloat = static_cast<float>(visitCnt);

        return winCntFloat/visitCntFloat + exploreParam * std::sqrt(std::log(parentSimCnt)/visitCntFloat); 
}
