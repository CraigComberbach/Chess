#ifndef CHESSPLAY_H_INCLUDED
#define CHESSPLAY_H_INCLUDED

//External Function Prototypes
extern void pawnPromotion(char grid[8][8][33], char pieceTranslator[33]);
extern int getPieceFromCoordinates(char grid[8][8][33], char pieceTranslator[33]);
extern char Current_Turn();
extern void Initialize_Chess_Play();
extern void Move_Piece(char grid[8][8][33], int piece, char pieceTranslator[33], char status[32]);
extern struct coordinates Get_Coordinates(char grid[8][8][33], int piece);

//Structure
struct globalStatus
{
    unsigned char turn:1;
    unsigned char checkMate:1;
};

//Stores a pair of coordinates
struct coordinates
{
    unsigned char   x,
                    y;
};

//Global Variables
extern struct globalStatus boardStatus;

#endif // CHESSPLAY_H_INCLUDED
