#ifndef MCTreeNode_h
#define MCTreeNode_h

#include <functional>
#include <includes/range-v3/range/v3/all.hpp>

#include <memory>
#include <string>
#include <vector>
#include "range/v3/view/transform.hpp"

template <typename MCTS_GAME>
class MCTreeNode {

 public:
  MCTreeNode(MCTreeNode* parent, MCTS_GAME game);

  void addChildNode(std::unique_ptr<MCTreeNode> childNode);
  void recordSimulationResult(bool wonSim);
  float getComparisonNum(float parentSimCnt);

  MCTS_GAME game() const;

  int visitCnt() const;
  int winCnt() const;

  MCTreeNode* parent() const;

  void addWin();
  void addLoss();

  std::vector<MCTreeNode<MCTS_GAME>*> children();

 private:
  MCTS_GAME d_game;

  int d_visitCnt = 0;
  int d_winCnt = 0;

  MCTreeNode* d_parent;
  std::vector<std::unique_ptr<MCTreeNode>> d_children;
};

template <typename MCTS_GAME>
MCTreeNode<MCTS_GAME>::MCTreeNode(MCTreeNode* parent, MCTS_GAME game)
    : d_parent(parent), d_game(game) {}

template <typename MCTS_GAME>
MCTS_GAME MCTreeNode<MCTS_GAME>::game() const {
  return d_game;
}

template <typename MCTS_GAME>
std::vector<MCTreeNode<MCTS_GAME>*> MCTreeNode<MCTS_GAME>::children() {
  std::vector<MCTreeNode<MCTS_GAME>*> ret;

  for (auto& child : d_children) {
    ret.pushback(child.get());
  }

  return ret;
}

template <typename MCTS_GAME>
int MCTreeNode<MCTS_GAME>::visitCnt() const {
  return d_visitCnt;
}

template <typename MCTS_GAME>
int MCTreeNode<MCTS_GAME>::winCnt() const {
  return d_winCnt;
}

template <typename MCTS_GAME>
MCTreeNode<MCTS_GAME>* MCTreeNode<MCTS_GAME>::parent() const {
  return d_parent;
}

template <typename MCTS_GAME>
void MCTreeNode<MCTS_GAME>::addWin() {
  ++d_winCnt;
  ++d_visitCnt;
}
template <typename MCTS_GAME>
void MCTreeNode<MCTS_GAME>::addLoss() {
  d_visitCnt;
}

template <typename MCTS_GAME>
void MCTreeNode<MCTS_GAME>::addChildNode(
    std::unique_ptr<MCTreeNode> childNode) {
  d_children.push_back(std::move(childNode));
};

template <typename MCTS_GAME>
void MCTreeNode<MCTS_GAME>::recordSimulationResult(bool wonSim) {
  ++d_visitCnt;
  if (wonSim) {
    ++d_winCnt;
  };
}

#endif
