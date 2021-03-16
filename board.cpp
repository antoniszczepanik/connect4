#include <iostream>
#include "board.h"

using namespace std;

// This implementation uses bitboard as board representations which
// allows to use bitwise operations to calculate the board value 
// and check winning conditions. For details please see:
// https://github.com/denkspuren/BitboardC4/blob/master/BitboardDesign.md


void Board::getMoves(bool* available) {
    long long top = 0b1000000100000010000001000000100000010000001000000;
    for(int col = 0; col < 7; col++) {
        if ((top & (LL1 << heights[col])) == 0){
           available[col] = true; 
        }
    }
}

void Board::printMoves(){
    bool available[7] = {false};
    getMoves(available);
    cout << "Moves available: ";
    for (int i = 0; i < 7; i++){
        if (available[i]){
            cout << i << " ";
        }
    }
    cout << endl;
}


void Board::makeMove(int column){
    if (column == -1) {
        undoMove();
        return;
    }
    moves[counter] = column;
    boards[counter++ & 1] ^= LL1 << heights[column]++;
    printBoard();
    printMoves();
}

void Board::undoMove(){
    int previous_move = moves[--counter];
    boards[counter & 1] ^= LL1 << --heights[previous_move];
    printBoard();
    printMoves();
}

bool Board::isWin(bitboard board) {
    int directions[] = { 1, 7, 6, 8 }; // vert, diag, diag, horizon
    long long bb;
    for (const int& direction : directions) {
        bb = board & (board >> direction);
        if ((bb & (bb >> (2 * direction))) != 0){
            return true;
        }
    }
    return false;
}

void Board::printBoard(){
    // First convert two long long digits to array
    int board_arr[64] = {0};
    for (int i = 0; i < 64; i++){
        if ((boards[0] & (LL1 << i)) != 0){
            board_arr[i] = 1;
    }
        if ((boards[1] & (LL1 << i)) != 0){
            board_arr[i] = -1;
        }
    }
    for (int i = 5; i >= 0; i--){
        cout << "|";
        for (int j = 0; j < 7; j++){
            switch(board_arr[i + (7 * j)]) {
                case 0:
                    cout << " |";
                    break;
                case 1:
                    cout << "O|";
                    break;
                case -1:
                    cout << "X|";
                    break;
            }
        }
        cout << endl;
    }
    cout << "|";
    for (int i = 0; i < 7; i++){
        cout << i << "|";
    }
    cout << endl;
    if ( isWin(boards[(counter-1) & 1]) ){
        cout << "There is a win on a board!" << endl;
    }
    cout << endl;
}
