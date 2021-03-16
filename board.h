constexpr char ODD_SYMBOL = 'X';
constexpr char EVEN_SYMBOL = 'O';
constexpr long long LL1 = 1;

typedef long long bitboard;

class Board {
    public:
        bool isWin(bitboard board);
        void makeMove(int column);
        void undoMove();
        void getMoves(bool* available); // Get all possible moves
//        int evaluateBoard();
//        int minMax(int depth); // Get next best move with minMax algorithm
        void printMoves();
        void printBoard();
    private:
        bitboard boards[2] = {0, 0}; // Two seperate boards for O and X
        int heights[7] = {0, 7, 14, 21, 28, 35, 42}; // how high is each
        int counter = 0; // Move counter to quickly distinquish between players
        int moves[42];
};
