//#include<iostream.h>		// Yup, this was pre ISO C++.
#include<iostream>
#include<assert.h>
extern int outputOK;
using namespace std;
#include "Board.h"

// remember..arrays are stored row-wise in C++.  last subscript should vary fastest
board::board()
{
  for (int x=0; x<8; x++)
    for (int y=0; y<8; y++)
      brd[x][y] = '-';
  brd[4][3] = 'b';
  brd[3][4] = 'b';
  brd[3][3] = 'w';
  brd[4][4] = 'w';
  movex = -1;
  movey = -1;
  Reset();
}


board::board(const char* initBrd)
{
  for (int x=0; x<8; x++)
  {
    for (int y=0; y<8; y++)
	{
      char place = initBrd[y*8+x];
        if (place == 'e')
          brd[x][y] = '-';
        else
          brd[x][y] = place;
    }
  }
  movex = -1;
  movey = -1;
  Reset();
}


void board::Reset()
{
  state = valid;
  curry = -1;
  currx = 0;
}


int board::ChangeLine(int incx, int incy, char colour)
// change ine (if possible) starting from movex, movey
{
  int foundopp = 0;
  int cx = movex + incx, cy = movey + incy;
  while ((cx <= 7) && (cx >=0) && (cy <=7) && (cy >= 0))
  {
    if (brd[cx][cy] == '-') return 0;
    if (brd[cx][cy] == Opposite(colour)) foundopp = 1;
    if (brd[cx][cy] == colour)
    {
      if (foundopp == 1)
        break;
      else
        return 0;
    }
    cx += incx;
    cy += incy;
  }
  if ((cx <0) || (cx > 7) || (cy < 0) || (cy > 7)) return 0;
  brd[movex][movey] = colour; // this should be somewhere else
  cx -= incx;
  cy -= incy;
  while ((cx != movex) || (cy != movey))
  {
    brd[cx][cy] = colour;
    //if (outputOK)
    //  cout << "Flipped " << cx << " " << cy << endl;
    cx -= incx;
    cy -= incy;
  }
  return 1;
}
    

board board::FindNextBoard(char whoseturn) // whoseturn must be 'w' or 'b'
{
  board rb(*this);
  rb.Reset();
  int found = 0;
  while (!found)
  {
    if (++curry == 8)
    {
      curry = 0;
      if (++currx == 8)
	  {
		  state = invalid;
		  return rb;
	  }
    }    // now we are at pos we want to check
    if (rb.brd[currx][curry] == '-')  // if able to go here
    {
      rb.movex = currx;
      rb.movey = curry;
      found += rb.ChangeLine ( 1,  0, whoseturn);  // rets true if changed
      found += rb.ChangeLine ( 1, -1, whoseturn);
      found += rb.ChangeLine ( 0, -1, whoseturn);
      found += rb.ChangeLine (-1, -1, whoseturn);
      found += rb.ChangeLine (-1,  0, whoseturn);
      found += rb.ChangeLine (-1,  1, whoseturn);
      found += rb.ChangeLine ( 0,  1, whoseturn);
      found += rb.ChangeLine ( 1,  1, whoseturn);
    }
  }

  if (!found)
	  state = invalid;

  return rb;
}


int board::Move(int x, int y, char who)  // ret 1 if illegal;
{
  if ((x == -1) || (y == -1))
	  return 1;

  if (brd[x][y] != '-')
  {
    if (outputOK)
      cout << "Error: illegal move... skipping." << endl;
    return 1;
  }
  int found = 0;
  movex = x;
  movey = y;
  found =  ChangeLine ( 1,  0, who);  // rets true if changed
  found += ChangeLine ( 1, -1, who);
  found += ChangeLine ( 0, -1, who);
  found += ChangeLine (-1, -1, who);
  found += ChangeLine (-1,  0, who);
  found += ChangeLine (-1,  1, who);
  found += ChangeLine ( 0,  1, who);
  found += ChangeLine ( 1,  1, who);
  if (!found)
  {
    if (outputOK)
      cout << "Error: illegal move... skipping." << endl;
    return 1;
  }
  return 0;
}


int board::Minimax(char colour, int ply, int alpha, int beta) // white is maximizing
{
//  cout << "Minimax stub called with " << colour << " ply ";
//  cout << ply << "  alpha beta: " << alpha << " " << beta << endl;
//  int reteval;
//  int tx,ty;
  board child;
  if (!(--ply)) { return Evaluate(); }
  if (colour == 'b')   // maximizing layer
  {
	int value = NEGINFINITY;
	movex = movey = -1;
    child = FindNextBoard('b');  // whites turn
	if (state == valid)
	{
		movex = child.movex;
		movey = child.movey;
	}
    while (state == valid)
    {
	  int thismovex = child.movex;
	  int thismovey = child.movey;
	  int childValue = child.Minimax('w', ply, alpha, beta);
	  if (childValue > value)
	  {
		  value = childValue;
          movex = thismovex;
          movey = thismovey;
	  }
	  alpha = MAX(value, alpha);
      if (beta <= alpha)
		  break;
      child = FindNextBoard('b');
    }
    return value;
  }
  else // minimizing layer.
  {
	int value = POSINFINITY;
	movex = movey = -1;
    child = FindNextBoard('w');  // blacks turn
	if (state == valid)
	{
		movex = child.movex;
		movey = child.movey;
	}
    while (state == valid)
    {
	  int thismovex = child.movex;
	  int thismovey = child.movey;
	  int childValue = child.Minimax('b', ply, alpha, beta);
	  if (childValue < value)
	  {
        value = childValue;
        movex = thismovex;
        movey = thismovey;
	  }
	  beta = MIN(beta, value);
      if (beta <= alpha)
        break;
      child = FindNextBoard('w');
    }
    return value;
  }
}


void board::PrintScore()
{
  int black=0, white=0;
  for (int x=0; x<8; x++)
    for (int y=0; y<8; y++)
      if (brd[x][y] == 'b')
        black++;
      else if (brd[x][y] == 'w')
        white++;
  cout << "\nScore    Black:" << black << "   White:" << white << endl;
}


int positionalScore[8][8] =
{
	{ 100,	-10,	10,		6,		6,		10,		-10,	100 },
	{ -10,	-25,	-5,		-3,		-3,		-5,		-25,	-10	},
	{ 10,	-5,		7,		4,		4,		7,		-5,		10	},
	{ 6,	-3,		4,		0,		0,		4,		-3,		6	},
	{ 6		-3,		4,		0,		0,		4,		-3,		6	},
	{ 10,	-5,		7,		4,		4,		7,		-5,		10	},
	{ -10,	-25,	-5,		-3,		-3,		-5,		-25,	-10	},
	{ 100,	-10,	10,		6,		6,		10,		-10,	100 }
};


int board::Evaluate()
{
  int blackgoodness = 0;

  // We're going to try favouring raw piece count for the last 14 moves.
  int empty = 0;
  for (int x=0; x<8; x++)
    for (int y=0; y<8; y++)
      if (brd[x][y] == '-')
        empty++;

  if (empty <= 10)
  {
	  for (int x=0; x<8; x++)
		for (int y=0; y<8; y++)
		  if (brd[x][y] == 'b')
            blackgoodness++;
		  else if (brd[x][y] == 'w')
            blackgoodness--;
  }
  else
  {
    for (int x=0; x<8; x++)
      for (int y=0; y<8; y++)
        if (brd[x][y] == 'b')
          blackgoodness += positionalScore[x][y];
        else if (brd[x][y] == 'w')
          blackgoodness -= positionalScore[x][y];
  }
  return blackgoodness;   // >0 good for black.  <0 good for white
}

  
ostream& operator<<(ostream& ost, const board& b)
{
  for (int y=0; y<8; y++)
  {
    for (int x=0; x<8; x++)
      ost << (b.brd[x][y]);
    ost << endl;
  }
  return ost;
}

