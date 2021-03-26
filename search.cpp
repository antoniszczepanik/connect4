#include <iostream>
#include <utility>
#include <assert.h>
#include "search.h"
#include "board.h"

using namespace std;

pair<int, int> miniMax(Board b, int depth, int alpha, int beta)
{
    // If there's a win on the board or this is a max depth
    // then the method returns -1 as index.
    bool previous_player = b.getPreviousPlayer();
    if (b.isWin()) {
        // We need to check whose turn was it before the last move
        return make_pair((previous_player ? INF : NEG_INF), -1);
    } else if (depth == 0) {
        int score_a = getValue(b.getBitboards(), previous_player);
        int score_b = getValue(b.getBitboards(), !previous_player);
        return make_pair(score_a + score_b, -1);
    }

    bool available[7] = { false };
    b.getMoves(available);
    int best_value, best_value_ix, cur_value;
    best_value_ix = -1;
    best_value = b.getNextPlayer() ? NEG_INF : INF;
    for (int i = 0; i < 7; i++) {
        if (available[i]) {
            // even in case all moves loose, chose first available
            if (best_value_ix == -1){
               best_value_ix = i; 
            }
            b.rawMakeMove(i);
            cur_value = miniMax(b, depth - 1, alpha, beta).first;
            b.undoMove();
            if (cur_value == (b.getNextPlayer() ? INF : NEG_INF)) {
                return make_pair(cur_value, i);
            }
            // maximizer
            if (b.getNextPlayer()) { 
                if (cur_value > best_value) {
                    best_value = cur_value;
                    best_value_ix = i;
                    alpha = max(best_value, alpha);
                    if (beta <= alpha){
                        break;
                    }
                      
                }
            // minimizer
            } else {
                if (cur_value < best_value) {
                    best_value = cur_value;
                    best_value_ix = i;
                    beta = min(best_value, beta);
                    if (beta <= alpha){
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
    int directions[] = { 1, 6, 7, 8 }; // vert, diag, diag, horizon
    bitboard board = bitboards[previous_player];
    int score = 0;
    bitboard temp;
    for (const int& direction : directions) {
        // Count number of threes
        temp = board >> direction;
        score += __builtin_popcountll(board & temp & (temp >> direction));
    }
    for (int i = 0; i < 14; i++) {
        // Check how favorable is the position
        if (IS_VALUE_USED[i]) {
            score += __builtin_popcountll(board & MASKS[i]) * i;
        }
    }
    return (previous_player ? score : -score);
}
