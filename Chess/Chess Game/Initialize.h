#ifndef INITIALIZE_H_INCLUDED
#define INITIALIZE_H_INCLUDED

extern void initializeBoard(char grid[8][8][33]);
extern void initializeLegal(char grid[8][8][33]);
extern void initializeStatus(char status[33]);
extern void initializePieces(char pieceTranslator[33]);
extern void initializeGameVariables(char gameVariables[21]);
extern void initializeAll(char grid[8][8][33], char status[33], char pieceTranslator[33], char gameVariables[21]);

#endif // INITIALIZE_H_INCLUDED
