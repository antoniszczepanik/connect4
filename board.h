#include <limits>

constexpr char ODD_SYMBOL = 'X';
constexpr char EVEN_SYMBOL = 'O';
constexpr long long LL1 = 1;
constexpr int INF = std::numeric_limits<int>::max();
constexpr int NEG_INF = std::numeric_limits<int>::min();
constexpr int SEARCH_DEPTH = 9;

typedef long long bitboard;


class Board {
    public:
        bool isWin(bitboard board);
        void makeMove(int column, bool print=false);
        void undoMove();
        void getMoves(bool* available); // Get all possible moves
        int getValue(); // Get current board value
        int getNextMove(); // Get next "best" optimal move
        int miniMax(int depth, bool isEvenPlayer, bool returnIndex); // FUN
        int minMax(int depth); // Get next best move with minMax algorithm
        void printMoves();
        void printBoard();
    private:
        bitboard boards[2] = {0, 0}; // Two seperate boards for O and X
        int heights[7] = {0, 7, 14, 21, 28, 35, 42}; // how high is each
        int counter = 0; // Move counter to quickly distinquish between players
        int moves[42];
};
