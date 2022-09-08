#include <gtest/gtest.h>

#include "models/bridgeMCTreeNode.hpp"


TEST(BridgeMCTreeNodeTests, DefaultConstructorTests) {
    
    using bNodeUniquePtr =  std::unique_ptr<Bridge::BridgeMCTreeNode>; 

    ASSERT_NO_THROW(bNodeUniquePtr baseNode = std::make_unique<Bridge::BridgeMCTreeNode>());

    bNodeUniquePtr baseNode = std::make_unique<Bridge::BridgeMCTreeNode>();

    ASSERT_NO_THROW(baseNode->makeMove("C","K"));
    ASSERT_NO_THROW(baseNode->makeMove("C","A"));
    ASSERT_NO_THROW(baseNode->makeMove("C","Q"));
    ASSERT_NO_THROW(baseNode->makeMove("C","J"));

}



TEST(BridgeMCTreeNodeTests, ParentPointerConstructorTests) {

    using bNodeUniquePtr =  std::unique_ptr<Bridge::BridgeMCTreeNode>; 

    bNodeUniquePtr baseNode = std::make_unique<Bridge::BridgeMCTreeNode>();

    ASSERT_NO_THROW( bNodeUniquePtr childNode = std::make_unique<Bridge::BridgeMCTreeNode>(baseNode.get()) ); 


    bNodeUniquePtr childNode = std::make_unique<Bridge::BridgeMCTreeNode>(baseNode.get());

    ASSERT_NO_THROW(childNode->makeMove("S","A"));

    ASSERT_NO_THROW(baseNode->makeMove("S","A"));
}



TEST(BridgeMCTreeNodeTests, ChildNodeCreationTests) {

    using nodeUniquePtr =  std::unique_ptr<MCTreeNode>; 

    nodeUniquePtr baseNode = std::make_unique<Bridge::BridgeMCTreeNode>();

    nodeUniquePtr childNode = std::make_unique<Bridge::BridgeMCTreeNode>(baseNode.get()); 

    baseNode->pushbackChildNode(std::move(childNode));

}

