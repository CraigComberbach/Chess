#ifndef VALIDMOVE_H_INCLUDED
#define VALIDMOVE_H_INCLUDED

extern void legalChessMoves(char grid[8][8][33], char status[33], char pieceTranslator[33]);
char judge(char attacker, char defender);
extern void rowColumnTest(char grid[8][8][33], int x, int y, char pieceTranslator[32]);
extern void diagonalTest(char grid[8][8][33], int x, int y, char pieceTranslator[32]);
extern void knightTest(char grid[8][8][33], int x, int y, char pieceTranslator[32]);
extern void kingTest(char grid[8][8][33], int x, int y, char pieceTranslator[33]);
extern void pawnTest(char grid[8][8][33], int x, int y, char status[33], char pieceTranslator[33]);
extern void twoKings(char grid[8][8][33], char pieceTranslator[33]);
extern void castling(char grid[8][8][33], char status[33], char pieceTranslator[33]);
extern void enPassant(char grid[8][8][33], char status[33]);
extern void check(char grid[8][8][33], char status[33], char pieceTranslator[33]);
extern int  sameSide(char piece1, char piece2);
extern void basicMoveValidation(char grid[8][8][33], char status[33], char pieceTranslator[33]);

#endif // VALIDMOVE_H_INCLUDED
