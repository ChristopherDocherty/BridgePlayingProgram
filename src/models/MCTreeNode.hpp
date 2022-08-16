#ifndef MCTreeNode_h
#define MCTreeNode_h

#include "interfaces/ISubject.hpp"



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

    private:

        constexpr static float exploreParam = 1.41;

        int visitCnt = 0;
        int winCnt = 0;
        
        MCTreeNode* mpParent;
        std::list<std::unique_ptr<MCTreeNode>> children;

};



#endif
