#include "bridgeMCTreeNode.hpp"

#include <boost/json.hpp>

#include <string>
#include <fstream>
#include <sstream>

namespace Bridge {

//ctor for root node
BridgeMCTreeNode::BridgeMCTreeNode(const std::string& initialGamestateJsonFilepath) : MCTreeNode(nullptr) {

    boost::json::object initialGamestateJson = loadGamestateJsonFromFile(initialGamestateJsonFilepath);

    pGamestate = std::make_unique<BridgeGamestate>(initialGamestateJson);

}



BridgeMCTreeNode::BridgeMCTreeNode(BridgeMCTreeNode* parent) : MCTreeNode(parent) {

    pGamestate = std::make_unique<BridgeGamestate>(*(parent->pGamestate)); 

}



void BridgeMCTreeNode::notify() {

    std::string gamestateJsonString = getGamestateJsonString();  

    for (auto pObserver : observerList) {
        pObserver->update(gamestateJsonString);
    }

}





boost::json::object BridgeMCTreeNode::loadGamestateJsonFromFile(const std::string& filepath) {

    std::ifstream jsonFile(filepath);
    std::stringstream buffer;
    buffer << jsonFile.rdbuf();

    auto json = boost::json::parse(buffer.str());

    return json.as_object();
}










}
