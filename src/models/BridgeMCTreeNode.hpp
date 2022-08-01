#ifndef BridgeMCTreeNode_h
#define BridgeMCTreeNode_h

#include "MCTreeNode.hpp"
#include "bridge/bridgeGamestate.hpp"


class BridgeMCTreeNode : public MCTreeNode {


    public:

        //will be json for final thing
        std::string getGamestateJson();

        virtual void notify() override;

    private:

        BridgeGamestate gamestate;


}




#endif
