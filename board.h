constexpr unsigned int WIDTH = 7;
constexpr unsigned int HEIGHT = 6;

constexpr char EVEN_SYMBOL = 'X';
constexpr char ODD_SYMBOL = 'O';

class Board {
    public:
        void printBoard();
        void move(bool player, int column);
        bool isLegal(bool player, int column);
    private:
        int board[HEIGHT][WIDTH] = {{}};
        int heights[WIDTH] = {0};
        bool next_move = false; // false is even, true is odd
};
