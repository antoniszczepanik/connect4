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
    // Select the best move out of all available children moves
    result_t best_result = { -1, b.getNextPlayer() ? NEG_INF : INF, -99};
    for (result_t cur_result : possible_results) {
        // even in case all moves loose, choose first available
        if (best_result.move == -1){
            best_result = cur_result;
        }
        // if this is a win just return it (TODO: for now)
        if (cur_result.value == (b.getNextPlayer() ? INF : NEG_INF)) {
            return makeResult(cur_result.move, cur_result.value, cur_result.depth);
        }
        // maximizer
        if (b.getNextPlayer()) { 
            if (cur_result.value > best_result.value) {
                best_result = cur_result;
            }
        // minimizer
        } else {
            if (cur_result.value < best_result.value) {
                best_result = cur_result;
            }
        }
    }
    return makeResult(best_result.move, best_result.value, best_result.depth);
}

std::vector<result_t> getPossibleResults(Board b, int depth){
    std::vector<int> available_moves = b.getMoves();
    std::vector<result_t> possible_results;
    if (available_moves.empty()) {
        return possible_results;
    }
    result_t cur_result;
    for (int move : available_moves){
        b.rawMakeMove(move);
        cur_result = miniMax(b, depth - 1);
        b.rawUndoMove();
        // Let's collect all best possible values
        // if (cur_result.value == (b.getNextPlayer() ? INF : NEG_INF)) {
        //    possible_results.push_back(makeResult(move, cur_result.value, cur_result.depth+1));
        //    continue
        //}
        // Let's collect everything for now.
        // TODO: Alpha-Beta prunning needs to make it's way back here
        possible_results.push_back(makeResult(move, cur_result.value, cur_result.depth+1));
    }
    return possible_results;
}

result_t makeResult(int move, int value, int depth){
    result_t res = { move, value, depth };
    return res;
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
