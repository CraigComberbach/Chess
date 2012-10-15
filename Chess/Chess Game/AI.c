#include <stdio.h>
#include <stdlib.h>

int Number_of_Legal_Moves(char grid[8][8][33], char pieceTranslator[33], char king);

int Number_of_Legal_Moves(char grid[8][8][33], char pieceTranslator[33], char king)
{
    int total = 0,
        x,
        y,
        z;

    for(x = 0; x < 8; ++x)
        for(y = 0; y < 8; ++y)
            for(z = 1; z < 33; ++z)
                if((sameSide(king, pieceTranslator[z])) && (grid[x][y][z] == 'L'))
                    ++total;

    return total;
}
