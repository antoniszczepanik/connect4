#include <utility>
#include <vector>
#include "board.h"

#ifndef SEARCH_H
#define SEARCH_H

using namespace std; 

constexpr bitboard VALID_MOVE_MASK = 279258638311359;

typedef struct result {
  int move;
  int value;
  int depth;
} result_t;

result_t miniMax(Board b, int depth);
result_t getBestMove(Board b, int depth);
std::vector<result_t> getPossibleResults(Board b, int depth);
int getValue(bitboard* bitboards, bool previous_player);
int countWins(bitboard board);
result_t makeResult(int move, int value, int depth);

#endif
