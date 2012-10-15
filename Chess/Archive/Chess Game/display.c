#include <stdio.h>
#include <stdlib.h>
#include "chess.h"

//Prints the contents of the board onto the display
void printChessBoard(char grid[8][8][33], char pieceTranslator[33])
{
    int     x, y;

    //Clear screen for better formating
//    system("cls");

    //Makes the top of the window space
    horizontalLine(width);

    //Prints out the new table after shifting
    for(y = 0; y < 8; y++)
    {
        putchar('|');//Left Side of window
        for(x = 0; x < 8; x++)
            if(grid[x][y][0] == 0)
                if(((x + y) % 2) == 0)
                    printf(":|");//Blank Black square
                else
                    printf(" |");//Blank white square
            else
                printf("%c|", pieceTranslator[(int)grid[x][y][0]]);
        horizontalLine(width);
    }

    //For formating
    putchar('\n');

    return;
}

void printExpandedChessBoard(char grid[8][8][33])
{
    //Need an expanded version that will display piece number as well
    int     x, y;

    //Clear screen for better formating
//    system("cls");

    //Makes the top of the window space
    horizontalLine(width + 8);

    //Prints out the new table after shifting
    for(y = 0; y < 8; y++)
    {
        putchar('|');//Left Side of window
        for(x = 0; x < 8; x++)
            if((grid[x][y][0] == ' ') && (((x + y) % 2) == 0))
                printf("::|");//Blank Black square
            else
                printf("%c|", grid[x][y][0]);
        horizontalLine(width + 8);
    }

    //For formating
    putchar('\n');

    return;
}

void horizontalLine(short int length)
{
    putchar('\n'); //New line after each segment

    for(;length > 0; --length)
        putchar('-');

    putchar('\n'); //New line after each segment

    return;
}
