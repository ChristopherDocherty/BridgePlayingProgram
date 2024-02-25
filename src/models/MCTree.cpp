#include "MCTree.hpp"

#include <cmath>

constexpr static float EXPLORE_PARAM = 1.41;

float details::getComparisonNumber(int parentSimCnt, int childVisitCnt,
                                   int childWinCnt) {
  float winCntFloat = static_cast<float>(childWinCnt);
  float visitCntFloat = static_cast<float>(childVisitCnt);

  return winCntFloat / visitCntFloat +
         EXPLORE_PARAM * std::sqrt(std::log(parentSimCnt) / visitCntFloat);
}
