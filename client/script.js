const WIDTH=7;
const HEIGHT=6;

Module.onRuntimeInitialized = async _ => {
      b =  new Module.Board()
};

function initializeBoard(){
  board = document.getElementById("board");
  for (var row = 0; row < 6; row++) {
    var tr = document.createElement('tr');
    for (var col = 0; col < 7; col++) {
        var td = document.createElement('td');
        td.innerHTML = `${row}${col}`;
        tr.appendChild(td);
    }
    board.appendChild(tr);
  }
}
initializeBoard();

/*
function refreshBoard(){
  getBoard()  
}

function getAIMove(depth){
  move = b.getNextMove(depth);
  b.make(move);
  refreshBoard();
  // TODO: Get stats - number of positions evaluated, time
  //
}

// onclick for all the rows/columns
function makeMove(position){
  b.makeMove(position)
  refreshBoard()
}

// Return board array
function readBoard(){
      pass;
}
*/