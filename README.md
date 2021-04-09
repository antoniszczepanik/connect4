# Connect4
This is [connect-four](https://en.wikipedia.org/wiki/Connect_Four) AI written
in C++ and compiled to WASM which allows to run it 100% on the client.
You can adjust algorithms search depth and try to beat it at various difficulty
levels. Check your skills [here](http://iwillbeheresoon.ipromise)

(image will be here soon)

You could also use it to cheat, but hey, I hope you're not a cheater.

### Why is it interesting?

A lot of board valuations are performed, so valuation function and win checking 
function need to be REALLY fast. To achieve that super-efficient 64bit 
representation is used for the board. It allows to check for a win with 3 
bitshifts, which is kinda insane. Dominikus Herzberg has written [excellent
article](https://github.com/denkspuren/BitboardC4/blob/master/BitboardDesign.md)
explaining how it works, I highly recommend it!

```txt
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

TODO: How fast are bitwise operations in WASM? How much overhead is introduced
by running the code on 32bit machine?

### Search algorithm 

To search the game tree MiniMax algorithm with alpha/beta prunning was used.
It was really rewarding to implement such a classic from scratch and I suggest
anyone interested in turn based game AIs should give it a try :) 

### Comparison of C++ and WASM

Comparing to native C++ implementation WASM code is around X% slower,
on 2.1Ghz AMD CPU and Y% slower on iPhone 11.
Still, bitboard implementation allows it evaluate around X boards
positions/second, which means exploring tree with depth of Z is feaseable even on
mobile devices.

\*Disclaimer - the game has been solved, but such a huge game tree makes 
it really interesting playground nonetheless.
