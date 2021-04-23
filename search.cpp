#include "search.h"
#include "board.h"


result_t miniMax(Board b, int depth)
{
    // If there's a win on the board or this is a max depth
    // then the method returns -1 as index.
    bool previous_player = b.getPreviousPlayer();
    if (b.isWin()) {
        // We need to check whose turn was it before the last move
        return makeResult(-1, (previous_player ? INF : NEG_INF), 0);
    } else if (depth == 0) {
        // We're at the bottom of the tree
        int score_a = getValue(b.getBitboards(), previous_player);
        int score_b = getValue(b.getBitboards(), !previous_player);
        return makeResult(-1, score_a + score_b, 0);
    }
    return getBestMove(b, depth);
}

result_t getBestMove(Board b, int depth){
    std::vector<result_t> possible_results = getPossibleResults(b, depth);
    if (possible_results.size() == 0) {
        // The board is full.
        return makeResult(-1, 0, 0);
    } else if (possible_results.size() == 1) {
        // There is unique result.
        return possible_results[0];
    }

    // Otherwise there are multiple results with the same value:
    //
    //  * If posiblle results are all winning we would like to win
    //    as soon as possible (picking move with minimum depth).
    //
    //  * If posiblle results are all loosing we would like to loose
    //    as soon as possible (picking move with maximum depth).
    //
    //  * If there are no loosing/winning moves it doesn't matter which one
    //    we choose because they all must come from leaf nodes (their depth is
    //    the same).
    
    result_t best_result = possible_results[0];
    // Hangle neither loosing nor winning case
    if ((best_result.value != INF) && (best_result.value != NEG_INF)){
        return best_result;
    }
    bool is_best_value_favorable;
    if (b.getNextPlayer()){
        is_best_value_favorable = (best_result.value == INF);
    } else {
        is_best_value_favorable = (best_result.value == NEG_INF);
    }
    bool first = true;
    for (result_t cur_result : possible_results) {
        if (first){
            first = false;
            continue;
        }
        if (is_best_value_favorable){
            // The faster we can win the better.
            if (cur_result.depth < best_result.depth){
                best_result = cur_result;
            }
        } else {
            // The later we can loose the better.
            if (cur_result.depth > best_result.depth){
                best_result = cur_result;
            }
        }
    }
    return best_result;
}

std::vector<result_t> getPossibleResults(Board b, int depth){
    // In case the best value is unique return vector of size 1.
    // Otherwise return multiple winning or loosing moves.
    std::array<bool, 7> available_moves = b.getMoves();
    std::vector<result_t> possible_results;
    bool all_false = true;
    for (int i = 0; i < 7; i++){
        if (available_moves[i]){
            all_false = false;
        }
    }
    if (all_false) {
        return possible_results;
    }

    std::vector<result_t> loosing_moves;
    bool all_moves_are_loosing = true;
    result_t best_result = makeResult(-1, (b.getNextPlayer() ? NEG_INF : INF), -99);
    result_t cur_result;
    for (int move = 0; move < 7; move++){
        if (available_moves[move]){
            b.rawMakeMove(move);
            cur_result = miniMax(b, depth - 1);
            cur_result.depth += 1;
            cur_result.move = move;
            b.rawUndoMove();
            if (b.getNextPlayer()) { 
                // Maximizer
                if (cur_result.value == INF){
                    possible_results.push_back(cur_result);
                    all_moves_are_loosing = false;
                } else if (cur_result.value > best_result.value) {
                    best_result = cur_result;
                    all_moves_are_loosing = false;
                } else if (all_moves_are_loosing && (best_result.value == NEG_INF)){
                    loosing_moves.push_back(cur_result);
                }
            } else {
                // Minimizer
                if (cur_result.value == NEG_INF){
                    possible_results.push_back(cur_result);
                    all_moves_are_loosing = false;
                } else if (cur_result.value < best_result.value) {
                    best_result = cur_result;
                    all_moves_are_loosing = false;
                } else if (all_moves_are_loosing && (best_result.value == INF)) {
                    loosing_moves.push_back(cur_result);
                }
            }
        }
    }
    if (all_moves_are_loosing){
        return loosing_moves;
    }
    if (possible_results.empty()){
        possible_results.push_back(best_result);
    }
    return possible_results;
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

result_t makeResult(short move, int value, short depth){
    result_t res = { move, value, depth };
    return res;
}
