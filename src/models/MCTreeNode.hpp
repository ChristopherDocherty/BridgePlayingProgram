#ifndef MCTreeNode_h
#define MCTreeNode_h

#include "ISubject.hpp"


class MCTreeNode : public ISubject {

    public:

        const float getComparisonNum(int parentSimCount);

    private:

        const static float exploreParam = 1.41;

        int visitCNT = 0;
        int winCNT = 0;
        
        const std::shared_ptr<MCTreeNode> parent;
        std::list<std::shared_ptr<MCTreeNode>> children;

};


#endif
