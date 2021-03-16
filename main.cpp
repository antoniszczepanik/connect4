#include "board.h"
#include <iostream>

using namespace std;

int main(){
    Board b;
    int move;
    while (true) {
        cout << "Enter an next move (int in range 0-6):" << endl;
        cin >> move;
        b.makeMove(move);
    }
}
