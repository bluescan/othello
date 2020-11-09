#ifndef _board_h
#define _board_h


#define NEGINFINITY 0x80000000		// -2147483648. Avoid VS bug. I reported it here: https://social.msdn.microsoft.com/Forums/vstudio/en-US/c3029dd1-27a2-4e74-a257-1ca01458d294/the-type-of-integer-literal-2147483648?forum=vclanguage
#define POSINFINITY  2147483647
#define MAX(x, y) ((x > y) ? x : y)
#define MIN(x, y) ((x < y) ? x : y)


struct board
{
  char brd[8][8]; // '-'=blank 'b'=black 'w'=white
  enum states { invalid, valid };
  int state;
  int currx;
  int curry;
  int movex;  // after minimax or FindNextBoard is called these will contain the move that was suggested
  int movey;
  void Reset();
  board FindNextBoard(char who);
  int Move(int x, int y, char who);
  int Minimax( char col, int ply, int alpha, int beta );
  // col = 'w' => maximizing.  ply = 1 + depth
  int Evaluate();
  void PrintScore();
  friend ostream& operator<<(ostream&, const board&);
  board();
  board(const char* state);
private:
  char Opposite(char c) { return c == 'w' ? 'b' : 'w'; }
  int ChangeLine(int incx, int incy, char colour);
  // returns true if anything flipped starting from currx, curry
};

ostream& operator<<(ostream&, const board&);

#endif
