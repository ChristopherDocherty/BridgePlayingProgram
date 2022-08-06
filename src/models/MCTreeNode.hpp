#ifndef MCTreeNode_h
#define MCTreeNode_h

#include "ISubject.hpp"



class MCTreeNode : public ISubject {

    public:

        MCTreeNode(MCTreeNode* parent) : mParent(parent) {};

        virtual ~MCTreeNode();

        void recordSimulationResult(bool wonSim) { 
            ++visitCnt;
            if (wonSim) {++winCnt;};
        };

        float getComparisonNum(float parentSimCount);

    private:

        constexpr static float exploreParam = 1.41;

        int visitCnt = 0;
        int winCnt = 0;
        
        MCTreeNode* mParent;
        std::list<std::unique_ptr<MCTreeNode>> children;

};



#endif
