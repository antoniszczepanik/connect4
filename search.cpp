#include <iostream>
#include <utility>
#include <assert.h>
#include "search.h"

using namespace std;

long g_number_of_positions_checked;

int getNextMove(Board b, int search_depth)
{
    g_number_of_positions_checked = 0;
    pair<int, int> value_n_index = miniMax(b, search_depth, NEG_INF, INF);
    cout << "Optimal move is " << value_n_index.second;
    cout << " with value " << value_n_index.first << endl;
    return value_n_index.second;
}

pair<int, int> miniMax(Board b, int depth, int alpha, int beta)
{
    // If there's a win on the board or this is a max depth
    // then the method returns -1 as index.
    bool previous_player = b.getPreviousPlayer();
    if (b.isWin()) {
        // We need to check whose turn was it before the last move
        return make_pair((previous_player ? INF : NEG_INF), -1);
    } else if (depth == 0) {
        int score = getValue(b.getBitboards(), previous_player);
        return make_pair(score, -1);
    }

    bool available[7] = { false };
    b.getMoves(available);
    int best_value, best_value_ix, cur_value;
    best_value = b.getNextPlayer() ? NEG_INF : INF;
    for (int i = 0; i < 7; i++) {
        if (available[i]) {
            b.rawMakeMove(i);
            cur_value = miniMax(b, depth - 1, alpha, beta).first;
            b.undoMove();
            if (cur_value == (b.getNextPlayer() ? INF : NEG_INF)) {
                return make_pair(cur_value, i);
            }
            // maximizer
            if (b.getNextPlayer()) { 
                if (cur_value >= best_value) {
                    best_value = cur_value;
                    best_value_ix = i;
                    alpha = max(best_value, alpha);
                    if (beta < alpha){
                        break;
                    }
                      
                }
            // minimizer
            } else {
                if (cur_value <= best_value) {
                    best_value = cur_value;
                    best_value_ix = i;
                    beta = min(best_value, beta);
                    if (alpha < beta){
                        break;
                    }
                }
            }
        }
    }
    return make_pair(best_value, best_value_ix);
}

int getValue(bitboard* bitboards, bool previous_player)
{
    g_number_of_positions_checked += 1;    
    if (countWins(bitboards[0]) > 0){
        return 1;
    } else if (countWins(bitboards[1]) > 0){
        return -1;
    } else {
        return 0;
    }
    //int directions[] = { 1, 6, 7, 8 }; // vert, diag, diag, horizon
    //bitboard board = bitboards[previous_player];
    //int score = 0;
    //bitboard temp;
    //for (const int& direction : directions) {
    //    // Count three stones in a row
    //    temp = board >> direction;
    //    score += countSetBits(board & temp & (temp >> direction));
    //}
    //for (int i = 0; i < 14; i++) {
    //    // Check how favorable is the position
    //    if (IS_VALUE_USED[i]) {
    //        score += countSetBits(board & MASKS[i]) * i;
    //    }
    //}

    //return (previous_player ? score : -score);
}

int getValueBitwise(bitboard* bitboards, bool previous_player){
    g_number_of_positions_checked += 1;    
    int directions[] = { 1, 6, 7, 8 }; // vert, diag, diag, horizon
    int weights[] = { 
        3, // possible winning lines missing 1 stone
        1, // possible winning positions missing 2 stones
    };
    int score = 0;
    bitboard board = bitboards[previous_player];
    bitboard opponent = bitboards[~previous_player];
    bitboard temp_board = board;
    for (const int& direction : directions){
        for (const int& weight : weights){
            temp_board ^= temp_board >> direction; // add consequent move
            temp_board &= VALID_MOVE_MASK;         // check for overflow
            temp_board &= ~opponent;               // remove blocked by opponent
            score += countWins(temp_board) * weight;
        }
    }
    return (previous_player ? score : -score);
}


int countWins(bitboard board){
    int directions[] = { 1, 6, 7, 8 }; // vert, diag, diag, horizon
    bitboard temp;
    int win_number = 0;
    for (const int& direction : directions) {
        temp = board & (board >> direction);
        temp &= (temp >> (2 * direction));
        win_number += countSetBits(temp);
    }
    return win_number;
}

unsigned int countSetBits(bitboard n)
{
    int count = 0;
    while (n) {
        n &= (n - 1);
        count++;
    }
    return count;
}

int getCheckedPositionsCount(){
    return g_number_of_positions_checked;
}
