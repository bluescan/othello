#ifndef _game_h
#define _game_h


#include "Board.h"


class game
{
  board currbrd;
  int plyBlack;
  int plyWhite;
public:
  game();
  game(const char* state, char player, int ply);                       // Compute a single move.
  game(const char* state, char player, int testXmove, int testYmove);  // Test if move can be made.
  ~game();
  int PlayerMove(char player);
  int ComputerBlackMove();
  int ComputerWhiteMove();
};


#endif

