#define WIDTH  7
#define HEIGHT 6

#define EVEN_PLAYER_SYMBOL 'X'
#define ODD_PLAYER_SYMBOL 'O'

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
