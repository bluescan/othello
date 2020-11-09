// #include<iostream.h>		// Yup, this was pre ISO C++.
#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;
#include "Board.h"
#include "Game.h"
int outputOK = 1;

int main(int argc, char** argv)
{
  if (argc == 4)
  {
    char player = (argv[2][0] == 'b') ? 'b' : 'w';
	int ply = stoi(argv[3]);
	outputOK = 0;
    game g(argv[1], player, ply);
	return 0;
  }
  else if (argc == 5)
  {
	const char* board = argv[1];
    char player = (argv[2][0] == 'b') ? 'b' : 'w';
	int testXmove = stoi(argv[3]);
	int testYmove = stoi(argv[4]);
	outputOK = 0;
    game g(board, player, testXmove, testYmove);
	return 0;
  }
  cout << "Othello V1.0 by Tristan" << endl << endl;

//  b.brd[1][4] = 'w';
//  b.brd[2][3] = 'b';
//  b.brd[3][2] = 'b';
//  b.brd[3][5] = 'w';
//  b.brd[4][2] = 'b';
//  b.brd[4][5] = 'w';
//  b.brd[5][2] = 'b';
//  b.brd[5][3] = 'b';
//  b.brd[5][4] = 'b';
//  b.brd[6][3] = 'w';
//  b.brd[7][1] = 'b';
//  b.brd[7][2] = 'w';

//  cout << "Original board" << endl;
//  cout << b << endl;
//  board newb;
//  newb = b.FindNextBoard('b');
//  while(b.state == board::valid)
//  {
//    cout << newb << endl;
//    newb = b.FindNextBoard('b');
//  }
  game g;

  cout << "Press return to exit." << endl;
  fflush(stdin);
  int c = getchar();
  cout << c;
}



