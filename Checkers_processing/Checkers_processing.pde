//* @pjs preload="Pawn.png,Pawn1.png,King.png,King1.png"; */
int down, right, down1, right1;//curr move, (down, right)starting pos   (down1,right1)ending pos
int p0,p1;//for double jumping
boolean click;//first click select piece, second click moves piece
boolean WHITE = true;
boolean BLACK = false;
boolean turn;//player turn
boolean promote;
boolean doubleJump, jumping;
boolean gameOver;
boolean init = true;
PImage wKing, bKing, wPawn, bPawn;
PImage[][] board;
PImage[][] lastBoard;

import processing.serial.*;

Serial myPort;

//EDIT
void keyPressed() {
  if (key=='r') startPosition();
}
//END EDIT


void setup() {
  size(640, 640);
  String portName = Serial.list()[3];
  myPort = new Serial(this, portName, 9600);
  print(Serial.list());
    
  noStroke();
  textSize(width/8);
  textAlign(CENTER);

  wKing = loadImage("King.png");
  bKing = loadImage("King1.png");
  wPawn = loadImage("Pawn.png");
  bPawn = loadImage("Pawn1.png");
  wKing.resize(width/8, height/8);
  bKing.resize(width/8, height/8);
  wPawn.resize(width/8, height/8);
  bPawn.resize(width/8, height/8);
  /*for android
   wKing.loadPixels();
   bKing.loadPixels();
   wPawn.loadPixels();
   bPawn.loadPixels();
   */
  startPosition();
}
void draw() {
  //myPort.write('1');
  //println("1"); //prints 1 in processing
  
  showBoard();
  if (gameOver) {
    fill(0, 255, 0);
    text("GAMEOVER", 0, height/2, width, height);
  }
}

void showPhysBoard() {
  int counter = -1;
  for (int i = 0; i<8; i++) {
    for (int j = 0; j<8; j++) {
      counter++;
      //if (lastBoard[j][i] != board[j][i]) {
         if (board[j][i] != null) {
         if (board[j][i] == wPawn) {
            myPort.write("<wP," + str(counter) + ">");
            delay(30);
          }
          else if (board[j][i] == wKing) {
            // send piece type j, i     }
            myPort.write("<wK," + str(counter) + ">");
          }
          else if (board[j][i] == bKing) {
            // send piece type j, i
           myPort.write("<bK," + str(counter) + ">");
          }
          else if (board[j][i] == bPawn) {
            // send piece type j, i
            myPort.write("<bP," + str(counter) + ">");
          }
          delay(10);
        } else {
           myPort.write("<off," + str(counter) + ">");
           delay(30);
        }
      //}
      
    }
  }
}

void showBoard() {
  if (init) {
    showPhysBoard();
    init = false;
  }
  for (int i = 0; i<8; i++) {
    for (int j = 0; j<8; j++) {
      if ((i+j)%2 == 0) fill(255, 206, 158);
      else fill(209, 139, 71);
      rect(i*width/8, j*height/8, width/8, height/8);//chessboard
      
      if (board[j][i] != null) {
        image(board[j][i], i*width/8, j*height/8);//piece 
      }
      if (click) {
        
        if (validMove(down, right, j, i, turn, board)) {
          fill(255, 0, 0, 100);//highlight posibble moves in red
          rect(i*width/8, j*height/8, width/8, height/8);
        }
        if (j == down && i == right && board[j][i] != null) {
          fill(0, 0, 255, 100);//highlight piece in blue
          rect(i*width/8, j*height/8, width/8, height/8);
        }
      }
    }
  }
}

//void recvWithEndMarker() {
  
//  static byte ndx = 0;
//  char endMarker = '\n';
//  char rc;
       
        //if(wPawn != endMarker )
void mousePressed() {
  if (gameOver) startPosition();
  if (click) {
    down1 = round(mouseY / (height/8)-0.5);
    right1 = round(mouseX / (width/8)-0.5);
    if (validMove(down, right, down1, right1, turn, board)) {
      board = movePiece(down, right, down1, right1, board);//move piece
      showPhysBoard();
      click = false;
    } else {//change piece
      down = down1;
      right = right1;
      click = true;
    }
  } else {
    down = round(mouseY / (height/8)-0.5);
    right = round(mouseX / (width/8)-0.5);
    click = true;
  }
}
void startPosition() {
  board = new PImage[8][8];
  
  lastBoard = new PImage[8][8];

  board[0][1] = bPawn;
  board[0][3] = bPawn;
  board[0][5] = bPawn; 
  board[0][7] = bPawn;
  board[1][0] = bPawn;
  board[1][2] = bPawn;
  board[1][4] = bPawn;
  board[1][6] = bPawn;
  board[2][1] = bPawn;
  board[2][3] = bPawn;
  board[2][5] = bPawn; 
  board[2][7] = bPawn;

  board[5][0] = wPawn;
  board[5][2] = wPawn;
  board[5][4] = wPawn;
  board[5][6] = wPawn;
  board[6][1] = wPawn;
  board[6][3] = wPawn;
  board[6][5] = wPawn;
  board[6][7] = wPawn;
  board[7][0] = wPawn;
  board[7][2] = wPawn;
  board[7][4] = wPawn;
  board[7][6] = wPawn;

  //global variables
  promote = false;
  down=right=down1=right1=-1;
  click = false;
  turn = WHITE;
  gameOver = false;
  doubleJump = false;
}
PImage[][] movePiece(int i0, int j0, int i1, int j1, PImage[][] Board) {
  if (Board[i0][j0] == wPawn) {//promote
    if (i1 == 0) {
      Board[i0][j0] = wKing;
      promote = true;
      doubleJump = false;
    }
  } else if (Board[i0][j0] == bPawn) {//promote
    if (i1 == 7) {
      Board[i0][j0] = bKing;
      promote = true;
      doubleJump = false;
    }
  }
  Board[i1][j1] = Board[i0][j0];//move piece
  Board[i0][j0] = null;//remove original piece
  if (abs(j0 - j1) == 2) {//jump
    Board[(i0 + i1)/2][(j0 + j1)/2] = null;
    if (!promote) {//can jump again
      if (validMove(i1, j1, i1+2, j1+2, turn, Board) || validMove(i1, j1, i1+2, j1-2, turn, Board) ||
        validMove(i1, j1, i1-2, j1+2, turn, Board) || validMove(i1, j1, i1-2, j1-2, turn, Board)) {
        turn = !turn;
        doubleJump = true;
        p0 = i1;
        p1 = j1;
      } else {
        doubleJump = false;
      }
    }
  }
  promote = false;
  if(mustJump(!turn)){
    jumping = true;
  }else{
    jumping = false;
  }
  if (finish(!turn)) {//no legal moves
    gameOver = true;
  }
  turn = !turn;
  return Board;
}
boolean finish(boolean side) {//no valid moves
  for (int k = 0; k<8; k++) {
    for (int l = 0; l<8; l++) {
      if (side == WHITE) {
        if (notWhite(l, k, board))
          continue;
      } else if (notBlack(l, k, board)) {
        continue;
      }
      for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
          if (validMove(l, k, i, j, side, board)) return false;
        }
      }
    }
  }
  return true;
}
boolean mustJump(boolean side) {
  for (int k = 0; k<8; k++) {
    for (int l = 0; l<8; l++) {
      if (side == WHITE) {
        if (notWhite(l, k, board))
          continue;
      } else if (notBlack(l, k, board)) {
        continue;
      }
      for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
          if (validMove(l, k, i, j, side, board) && abs(l-i)==2) return true;
        }
      }
    }
  }
  return false;
}
boolean validMove(int down, int right, int down1, int right1, boolean side, PImage[][] Board) {
  if (down > 7 ||  down < 0 || down1 > 7 ||  down1 < 0 || right > 7 ||  right < 0 || right1 > 7 ||  right1 < 0) {
    return false;
  }
  if(doubleJump){
    if(down!=p0 || right != p1 || abs(right1-right) != 2) return false;
  }
  if(jumping){
    if(abs(right1-right) != 2) return false;
  }
  if (side == WHITE) {//white
    if (Board[down][right] == wPawn) {
      if (abs(right1 - right) == 1 && down1 == down-1 && Board[down1][right1] == null) { // move forward 1
        return true;
      }
      if (abs(right1 - right) == 2 && down1 == down-2 && Board[down1][right1] == null && 
        black(down-1, (right + right1)/2, Board)) { //jump
        return true;
      }
    } else if (Board[down][right] == wKing) {
      if (abs(right1 - right) == 1 && abs(down1-down) == 1 && Board[down1][right1] == null) { // move forward 1
        return true;
      }
      if (abs(right1 - right) == 2 && abs(down1-down) == 2 && Board[down1][right1] == null 
        && black((down+down1)/2, (right + right1)/2, Board)) { //jump
        return true;
      }
    }
  } else {
    if (Board[down][right] == bPawn) {
      if (abs(right1 - right) == 1 && down1 == down+1 && Board[down1][right1] == null) { // move forward 1
        return true;
      }
      if (abs(right1 - right) == 2 && down1 == down+2 && Board[down1][right1] == null && 
        white(down+1, (right + right1)/2, Board)) { //jump
        return true;
      }
    } else if (Board[down][right] == bKing) {
      if (abs(right1 - right) == 1 && abs(down1-down) == 1 && Board[down1][right1] == null) { // move forward 1
        return true;
      }
      if (abs(right1 - right) == 2 && abs(down1-down) == 2 && Board[down1][right1] == null && 
        white((down+down1)/2, (right + right1)/2, Board)) { //jump
        return true;
      }
    }
  }
  return false;
}
boolean black (int down1, int right1, PImage[][] Board) {
  return (Board[down1][right1] == bPawn || Board[down1][right1] == bKing);
}
boolean white (int down1, int right1, PImage[][] Board) {
  return (Board[down1][right1] == wPawn || Board[down1][right1] == wKing);
}
boolean notBlack (int down1, int right1, PImage[][] Board) {
  return (white(down1, right1, Board) || Board[down1][right1] ==null);
}
boolean notWhite (int down1, int right1, PImage[][] Board) {
  return (black(down1, right1, Board) || Board[down1][right1] ==null);
}
