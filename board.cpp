#include <iostream>
#include <string>
#include <emscripten/bind.h>
#include "board.h"
#include "search.h"

using namespace std;

// This implementation uses bitboard as representations to
// allow use of bitwise operations to calculate the board value
// and check winning conditions. For details see:
// https://github.com/denkspuren/BitboardC4/blob/master/BitboardDesign.md
int Board::getNextMove(int search_depth)
{
    pair<int, int> value_n_index = miniMax(*this, search_depth, NEG_INF, INF);
    cout << "Optimal move is " << value_n_index.second;
    cout << " with value " << value_n_index.first << endl;
    return value_n_index.second;
}

void Board::getMoves(bool* available)
{
    // This row is not part of the board, used only to check for overflows
    long long top_row = 0b1000000100000010000001000000100000010000001000000;
    for (int col = 0; col < 7; col++) {
        if ((top_row & (LL1 << heights[col])) == 0) {
            available[col] = true;
        }
    }
}

int Board::makeMove(int column)
{
    if (isWin()) {
        return 2;
    }
    if (column > 6 || column < 0){
        return 1;
    }
    // Move not available
    if (heights[column] + 1 > ((column * 7) + 7)){
        return 1;
    }
    rawMakeMove(column);
    return 0;
}

void Board::rawMakeMove(int column)
{
    move_history[counter] = column;
    boards[getNextPlayer()] ^= LL1 << heights[column]++;
    counter++;
}

int Board::undoMove(){
    if (counter == 0){
        return 1;
    }
    rawUndoMove();
    return 0;
}

void Board::rawUndoMove()
{
    int previous_move = move_history[--counter];
    boards[getNextPlayer()] ^= LL1 << --heights[previous_move];
}

bool Board::isWin()
{
    // Will check if previously made move was a winning move
    bitboard board = boards[getPreviousPlayer()];
    int directions[] = { 1, 6, 7, 8 }; // vert, diag, diag, horizon
    bitboard temp;
    for (const int& direction : directions) {
        temp = board & (board >> direction);
        if ((temp & (temp >> (2 * direction))) != 0) {
            return true;
        }
    }
    return false;
}

void Board::printBoard()
{
    // First convert to array
    int board_arr[64] = { 0 };
    for (int i = 0; i < 64; i++) {
        if ((boards[0] & (LL1 << i)) != 0) {
            board_arr[i] = 1;
        }
        if ((boards[1] & (LL1 << i)) != 0) {
            board_arr[i] = -1; }
    }
    for (int i = 5; i >= 0; i--) {
        cout << "|";
        for (int j = 0; j < 7; j++) {
            switch (board_arr[i + (7 * j)]) {
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
    cout << " _ _ _ _ _ _ _ " << endl;
    cout << "|";
    for (int i = 0; i < 7; i++) {
        cout << i << "|";
    }
    cout << endl;
}

bool Board::getNextPlayer(){
    return (counter & 1);
}

char Board::getNextPlayerRepr(){
    return (counter & 1) ? ODD_SYMBOL : EVEN_SYMBOL;
}

bool Board::getPreviousPlayer(){
    return ((counter -1) & 1);
}

string Board::getBoardStr(){
    string board_str;
    int index, i, j;
    for (i = 5; i >= 0; i--){
        for (j = 0; j <= 6; j++){
            index = i + (7 * j); // to go from top left
            if ((boards[0] & (LL1 << index)) != 0) {
                board_str.push_back('1');
            } else if ((boards[1] & (LL1 << index)) != 0) {
                board_str.push_back('2');
            } else {
                board_str.push_back('0');
            }

        }
    }
    return board_str;
}

bitboard* Board::getBitboards(){    
    return boards;
}

// Binding to WASM
EMSCRIPTEN_BINDINGS(my_class_example) {
    emscripten::class_<Board>("Board")
    .constructor()
    .function("printBoard", &Board::printBoard)
    .function("makeMove", &Board::makeMove)
    .function("undoMove", &Board::undoMove)
    .function("getNextMove", &Board::getNextMove)
    .function("getBoardStr", &Board::getBoardStr)
    ;
}
