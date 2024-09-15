#ifndef MCTREE_H
#define MCTREE_H

#include <chrono>
#include <ios>
#include <models/MCTreeNode.hpp>

#include <range/v3/algorithm/find.hpp>
#include <range/v3/algorithm/max_element.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/view/enumerate.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/sample.hpp>
#include <range/v3/view/transform.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <random>
#include <sstream>
#include <stdexcept>
#include <tuple>

namespace details {
float getComparisonNumber(int parentSimCnt, int childVisitCnt, int childWinCnt);
}  // namespace details

template <typename MCTS_GAME>
class MCTree {

 public:
  MCTree(MCTS_GAME game);
  int findBestMove();

 private:
  MCTreeNode<MCTS_GAME>* selectNode();
  void expandNode(MCTreeNode<MCTS_GAME>* node);
  int simulate(MCTreeNode<MCTS_GAME>* node);
  void backpropagateResult(MCTreeNode<MCTS_GAME>* node, bool winningSimulation);

  void dumpCurrentState(int iterations);

  static std::mt19937 s_rngEngine;

  std::unique_ptr<MCTreeNode<MCTS_GAME>> d_rootNode;
};

template <typename MCTS_GAME>
std::mt19937 MCTree<MCTS_GAME>::s_rngEngine{std::random_device{}()};

template <typename MCTS_GAME>
MCTree<MCTS_GAME>::MCTree(MCTS_GAME game)
    : d_rootNode(
          std::make_unique<MCTreeNode<MCTS_GAME>>(std::move(game), nullptr)) {}

template <typename MCTS_GAME>
int MCTree<MCTS_GAME>::findBestMove() {
  int i = 0;

  auto startTime = std::chrono::steady_clock::now();
  auto endTime = startTime + std::chrono::seconds(1);
  while (std::chrono::steady_clock::now() < endTime) {
    //  while (i < 100) {
    auto selectedNode = selectNode();
    //Don't attempt to expand if the selectedNode is already a end game scenario
    if(!selectedNode){
      continue;
    }
    expandNode(selectedNode);
    //Catch for when there is only one child so we don't simulate
    if (d_rootNode->children().size() == 1) {
      return i;
    }

    std::uniform_int_distribution<> dist{
        0, static_cast<int>(selectedNode->children().size() - 1)};
    size_t selectedChildIndex = dist(s_rngEngine);

    MCTreeNode<MCTS_GAME>* childNode =
        selectedNode->children()[selectedChildIndex];

    int result = simulate(childNode);

    bool computerWonSimulation = result == 0;
    backpropagateResult(childNode, computerWonSimulation);

    dumpCurrentState(i);
    ++i;
    if (i % 1000 == 0) {
      std::cout << i << " simulations done \n";
    }
  }

  std::vector<MCTreeNode<MCTS_GAME>*> children = d_rootNode->children();

  auto bestChild = ranges::max_element(
      children.begin(), children.end(),
      [](const MCTreeNode<MCTS_GAME>* lhs, const MCTreeNode<MCTS_GAME>* rhs) {
        return lhs->visitCnt() < rhs->visitCnt();
      });

  auto findBestChild =
      std::find_if(children.begin(), children.end(),
                   [bestChild](const MCTreeNode<MCTS_GAME>* node) {
                     return node == *bestChild;
                   });

  return findBestChild - children.begin();
}

template <typename MCTS_GAME>
MCTreeNode<MCTS_GAME>* MCTree<MCTS_GAME>::selectNode() {

  MCTreeNode<MCTS_GAME>* currNode = d_rootNode.get();

  while (!currNode->children().empty()) {
    std::vector<MCTreeNode<MCTS_GAME>*> children = currNode->children();

    //find any unexplored children
    auto unexploredChildren =
        children | ranges::views::filter([](const MCTreeNode<MCTS_GAME>* node) {
          return node->visitCnt() == 0;
        }) |
        ranges::to<std::vector>;

    if (!unexploredChildren.empty()) {
      return unexploredChildren.front();
    }

    if (ranges::all_of(currNode->children(),
                           [](MCTreeNode<MCTS_GAME>* childNode) {
                             return childNode->game().winner() != -1;
                           })) {
      return nullptr;
    }

    //If all explored, choose a next child
    auto nextChild =
        ranges::max_element(children, [parentSimCnt = currNode->visitCnt()](
                                          const MCTreeNode<MCTS_GAME>* lhs,
                                          const MCTreeNode<MCTS_GAME>* rhs) {
          return lhs->getComparisonNum(parentSimCnt) <
                 rhs->getComparisonNum(parentSimCnt);
        });

    currNode = *nextChild;
  }

  return currNode;
}

template <typename MCTS_GAME>
void MCTree<MCTS_GAME>::expandNode(MCTreeNode<MCTS_GAME>* node) {
  //Add children for each possible move

  MCTS_GAME baseGame = node->game();

  for (int move : baseGame.getAvailableMoves()) {

    MCTS_GAME childGame = baseGame;

    childGame.makeMove(move);

    std::unique_ptr<MCTreeNode<MCTS_GAME>> childNode =
        std::make_unique<MCTreeNode<MCTS_GAME>>(childGame, node);

    node->addChildNode(std::move(childNode));
  }
}

template <typename MCTS_GAME>
//TODO: THINK about type for winner
int MCTree<MCTS_GAME>::simulate(MCTreeNode<MCTS_GAME>* node) {

  MCTS_GAME game = node->game();

  while (!game.gameIsComplete()) {

    //TODO: think about type of move
    std::vector<int> availableMoves = game.getAvailableMoves();

    std::uniform_int_distribution<> dist{
        0, static_cast<int>(availableMoves.size() - 1)};
    size_t selectedChildIndex = dist(s_rngEngine);
    size_t chosenMove = availableMoves[selectedChildIndex];
    game.makeMove(chosenMove);
  }

  return game.winner();
}

template <typename MCTS_GAME>
void MCTree<MCTS_GAME>::backpropagateResult(MCTreeNode<MCTS_GAME>* node,
                                            bool computerWon) {
  while (node != nullptr) {
    if ((computerWon && node->isComputer()) ||
        (!computerWon && !node->isComputer())) {
      node->addWin();
    } else {
      node->addLoss();
    }
    node = node->parent();
  }
}

template <typename MCTS_GAME>
void MCTree<MCTS_GAME>::dumpCurrentState(int iterations) {
  auto children = d_rootNode->children();
  std::string output =
      children | ranges::views::enumerate |
      ranges::views::transform(
          [iterations, parentSimCnt = d_rootNode->visitCnt()](
              std::tuple<int, MCTreeNode<MCTS_GAME>*> enumChildNode) {
            auto& [childId, childNode] = enumChildNode;
            std::stringstream ss;
            ss << iterations << "|" << childId << "|" << childNode->visitCnt()
               << "|" << childNode->winCnt() << "|"
               << childNode->getComparisonNum(parentSimCnt) << "\n";
            return ss.str();
          }) |
      ranges::views::join | ranges::to<std::string>;

  std::fstream fout("data_dump.csv", std::ios_base::app);
  fout << output;
}

#endif
