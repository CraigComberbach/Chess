#include <stdio.h>
#include "chess.h"

void initializeStatus(char status[33])
{
    /*
    'V' for virgin, never moved
    'D' for double move (Pawns only)
    'M' for moved, indicates that in the past movement has occured
    'S' for Short Castle (For Rooks and Kings only)
    'L' for Long Castle (For Rooks and Kings only)
    'B' for both long and short castles (Kings only)
    */

    int loop;

    for(loop = 0; loop <= 32; ++loop)
        status[loop] = 'V';

    return;
}

//Initializes it all to I (Illegal), Guilty until proven innocent in this case!
void initializeLegal(char grid[8][8][33])
{
    short int   x,
                y,
                z;
    for(y = 0; y < 8; ++y)
        for(x = 0; x < 8; ++x)
            for(z = 1; z < 33; ++z)
                grid[x][y][z] = 'I';

    return;
}

//Assigns the initial values of each piece wrt the initial board setup
void initializePieces(char pieceTranslator[33])
{
    int loop;

    for(loop = 0; loop < 33; ++loop)
    {
        if(loop == 0)
            pieceTranslator[loop] = ' ';
        else if((loop == 1) || (loop == 8))
            pieceTranslator[loop] = 'R';
        else if((loop == 25) || (loop == 32))
            pieceTranslator[loop] = 'r';
        else if((loop == 2) || (loop == 7))
            pieceTranslator[loop] = 'N';
        else if((loop == 26) || (loop == 31))
            pieceTranslator[loop] = 'n';
        else if((loop == 3) || (loop == 6))
            pieceTranslator[loop] = 'B';
        else if((loop == 27) || (loop == 30))
            pieceTranslator[loop] = 'b';
        else if(loop == 5)
            pieceTranslator[loop] = 'Q';
        else if(loop == 29)
            pieceTranslator[loop] = 'q';
        else if(loop == 4)
            pieceTranslator[loop] = 'K';
        else if(loop == 28)
            pieceTranslator[loop] = 'k';
        else if((loop >= 9) && (loop <= 16))
            pieceTranslator[loop] = 'P';
        else if((loop >= 17) && (loop <= 24))
            pieceTranslator[loop] = 'p';
        else
            printf("\nOut of bounds on the initializePieces function\n");
    }

    return;
}

//Fills grid with a new game layout
void initializeBoard(char grid[8][8][33])
{
    char    type[] =   {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};

    int     x,
            y,
            z = 0;

    for(y = 0; y < 8; ++y)
        for(x = 0; x < 8; ++x)
            grid[x][y][0] = type[z++];

    return;

}

void initializeAll(char grid[8][8][33], char status[33], char pieceTranslator[33])
{
    initializeLegal(grid);
    initializeStatus(status);
    initializePieces(pieceTranslator);
    initializeBoard(grid);

    return;
}
