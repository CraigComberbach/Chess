#ifndef TESTCODE_H_INCLUDED
#define TESTCODE_H_INCLUDED

extern void test();
extern void clearBoard(char grid[8][8][33]);
extern void legalDisplay(char grid[8][8][33], int piece);
extern int  validMoves(char grid[8][8][33], int piece);
extern void statusDisplay(char grid[8][8][33], char status[33]);

#endif // TESTCODE_H_INCLUDED
