#ifndef MCTreeNode_h
#define MCTreeNode_h



class MCTreeNode{

    public:

        //static method??
        const float getComparisonNum(int parentSimCount);

    private:

        const static float exploreParam = 1.41;

        int visitCNT = 0;
        int winCNT = 0;
        
        const std::shared_ptr<node> parent;
        std::list<std::shared_ptr<node>> children;

};


class BridgeMCTreeNode : public MCTreeNode {

    public:

       //gamestate ptr 


    private:

        std::shared_ptr<BridgeGamestate> gamestate;

            

}







#endif
