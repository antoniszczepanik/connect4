#include <limits>
#include <utility>

constexpr char ODD_SYMBOL = 'X';
constexpr char EVEN_SYMBOL = 'O';
constexpr long long LL1 = 1;
constexpr int INF = std::numeric_limits<int>::max();
constexpr int NEG_INF = std::numeric_limits<int>::min();
constexpr int MAX_DEPTH = 10;

// This is a map used for valuation function - each field is assigned a value
// just like in https://web.stonehill.edu/compsci/CS211/Assignments/c43.gif
constexpr long long IS_VALUE_USED[14] = {
    false, false, false,
    true, true, true, true, true, true,
    false,
    true, true,
    false,
    true
};
constexpr long long MASKS[14] = {
    0, 0, 0,          // 1, 2, 3
    145135534866465,  // 3
    80298708570258,   // 4
    52785417043980,   // 5
    618475292928,     // 6
    69206016,         // 7
    4297359360,       // 8
    0,                // 9
    37748736,         // 10
    3221422080,       // 11
    0,                // 12
    25165824          // 13
};

typedef long long bitboard;

class Board {
    public:
        bool isWin();
        int makeMove(int column);
        void undoMove();
        void getMoves(bool* available); // Get all possible moves
        int getValue(bool print=false); // Get current board value
        int getNextMove(int search_depth); // Get next "best" optimal move
        std::pair<int, int> miniMax(int depth); // FUN
        void printMoves();
        void printBoard();
    private:
        bitboard boards[2] = {0, 0}; // Two seperate boards for O and X
        int heights[7] = {0, 7, 14, 21, 28, 35, 42}; // how high is each
        int counter = 0; // Move counter to quickly distinquish between players
        int moves[42];
        unsigned int countSetBits(bitboard n);
        void _makeMove(int column);
};
