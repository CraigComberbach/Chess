#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

extern void printChessBoard(char grid[8][8][33], char pieceTranslator[33]);
extern void horizontalLine(short int length);
extern void legalDisplay(char grid[8][8][33], int piece);
extern void Print_Chess_Board_with_Legal(char grid[8][8][33], char pieceTranslator[33], int piece);

#endif // DISPLAY_H_INCLUDED
