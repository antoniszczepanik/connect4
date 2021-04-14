const WIDTH=7;
const HEIGHT=6;

connect4 = function(){
  Module.onRuntimeInitialized = async _ => {
    b =  new Module.Board();
  };

  function initialize(){
    initializeBoard();
    document.addEventListener("click", makeManualMove);
  }

  function initializeBoard(){
    let board = document.getElementById("board");
    for (var row = 0; row < 6; row++) {
      let tr = document.createElement('tr');
      for (var col = 0; col < 7; col++) {
          let td = document.createElement('td');
          td.id = `${row}${col}`;
          td.className += "cell"
          td.setAttribute("data-value", 0)
          tr.appendChild(td);
      }
      board.appendChild(tr);
    }
  }

  function updateDepthLabel(new_value){
    let value_label = document.getElementById("depth_label");
    value_label.innerHTML = new_value;
  }

  function makeMove(column){
      b.makeMove(column);
      renderBoard();
  }

  // We want to be agnosting to height of the click, so let's
  // calculate next move based on mouse position.
  // Assumes cells inside the board are evenly spaced.
  function makeManualMove(event) {
    makeMove(getTargetColumnFromPosition(event));
  }
  
  function makeAIMove(){
    let depth = parseInt(document.getElementById("depth_label").innerHTML);
    makeMove(b.getNextMove(depth));
  }
  
  function undoMove(){
    b.undoMove();
    renderBoard();
  }
  
  function renderBoard(){
    let board_str = b.getBoardStr();
    for (let row_i = 0; row_i < 6; row_i++){
      for (let col_i = 0; col_i < 7; col_i++){
        let board_str_i = (row_i * 7) + col_i;
        let cell_target_value = board_str.charAt(board_str_i);
        let cell = document.getElementById(`${row_i}${col_i}`);
        if (cell.getAttribute("data-value") != cell_target_value){
          console.log("updating data-value of cell to", cell_target_value)
          cell.setAttribute("data-value", cell_target_value)
          if (cell_target_value == 1){
              cell.classList.remove("blue")
              cell.classList.add("red")
          } else if (cell_target_value == 2) {
              cell.classList.remove("red")
              cell.classList.add("blue")
          } else {
              cell.classList.remove("blue")
              cell.classList.remove("red")
          }
        }
      }
    }
  }

  function getTargetColumnFromPosition(event){
    let board = document.getElementById("board");
    let board_rect = board.getBoundingClientRect();
    // board rect includes the border
    let border_width = +getComputedStyle(board).borderTopWidth.slice(0, -2)
    let left = board_rect.left + border_width;
    let right = board_rect.right - border_width;
    let width = right - left;
    let col_width = width / WIDTH;
    // Allow clicks above, deny click below board
    if ((event.clientX > left) && (event.clientX < right) && (event.clientY < board_rect.bottom)){
      return Math.floor((event.clientX - left)/col_width)
    } else {
      return -1;
    }
  }

  return { 
    init:initialize,
    updateDepthLabel: updateDepthLabel,
    makeAIMove: makeAIMove,
    undoMove: undoMove,
   }
}();

connect4.init();