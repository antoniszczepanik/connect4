# Connect4
The goal of this project is to have Connect4 game with possibly computer opponent in the browser. Game engine and AI will be implemented in C++ and transpiled to WASM, which means all computations will run on the client.
It will be interesting to see how much we can optimize using bitboards, minimax algorithm and how much overhead is introduced by converting such implementation to WASM.

## AI
Minimax algorithm with alpha-beta prunning extension is defacto standard in simple
turned based games like Connect4. That's what is used in this project as well.

TODO:

- There seems to be a problem with alpha/beta pruning - to much pruning happens.

- Memoising recently requested boards in a hash table. Kind of LRU cache for getting borard values. How much memory can we afford to use in the browser?


## Board Representation
The board is represented using 64 bit integer. It allows to use
bitwise operations to check for a win and available moves, which is REALLY FAST. Bitwise operations are also used to valuate static board positions. To read more about this stuff make sure to see https://github.com/denkspuren/BitboardC4/blob/master/BitboardDesign.md
It's really clever!

```
  6 13 20 27 34 41 48   55 62     Additional row
+---------------------+ 
| 5 12 19 26 33 40 47 | 54 61     top row
| 4 11 18 25 32 39 46 | 53 60
| 3 10 17 24 31 38 45 | 52 59
| 2  9 16 23 30 37 44 | 51 58
| 1  8 15 22 29 36 43 | 50 57
| 0  7 14 21 28 35 42 | 49 56 63  bottom row
+---------------------+
```

## Converting C++ implementation to WASM
