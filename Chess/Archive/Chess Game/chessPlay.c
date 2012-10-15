#include <stdio.h>
#include "chess.h"

void pawnPromotion(char grid[8][8][33], char pieceTranslator[33])
{
    //Pawn Promotion  http://www.chessvariants.org/d.chess/pawnfaq.html
    //If a pawn is on the opposite side it can promote to a Queen, Bishop, Rook or Knight of the same case

    int x;
    char promotion;

    for(x = 0; x < 8; ++x)
    {
        //If the piece is a pawn on row zero than enter promotion scripts
        if(pieceTranslator[(int)grid[x][0][0]] == 'p')
        {
            do
            {
                printf("\nChoose what the pawn promotes to (q, b, n or r): ");//Prompt for a change
                promotion = getch();
            }
            while((promotion != 'q') && (promotion != 'b') && (promotion != 'n') && (promotion != 'r'));//Only accept proper input
            pieceTranslator[(int)grid[x][0][0]] = promotion;//Assign the users entry to the pawn
        }
        //If the piece is a PAWN on row seven then enter a slightly different promotion script
        else if(pieceTranslator[(int)grid[x][7][0]] == 'P')
        {
            do
            {
                printf("\nChoose what the pawn promotes to (Q, B, N or R): ");//Prompt for a change
                promotion = getch();
            }
            while((promotion != 'Q') && (promotion != 'B') && (promotion != 'N') && (promotion != 'R'));//Only accept proper input
            pieceTranslator[(int)grid[x][7][0]] = promotion;//Assign the users entry to the pawn
        }
    }

    return;
}
