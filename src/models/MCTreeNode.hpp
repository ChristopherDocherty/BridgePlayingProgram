#ifndef MCTreeNode_h
#define MCTreeNode_h

#include "interfaces/ISubject.hpp"

#include <list>
#include <memory>
#include <string>



class MCTreeNode : public ISubject {

    public:

        MCTreeNode() = delete;

        MCTreeNode(MCTreeNode* pParent) : mpParent(pParent) {};

        virtual ~MCTreeNode() {};

        void pushbackChildNode(std::unique_ptr<MCTreeNode> childNode) {children.push_back(std::move(childNode));};

        void recordSimulationResult(bool wonSim) { 
            ++visitCnt;
            if (wonSim) {++winCnt;};
        };

        float getComparisonNum(float parentSimCnt);

        virtual std::string getGamestate() = 0;
        virtual void setGamestate(std::string) = 0;
    

    private:

        constexpr static float exploreParam = 1.41; //TODO: refactor this to more appropriate place

        int visitCnt = 0;
        int winCnt = 0;
        
        MCTreeNode* mpParent;
        std::list<std::unique_ptr<MCTreeNode>> children;

};



#endif
