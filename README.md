# Connect4
The goal of this project is to have a real time connect4 game with possibly best AI opponent.
All the components will eventually run offline inside the browser.
This will be implemented solely in C++ and then transpiled to WASM.
It hope it will be interesting to compare results with native C++ speed.

## AI
Minimax algoritm is used for implementing the AI.
TODO: Picking the best possible valuation function, currently seems little random.
TOOD: alfa/beta pruning
TODO: Memoising recently requested boards in a hash table.

## Board Representation
The board is represented using very efficient Fhourstone representation, which
allows to perform bitwise operations to check for a win.

  6 13 20 27 34 41 48   55 62     Additional row
+---------------------+ 
| 5 12 19 26 33 40 47 | 54 61     top row
| 4 11 18 25 32 39 46 | 53 60
| 3 10 17 24 31 38 45 | 52 59
| 2  9 16 23 30 37 44 | 51 58
| 1  8 15 22 29 36 43 | 50 57
| 0  7 14 21 28 35 42 | 49 56 63  bottom row
+---------------------+
