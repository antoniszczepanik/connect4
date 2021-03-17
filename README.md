# Connect4

The goal of this project is to have a real time connect4 game with possibly best AI opponent.
All the components should run offline inside the browser.
This will be implemented solely in C++ and then transpiled to WASM, just for the sake of it.
It will also be interesting to compare results with native C++ speed.

## Board Representation

The board representation should allow to easily

1. Check for available moves
2. Verify if winning condition is satisfied
3. Check value function for both players

The board will be represented using Fhourstone representation:

  6 13 20 27 34 41 48   55 62     Additional row
+---------------------+ 
| 5 12 19 26 33 40 47 | 54 61     top row
| 4 11 18 25 32 39 46 | 53 60
| 3 10 17 24 31 38 45 | 52 59
| 2  9 16 23 30 37 44 | 51 58
| 1  8 15 22 29 36 43 | 50 57
| 0  7 14 21 28 35 42 | 49 56 63  bottom row
+---------------------+

## Code structure
