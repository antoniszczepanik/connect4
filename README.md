# Connect4

The goal of this project is to have a real time connect4 game with possibly best AI opponent.
All the components should run offline inside the browser.
This will be implemented solely in C++ and then transpiled to WASM, just for the sake of it.
It will also be interesting to compare results with native C++ speed.

## Code structure

To know how to abstract the C++ code I have to know how running WASM code in JS works.
For example I'm not sure what interfaces are available.

Let's figure out what we can use in JS after compiling C++ to WASM:
- we cannot use DOM from C++ - frontend operations need to be left entirely to JS, though that's not suprising
- we can use only SPECIFIED functions - if we do not specify any then only the main is run.

After that let's think about what interfaces will be available.
We should make sure that only displaying logic is calculated on frontend.

JS:
	- get's board representation
	- sends call with next move representation (position 7, player B)
	- get's new board state with (or error or win msg) back
	- front will use board representation seldom, also it will get it back rarely
	- this means we can use inefficient implementation and serialize it with C++

WASM:
	- provides above specified interfaces
	- board will need to be serialized to allow calculating value funciton as efficiently as possible
	- this will be done entirely in C++

## Board Representation

The board representation should allow to easily

1. Check for available moves
2. Verify if winning condition is satisfied
3. Check value function for both players

Let's try to represent the board using Fhourstone representation:

  6 13 20 27 34 41 48   55 62     Additional row
+---------------------+ 
| 5 12 19 26 33 40 47 | 54 61     top row
| 4 11 18 25 32 39 46 | 53 60
| 3 10 17 24 31 38 45 | 52 59
| 2  9 16 23 30 37 44 | 51 58
| 1  8 15 22 29 36 43 | 50 57
| 0  7 14 21 28 35 42 | 49 56 63  bottom row
+---------------------+
