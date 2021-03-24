#include <iostream>
#include <chrono>
#include <assert.h>
#include "search.h"

using namespace std;
using namespace std::chrono;


Board makeAIMove(Board b, int depth){
    int move;
    auto start = high_resolution_clock::now();
    move = getNextMove(b, depth);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    double seconds_passed = (double)duration.count()/1000000;
    double positions_checked = (double)getCheckedPositionsCount()/1000;
    cout << positions_checked << "K positions checked at ";
    cout << (positions_checked / seconds_passed) << "Kpos/s" << endl;
    if (move == -1){
        return b;
    }
    b.makeMove(move);
    return b;
}

int main(int argc, char* argv[]){
    Board b;
    int move;
    int depth = stoi(argv[1]);
    while (true) {
        b.printBoard();
        cout << "Enter an next move for " << b.getNextPlayerRepr() << endl;
        cin >> move;
        switch(move){
            case -1:
                b.undoMove();
                b.printBoard();
                break;
            case -2:
                b = makeAIMove(b, depth);
                break;
            case -3:
                cout << "Board value: " << getValue(b.getBitboards(),b.getPreviousPlayer()) << endl;
                break;
            case -4:
                while(true){
                    b = makeAIMove(b, depth);
                    b.printBoard();
                    if (b.isWin()) break; 
                }
                break;
            default:
                assert(move>=0);
                assert(move<=6);
                b.makeMove(move);
                break;
        }
        if(b.isWin()){
            b.printBoard();
            cout << "It looks like the game is over!" << endl;
            exit(0);
        }
    }
}
