#include <limits>
#include <utility>

constexpr char ODD_SYMBOL = 'X';
constexpr char EVEN_SYMBOL = 'O';
constexpr long long LL1 = 1;
constexpr int INF = std::numeric_limits<int>::max();
constexpr int NEG_INF = std::numeric_limits<int>::min();

// This map is used for valuation function - each field is assigned a value
// just like in https://web.stonehill.edu/compsci/CS211/Assignments/c43.gif
// Later boards are masked, which makes valuating given position a lot faster.
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

// Representation of "present" masks, makes iterating over them a little easier
constexpr long long IS_VALUE_USED[14] = {
    false, false, false,
    true, true, true, true, true, true,
    false,
    true, true,
    false,
    true
};
typedef long long bitboard;

class Board {
    public:
        bool isWin();
        int makeMove(int column);
        void rawMakeMove(int column);
        void undoMove();
        // Update available list with all possible moves
        void getMoves(bool* available);
        void printBoard();
        bool getNextPlayer(); // 0 for even, 1 for odd player
        char getNextPlayerRepr();
        bool getPreviousPlayer(); // 0 for even, 1 for odd
        bitboard* getBitboards();
    private:
        bitboard boards[2] = {0, 0};  // Two seperate boards for O and X
        int heights[7] = {0, 7, 14, 21, 28, 35, 42};  // Mark height in each col
        int counter = 0;  // Allows to distinguish between players with (counter & 1)
        int move_history[42];
};

