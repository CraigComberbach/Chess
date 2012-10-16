#include <stdio.h>
#include <stdlib.h>
#include "initialize.h"
#include "display.h"
#include "validMove.h"
#include "chessPlay.h"

/*
White was chosen for human player to create a situation where the game is reacting to players movements
SCI-Net (Specfically Chess Intelligence - Net)
*/

/*
AI maximizes the ratio of total possible moves between Black and White. (This goes one turn into the game, without taking into account future turns)

eg. If piece A moves to location X, how many moves can I calculate from in this position, how many moves can my opponent move.

Taking a high value piece (Queen, Bishop, Rook and Knight) will be targeted for destruction as they have high mobility and would thus greatly diminish the opposing players number of moves
*/

/*Assumptions
-----------
1)Pieces 1-16(uppercase) will always be on the same team, just like 17-32(Lowercase) will be on the other
*/

/*
Grid[8][8][33]
grid[x][y][0]
-Physical layout of the board, detailing where all of the pieces are
-Pieces, instead of being stored as their type, are stored as unique numbers now (1-32)
-The reference to what the piece is, is stored in a different array
grid[x][y][1] to grid[x][y][32]
-The legal grids are referenced to the unique numbers of the piece (Piece 3 is grid[x][y][3])

status[22] keeps track of all of the pieces history (EG pawns and kings movement in the past), mostly just like the hasMoved structure.

gameVariables
-0 and 1 are the coordinates of the currently selected piece, "  " (Double space) is the none selected or initialized state
-2-20 are variable to expand into
*/

int main()
{
    //Initializes the playing grid at the start of a game, CAPITALS are player controlled (White), lowercase is ai controlled (Black)
    char    grid[8][8][33],
            status[32],
            pieceTranslator[33],
            gameVariables[21];

    //Start the game fresh
    initializeAll(grid, status, pieceTranslator, gameVariables);

    //Populate the universe with the full set of legal moves
    legalChessMoves(grid, status, pieceTranslator);

    Print_Chess_Board_with_Legal(grid,pieceTranslator,28);//King
    Print_Chess_Board_with_Legal(grid, pieceTranslator, 1);//Rook
/*
    while(!boardStatus.checkMate)
    {
        printChessBoard(grid, pieceTranslator);
        Move_Piece(grid, getPieceFromCoordinates(grid, pieceTranslator), pieceTranslator, status);
        legalChessMoves(grid, status, pieceTranslator);
    }
*/
//    Print_Chess_Board_with_Legal(grid,pieceTranslator,getPieceFromCoordinates(grid));//Generic


    return 0;
}
