#include <stdio.h>
#include <stdlib.h>
#include "chess.h"

#define WIDTH   17

void printChessBoard(char grid[8][8][33], char pieceTranslator[33]);
void horizontalLine(short int length);
void legalDisplay(char grid[8][8][33], int piece);
void Print_Chess_Board_with_Legal(char grid[8][8][33], char pieceTranslator[33], int piece);

//Prints the contents of the board onto the display
void printChessBoard(char grid[8][8][33], char pieceTranslator[33])
{
    int     x, y;

    //Clear screen for better formating
//    system("cls");

    //Creats the alphabetical coordinates
    printf("\n   A B C D E F G H");

    //Makes the top of the window space
    putchar('\n'); //New line after each segment
    horizontalLine(WIDTH);
    putchar('\n'); //New line after each segment

    //Prints out the new table after shifting
    for(y = 0; y < 8; y++)
    {
        printf("%d |",8 - y);//Creates the numerical coordinates

        //Lays down the grid, complete with pieces
        for(x = 0; x < 8; x++)
            if(grid[x][y][0] == 0)
                if(((x + y) % 2) == 0)
                    printf(":|");//Blank Black square
                else
                    printf(" |");//Blank white square
            else
                printf("%c|", pieceTranslator[(int)grid[x][y][0]]);

        printf(" %d",8 - y);//Creates the numerical coordinates
        putchar('\n'); //New line after each segment
        horizontalLine(WIDTH);
        putchar('\n'); //New line after each segment
    }

    printf("   A B C D E F G H");//Creats the alphabetical coordinates
    //For formating
    putchar('\n');
    putchar('\n');

    return;
}

void horizontalLine(short int length)
{
    putchar(' ');
    putchar(' ');
    for(;length > 0; --length)
        putchar('-');

    return;
}

void legalDisplay(char grid[8][8][33], int piece)
{
    int     x, y;

    //Creats the alphabetical coordinates
    printf("\n   A B C D E F G H");

    //Makes the top of the window space
    putchar('\n'); //New line after each segment
    horizontalLine(WIDTH);
    putchar('\n'); //New line after each segment

    //Prints out the new table after shifting
    for(y = 0; y < 8; y++)
    {
        printf("%d |",8 - y);//Creates the numerical coordinates

        //Lays down the grid, complete with pieces
        for(x = 0; x < 8; x++)
            if(grid[x][y][piece] == 'L')
                printf("%c|", grid[x][y][piece]);
            else if(((x + y) % 2) == 0)
                    printf(":|");//Blank Black square
                else
                    printf(" |");//Blank white square

        printf(" %d",8 - y);//Creates the numerical coordinates
        putchar('\n'); //New line after each segment
        horizontalLine(WIDTH);
        putchar('\n'); //New line after each segment
    }

    //Creats the alphabetical coordinates
    printf("   A B C D E F G H");

    //For formating
    putchar('\n');
    putchar('\n');

    return;
}

void Print_Chess_Board_with_Legal(char grid[8][8][33], char pieceTranslator[33], int piece)
{
    int x,
        y;

    //Clear the screen
//    system("cls");

    //Board display
    //Creats the alphabetical coordinates
    printf("\n   A B C D E F G H\t   A B C D E F G H");

    //Makes the top of the window space
    putchar('\n'); //New line after each segment
    horizontalLine(WIDTH);
    putchar('\t'); //tab between boards
    horizontalLine(WIDTH);
    putchar('\n'); //New line after each segment

    //Prints out the new table after shifting
    for(y = 0; y < 8; y++)
    {
        //Board layout
        printf("%d |",8 - y);//Creates the numerical coordinates

        //Lays down the grid, complete with pieces
        for(x = 0; x < 8; x++)
            if(grid[x][y][0] == 0)
                if(((x + y) % 2) == 0)
                    printf(":|");//Blank Black square
                else
                    printf(" |");//Blank white square
            else
                printf("%c|", pieceTranslator[(int)grid[x][y][0]]);

        printf(" %d",8 - y);//Creates the numerical coordinates

        //Legal
        printf("\t%d |",8 - y);//Creates the numerical coordinates

        //Lays down the grid, complete with pieces
        for(x = 0; x < 8; x++)
            if(grid[x][y][piece] != 'I')
                printf("L|");
            else if(((x + y) % 2) == 0)
                    printf(":|");//Blank Black square
                else
                    printf(" |");//Blank white square

        printf(" %d",8 - y);//Creates the numerical coordinates

        //Make the bottom of the window
        putchar('\n'); //New line after each segment
        horizontalLine(WIDTH);
        putchar('\t'); //tab between boards
        horizontalLine(WIDTH);
        putchar('\n'); //New line after each segment

    }
    //Creats the alphabetical coordinates
    printf("   A B C D E F G H\t   A B C D E F G H");

    //For formating
    putchar('\n');
    putchar('\n');

    return;
}
