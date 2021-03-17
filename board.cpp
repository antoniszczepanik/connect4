#include <iostream>
//#include <utility>
#include "board.h"

using namespace std;

// This implementation uses bitboard as board representations which
// allows to use bitwise operations to calculate the board value 
// and check winning conditions. For details please see:
// https://github.com/denkspuren/BitboardC4/blob/master/BitboardDesign.md

int Board::getValue(bool isEvenPlayer){
    bitboard board = boards[(isEvenPlayer ? 0 : 1)];
    int directions[] = { 1, 7, 6, 8 }; // vert, diag, diag, horizon
    bitboard bb;
    int sum = 0;
    for (const int& direction : directions) {
        sum += board & (board >> direction);
    }
    return sum;
}

int Board::getNextMove(){
    return miniMax(SEARCH_DEPTH, (counter & 1), true);
}

int Board::miniMax(int depth, bool isEvenPlayer, bool returnIndex){
    // NOTE: depth == 0 is only allowed when not returning index
    if (!returnIndex){
        if (isWin()){
            return isEvenPlayer ? INF : NEG_INF;
        }
        if (depth == 0){
           return getValue(isEvenPlayer);
        }
    }
    bool available[7] = {false};
    getMoves(available);
    int best_value, best_value_ix, cur_value;
    if (isEvenPlayer) // Even player is a maximizer
    {
        best_value = NEG_INF;
        for (int i = 0; i < 7; i++){
            if (available[i]){
                makeMove(i);
                cur_value = miniMax(depth-1, false, false);
                if (cur_value == INF){
                    undoMove();
                    return returnIndex ? i : cur_value;
                }
                if (cur_value > best_value){
                    best_value = cur_value;
                    best_value_ix = i;
                }
                undoMove();
            }
        }
    } else { // Odd player is a minimizer
        best_value = INF;
        for (int i = 0; i < 7; i++){
            if (available[i]){
                makeMove(i);
                cur_value = miniMax(depth-1, true, false);
                if (cur_value == NEG_INF){
                    undoMove();
                    return returnIndex ? i : cur_value;
                }
                if (cur_value < best_value){
                    best_value = cur_value;
                    best_value_ix = i;
                }
                undoMove();
            }
        }
    }
    return returnIndex ? best_value_ix : best_value;
}


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


void Board::makeMove(int column, bool print){
    moves[counter] = column;
    boards[counter++ & 1] ^= LL1 << heights[column]++;
    if (print){
        printBoard();
        printMoves();
    }
}

void Board::undoMove(){
    int previous_move = moves[--counter];
    boards[counter & 1] ^= LL1 << --heights[previous_move];
}

bool Board::isWin() {
    bitboard board = boards[counter & 1];
    int directions[] = { 1, 7, 6, 8 }; // vert, diag, diag, horizon
    bitboard temp;
    for (const int& direction : directions) {
        temp = board & (board >> direction);
        if ((temp & (temp >> (2 * direction))) != 0){
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
}
