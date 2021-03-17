#include <iostream>
#include <utility>
#include <assert.h>
#include "board.h"

using namespace std;

// This implementation uses bitboard as board representations which
// allows to use bitwise operations to calculate the board value 
// and check winning conditions. For details please see:
// https://github.com/denkspuren/BitboardC4/blob/master/BitboardDesign.md
//
// TODO: (counter & 1) could be calculated once for some functions

int Board::getValue(){
    bitboard board = boards[((counter & 1) ? 0 : 1)];
    int directions[] = { 1, 7, 6, 8 }; // vert, diag, diag, horizon
    int sum = 0;
    for (const int& direction : directions) {
        sum += countSetBits(board & (board >> direction));
    }
    return (counter & 1) ? sum : -sum;
}

unsigned int Board::countSetBits(bitboard n)
{
        unsigned int count = 0;
        while (n) {
            n &= (n - 1);
            count++;
        }
        return count;
}

int Board::getNextMove(){
    pair<int, int> value_n_index = miniMax(MAX_DEPTH);
    // if best value for maximizer is the lowest possible then the game is lost
    if (value_n_index.first == ((counter & 1) ? NEG_INF : INF)){
        cout << ((counter & 1) ? "O" : "X") << " won the game!";
    }

    assert(value_n_index.second >= 0);
    assert(value_n_index.second < 7);
    cout << "Optimal move is " << value_n_index.second;
    cout << " with value " << value_n_index.first << endl;
    return value_n_index.second;
}

pair<int, int> Board::miniMax(int depth){
    // If there's a win on the board or this is a max depth
    // then the method returns -1 as index.
    if (isWin()){
        // We need to check whose turn was it before the last move
        return make_pair((((counter - 1) & 1) ? INF : NEG_INF), -1);
    } else if (depth == 0){
        return make_pair(getValue(), -1);
    }

    bool available[7] = {false};
    getMoves(available);
    int best_value, best_value_ix, cur_value;
    best_value = (counter & 1) ? NEG_INF : INF;
    for (int i = 0; i < 7; i++){
        if (available[i]){
            makeMove(i);
            cur_value= miniMax(depth-1).first;
            undoMove();
            if (cur_value == ((counter & 1) ? INF : NEG_INF)){
                return make_pair(cur_value, i);
            }
            if (counter & 1){ // maximizer
                if (cur_value > best_value){
                    best_value = cur_value;
                    best_value_ix = i;
                }
            } else { // minimizer
                if (cur_value < best_value){
                    best_value = cur_value;
                    best_value_ix = i;
                }
            }
        }
    }
    return make_pair(best_value, best_value_ix);
}


void Board::getMoves(bool* available) {
    // The last spot (index 7) is reserved for a flag representing 
    // "is any field available"
    long long top = 0b1000000100000010000001000000100000010000001000000;
    bool isAnyAvailable = false;
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
        cout << "Next move is for ";
        cout << ((counter & 1) ? "true maximizer (X)" : "false minimizer (O)") << endl;
    }
}

void Board::undoMove(){
    int previous_move = moves[--counter];
    boards[counter & 1] ^= LL1 << --heights[previous_move];
}

bool Board::isWin() {
    // Will check if previously made move was a winning move
    // Hence we need to consider previous board offseting counter by 1
    bitboard board = boards[(counter - 1)& 1];
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
