#ifndef MCTREE_H
#define MCTREE_H

#include "models/MCTreeNode.hpp"
#include "range/v3/view/sample.hpp"
#include "range/v3/view/transform.hpp"

#include <includes/range-v3/range/v3/all.hpp>

#include <algorithm>
#include <iterator>
#include <memory>
#include <random>

namespace details {
float getComparisonNumber(int parentSimCnt, int childVisitCnt, int childWinCnt);
}  // namespace details

template <typename MCTS_GAME>
class MCTree {

 public:

  int findBestMove(MCTS_GAME game);

 private:

  MCTreeNode<MCTS_GAME>* selectNode();
  void expandNode(MCTreeNode<MCTS_GAME>* node);
  int simulate(MCTreeNode<MCTS_GAME>* node);
  void backpropagateResult(MCTreeNode<MCTS_GAME>* node, bool winningSimulation);

  std::unique_ptr<MCTreeNode<MCTS_GAME>> d_rootNode;
};

template <typename MCTS_GAME>
MCTreeNode<MCTS_GAME>* MCTree<MCTS_GAME>::selectNode() {

  MCTreeNode<MCTS_GAME>* currNode = d_rootNode.get();

  while (currNode->children().empty()) {
    std::vector<MCTreeNode<MCTS_GAME>*> children = currNode->children();

    //find any unexplored children
    auto unexploredChildren =
        children | ranges::views::filter([](const MCTreeNode<MCTS_GAME>* node) {
          return node->visitCnt() == 0;
        }) |
        ranges::to<std::vector>;

    if (!unexploredChildren.empty()) {
      return unexploredChildren.first();
    }

    //If all explored, choose a next child
    auto nextChild = ranges::max_element(
        children,
        [](const MCTreeNode<MCTS_GAME>* lhs, const MCTreeNode<MCTS_GAME>* rhs) {
          //TODO check this
          return lhs->getComparisonNumber() < rhs->getComparisonNumber();
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
        std::make_unique(node, childGame);

    node->addChildNode(std::move(childNode));
  }
}

template <typename MCTS_GAME>
//TODO: THINK about type for winner
int MCTree<MCTS_GAME>::simulate(MCTreeNode<MCTS_GAME>* node) {

  MCTS_GAME game = node->game();

  while (!game.over()) {

    //TODO: think about type of move
    std::vector<int> nextMove{};
    //TODO: probably inefficient to do this
    ranges::views::sample(game.getAvailableMoves(),
                          std::back_inserter(nextMove), 1,
                          std::mt19937{std::random_device{}()});

    game.makeMove(nextMove.front());
  }

  return game.winner();
}

template <typename MCTS_GAME>
void MCTree<MCTS_GAME>::backpropagateResult(MCTreeNode<MCTS_GAME>* node,
                                            bool winningSimulation) {
  while (node != d_rootNode) {
    if (winningSimulation) {
      node->addWin();
    }
    node->addLoss();

    node = node->parent();
  }
}

#endif
