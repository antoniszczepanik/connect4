#include <iostream>
#include <chrono>
#include "search.h"

using namespace std;
using namespace std::chrono;

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

            auto start = high_resolution_clock::now();
            move = getNextMove(b, stoi(argv[1]));
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << getCheckedPositionsCount() << " positions checked ";
            cout << (getCheckedPositionsCount() /(duration.count()/1000));
            cout << " Kpos/s" << endl;
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
