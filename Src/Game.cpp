// #include<iostream.h>		// Yup, this was pre ISO C++.
#include<iostream>
#include<assert.h>
using namespace std;
#include "Board.h"
#include "Game.h"
extern int outputOK;

game::game() :
  currbrd(),          // init board  
  plyBlack(2),
  plyWhite(2)
{
/*  currbrd.brd[3][3] ='w';
  currbrd.brd[3][4] ='b';
  currbrd.brd[4][3] ='w';
  currbrd.brd[4][4] ='b';
  currbrd.brd[5][3] ='w';
  currbrd.brd[5][4] ='b';
  currbrd.brd[6][1] ='b';
  currbrd.brd[6][2] ='b';
  currbrd.brd[6][3] ='b';
  currbrd.brd[6][4] ='b';
  currbrd.brd[6][5] ='b';
  currbrd.brd[7][1] ='w';
  currbrd.brd[7][2] ='w';
  currbrd.brd[7][3] ='w';
  currbrd.brd[7][4] ='w';
  currbrd.brd[7][5] ='w';
  currbrd.brd[7][6] ='w';
  cout << currbrd;
  ComputerAMove('w');
  cout << currbrd;
  exit(1);  */


  cout << currbrd;
  cout << "Who goes first? Computer(c), User(u), or Comp vs Comp(v): ";
  char ans; cin >> ans;
  cout << "What ply[2 or bigger]? ";
  cin >> plyBlack;
  plyWhite = plyBlack;
  int conskipped = 0;
  switch (ans)
  {
  case 'c':
    while (1)
    {
      if (!ComputerBlackMove()) conskipped = 0; else conskipped++;
      if (conskipped == 2) break;
      cout << currbrd << endl;
      if (!PlayerMove('w')) conskipped = 0; else conskipped++;
      if (conskipped == 2) break;
      cout << currbrd << endl;
    }
    break;
  case 'u':
    while (1)
    {
      if (!PlayerMove('b')) conskipped = 0; else conskipped++;
      if (conskipped == 2) break;
      cout << currbrd << endl;
      if (!ComputerWhiteMove()) conskipped = 0; else conskipped++;
      if (conskipped == 2) break;
      cout << currbrd << endl;
    }
    break;
  case 'v':
    cout << "What ply for white computer? ";
    cin >> plyWhite;
    while (1)
    {
      if (!ComputerBlackMove()) conskipped = 0; else conskipped++;
      if (conskipped == 2) break;
      cout << currbrd << endl;
      if (!ComputerWhiteMove()) conskipped = 0; else conskipped++;
      if (conskipped == 2) break;
      cout << currbrd << endl;
    }
    break;
  }
  currbrd.PrintScore();
}


game::game(const char* state, char player, int ply) :
  currbrd(state),
  plyBlack(ply),
  plyWhite(ply)
{
  int skipped = 0;
  if (player == 'b')
    skipped = ComputerBlackMove();
  else
    skipped = ComputerWhiteMove();

  // print out the board.
  for (int y=0; y<8; y++)
  {
    for (int x=0; x<8; x++)
	{
      char piece = (currbrd.brd[x][y] == '-') ? 'e' : currbrd.brd[x][y];
      cout << piece;
    }
  }
  cout << " ";

  // print out the move
  if (skipped)
  {
    cout << "pass";
  }
  else
  {
    cout << char(currbrd.movex + 'a');
	cout << char((7 - currbrd.movey) + '1');
  }
}

game::game(const char* state, char player, int testXmove, int testYmove) :
  currbrd(state),
  plyBlack(2),
  plyWhite(2)
{
  int illegal = currbrd.Move(testXmove, testYmove, player);
  if (illegal)
    cout << "invalid ";
  else
    cout << "valid ";

  // print out the board.
  for (int y=0; y<8; y++)
  {
    for (int x=0; x<8; x++)
	{
      char piece = (currbrd.brd[x][y] == '-') ? 'e' : currbrd.brd[x][y];
      cout << piece;
    }
  }
}

int game::PlayerMove(char player)
{
  int x, y;
  cout << "Make your move x[0..7] y[0..7]: ";
  cin >> x;
  cin >> y;
  int skipped = currbrd.Move(x, y, player);
  return skipped;   // this updates the board.
}


// returns true if skipped turn
int game::ComputerBlackMove()
{
  int alpha = NEGINFINITY;
  int beta  = POSINFINITY;
  currbrd.Reset();

  int value = currbrd.Minimax( 'b', plyBlack, alpha, beta);  // minimax returns the move made in movex and movey
  if ((currbrd.movex == -1) || (currbrd.movey == -1) || (currbrd.brd[currbrd.movex][currbrd.movey] != '-'))
  {
    if (outputOK)
      cout << "Computer Black can't go!! Skipping turn..." << endl;
    return 1;
  }
  if (outputOK)
    cout << "Computer Black moved to " << currbrd.movex << " " << currbrd.movey << endl;
  currbrd.Move(currbrd.movex, currbrd.movey, 'b');
  return 0;
}


int game::ComputerWhiteMove()
{
  int alpha = NEGINFINITY;
  int beta  = POSINFINITY;
  currbrd.Reset();

  int value = currbrd.Minimax( 'w', plyWhite, alpha, beta);  // minimax returns the move made in movex and movey
  if ((currbrd.movex == -1) || (currbrd.movey == -1) || (currbrd.brd[currbrd.movex][currbrd.movey] != '-'))
  {
    if (outputOK)
      cout << "Computer White can't go!! Skipping turn..." << endl;
    return 1;
  }
  if (outputOK)
    cout << "Computer White moved to " << currbrd.movex << " " << currbrd.movey << endl;
  currbrd.Move(currbrd.movex, currbrd.movey, 'w');
  return 0;
}


game::~game()
{
}
