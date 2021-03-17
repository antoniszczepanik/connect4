#include "board.h"
#include <iostream>

using namespace std;

int main(){
    Board b;
    int move;
    while (true) {
        cout << "Enter an next move (int in range 0-6):" << endl;
        cin >> move;
        if (move == -1){
            b.undoMove();
            b.printBoard();
        } else if (move == -2){
            move = b.getNextMove();
            b.makeMove(move, true);
        } else {
            b.makeMove(move, true);
        }
    }
}
