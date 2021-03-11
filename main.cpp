#include "board.h"

int main(){
    Board b;
    b.move(false, 0);
    b.move(true, 3);
    b.move(false, 3);
    b.move(true, 5);
    b.move(false, 1);
    b.move(true, 1);
    b.move(false, 5);
    b.move(true, 5);
    b.move(false, 5);
    b.move(true, 5);
    b.move(false, 1);
    b.move(true, 1);
    b.move(false, 1);
    b.move(true, 1);
    b.printBoard();
}
