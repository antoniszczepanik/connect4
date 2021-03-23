#include <utility>
#include "board.h"

using namespace std; 

constexpr bitboard VALID_MOVE_MASK = 279258638311359;

int getNextMove(Board b, int search_depth);
pair<int, int> miniMax(Board b, int depth, int alpha, int beta);
int getValue(bitboard* bitboards, bool previous_player);
int getValueBitwise(bitboard* bitboards, bool previous_player);
int countWins(bitboard board);
unsigned int countSetBits(bitboard n);
int getCheckedPositionsCount();
