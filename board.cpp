#include <iostream>
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
    result_t result = miniMax(*this, search_depth);
    cout << "Optimal move is " << result.move;
    cout << " with value " << result.value << " at depth " << result.depth << endl;
    return result.move;
}

std::array<bool, 7> Board::getMoves()
{
    std::array<bool, 7> available_moves = { false };
    // This row is not part of the board, used only to check for overflows
    long long top_row = 0b1000000100000010000001000000100000010000001000000;
    for (int col = 0; col < 7; col++) {
        if ((top_row & (LL1 << heights[col])) == 0) {
            available_moves[col] = true;
        }
    }
    return available_moves;
}

int Board::makeMove(int column)
{
    if (isWin()) {
        return 2;
    }
    if (column > 6 || column < 0){
        return 1;
    }
    // Handle full column.
    if (heights[column] + 1 > ((column * 7) + 7)){
        return 1;
    }
    rawMakeMove(column);
    return 0;
}

void Board::rawMakeMove(int column)
{
    move_history[counter++] = column;
    boards[next_player] ^= LL1 << heights[column]++;
    next_player = !(next_player);
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
    boards[!next_player] ^= LL1 << --heights[move_history[--counter]];
    next_player = !(next_player);
}

bool Board::isWin()
{
    // Will check if previously made move was a winning move
    bitboard board = boards[getPreviousPlayer()];
    int directions[] = { 7, 1, 6, 8 }; // vert, diag, diag, horizon
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
    return next_player;
}

char Board::getNextPlayerRepr(){
    return next_player ? ODD_SYMBOL : EVEN_SYMBOL;
}

bool Board::getPreviousPlayer(){
    return !(next_player);
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
    .function("makeMove", &Board::makeMove)
    .function("undoMove", &Board::undoMove)
    .function("getNextMove", &Board::getNextMove)
    .function("getNextPlayer", &Board::getNextPlayer)
    .function("getBoardStr", &Board::getBoardStr)
    ;
}
