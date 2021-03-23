#include <iostream>
#include "search.h"

using namespace std;

int main(int argc, char* argv[]){
    Board b;
    int move;
    while (true) {
        cout << "Enter an next move (int in range 0-6):" << endl;
        cin >> move;
        if (move == -1){
            b.undoMove();
            b.printBoard();
            continue;
        } else if (move == -2){
            move = getNextMove(b, stoi(argv[1]));
            if (move == -1){
                cout << "No more moves, the game is won/lost!" << endl;
                exit(-1);
            }
        } else if (move == -3){
            int value = getValue(b.getBitboards(),b.getPreviousPlayer());
            cout << "Value of the board is: " << value << endl;
            continue;
        }
        if (b.makeMove(move) == -1){
            cout << "Game over!" << endl;
            exit(-1);
        };
    }
}
