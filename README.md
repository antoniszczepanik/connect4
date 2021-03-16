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
The board representation should allow to
1. Check for available moves

Interesting benchmark https://tromp.github.io/c4/fhour.html
And representation https://en.wikipedia.org/wiki/Fhourstones + description https://github.com/denkspuren/BitboardC4/blob/master/BitboardDesign.md

