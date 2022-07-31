#ifndef MCTSGame_h
#define MCTSGame_h


class MCTSGame{

    public:

        MCTSGame(); 

        void playGame();


        virtual std::shared_ptr<node> getRootNode() = 0; 
        virtual void hasWon() = 0;
        virtual void getTurn() = 0; 
        virtual void makeMove() = 0;
        virtual void getValidMoves() = 0;
        virtual void playerTurn() = 0;

        //Expect that a method to simluate till end would be useful




    private:
        
        int computeTimeInterval = 35;
        std::shared_ptr<node> root;



        void Initialise();

        T runMCTS();

        std::shared_ptr<node> Selection(std::shared_ptr<node>, std::vector<int>&);

        //Will return NULL unless a created state has won
        std::shared_ptr<node> ESV(std::shared_ptr<node>);

        std::shared_ptr<node> Expand(std::shared_ptr<node>, T, int);
        int Simulate(T);
        void Update(std::shared_ptr<node>, int result); //Might need ot remove recursion from this
        void cleanMemory();

};

#endif
