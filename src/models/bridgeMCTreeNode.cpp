#include "bridgeMCTreeNode.hpp"

#include <boost/json.hpp>

#include <fstream>
#include <sstream>
#include <string>

namespace Bridge {

//ctor for root node
BridgeMCTreeNode::BridgeMCTreeNode(const std::string& initialGamestateJsonFilepath) : MCTreeNode(nullptr) {

    std::string initialGamestateJson = loadGamestateJsonFromFile(initialGamestateJsonFilepath);

    setGamestate(initialGamestateJson);

}


BridgeMCTreeNode::BridgeMCTreeNode(MCTreeNode* parent) : MCTreeNode(parent) {

    std::string inheritedGamestate = parent->getGamestate();

    setGamestate(inheritedGamestate);

}



void BridgeMCTreeNode::notify() {

    std::string gamestateJsonString = getGamestateJsonString();  

    for (auto pObserver : observerList) {
        pObserver->update(gamestateJsonString);
    }

}


std::string BridgeMCTreeNode::loadGamestateJsonFromFile(const std::string& filepath) {

    std::ifstream jsonFile(filepath);
    std::stringstream buffer;
    buffer << jsonFile.rdbuf();

    return buffer.str();

}



void BridgeMCTreeNode::setGamestate(std::string gamestate) {

    auto gamestateJson = boost::json::parse(gamestate);

    pGamestate = std::make_unique<BridgeGamestate>(gamestateJson.as_object());

}



}
