#include <iostream>
#include "board.h"

using namespace std;


void Board::printBoard(){
    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            int value = board[i][j];
            char repr = ' ';
            if (value == 1){
                repr = EVEN_SYMBOL;
            } else if (value == -1) {
                repr = ODD_SYMBOL;
            }
            cout << repr  << "|";
        }
        cout << endl;
    }
}

bool Board::isLegal(bool player, int column){
    if (next_move != player){
        cout << "This is not this players turn" << endl;
        return false;
    }
    if ((column < 0) || column >= WIDTH){
        cout << "This column is not available" << endl;
        return false;
    }
    if (heights[column] >= HEIGHT) {
        cout << "This column is full" << endl;
        return false;
    }
    return true;
}

bool isFinished(){
    // TODO:
    return false;
}

void Board::move(bool player, int column){
    if(isLegal(player, column)){
        heights[column] += 1;
        board[HEIGHT  - heights[column]][column] = player ? 1 : -1;
        next_move = !player;
    }
    if (isFinished()){
        cout << (player ? ODD_SYMBOL : EVEN_SYMBOL) << " won!" << endl;
    }
}
