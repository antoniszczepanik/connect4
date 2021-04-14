#include "board.h"

int main(int argc, char* argv[]){
    Board b;
    b.printBoard();
    b.makeMove(0);
    b.makeMove(1);
    b.makeMove(2);
    b.makeMove(3);
    b.makeMove(4);
    b.makeMove(5);
    b.makeMove(6);
    b.printBoard();
    return 0;
}
