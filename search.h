#include <utility>
#include "board.h"

using namespace std; 

int getNextMove(Board b, int search_depth);
pair<int, int> miniMax(Board b, int depth);
int getValue(bitboard* bitboards, bool previous_player);
unsigned int countSetBits(bitboard n);
int getRecursionCount();
