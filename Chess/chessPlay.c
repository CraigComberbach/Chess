#include <stdio.h>
#include "display.h"
#include "validMove.h"
#include "chessPlay.h"

//Global Variables
struct globalStatus boardStatus;

//Function prototypes
int Convert_Coordinate(char coordinate);
void pawnPromotion(char grid[8][8][33], char pieceTranslator[33]);
int getPieceFromCoordinates(char grid[8][8][33], char pieceTranslator[33]);
char Current_Turn();
void Initialize_Chess_Play();
void Move_Piece(char grid[8][8][33], int piece, char pieceTranslator[33], char status[32]);
int Get_First_Coordinate();
int Get_Second_Coordinate();
int Get_Total_Legal_Moves_For_Piece(char grid[8][8][33], int piece);
struct coordinates Get_Coordinates(char grid[8][8][33], int piece);

struct coordinates Get_Coordinates(char grid[8][8][33], int piece)
{
    struct coordinates  foundAt;
    int                 x,
                        y;

    //Initialize foundAt to a known bad location
    foundAt.x = 8;//8 does not exist on the board
    foundAt.y = 8;//8 does not exist on the board

    for(x = 0; x < 8; ++x)
    {
        for(y = 0; y < 8; ++y)
            if(grid[x][y][0] == piece)
            {
                foundAt.x = x;
                foundAt.y = y;
            }
    }

    return foundAt;
}
void Initialize_Chess_Play()
{
    boardStatus.turn = 0;//king goes first, then KING
    boardStatus.checkMate = 0;//No one is in checkmate
    return;
}

char Current_Turn()
{
    if(boardStatus.turn)
        return 'K';
    else
        return 'k';
}

//Allows the promotion of a pawn once it reaches the other side of the board
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

int getPieceFromCoordinates(char grid[8][8][33], char pieceTranslator[33])
{
    int     x,
            y;

    //Keep requesting coordinates until one with a potential move comes along
    do
    {
        printf("Please enter a pair of coordinates: ");

        while(x = Get_First_Coordinate(), y = Get_Second_Coordinate(), !sameSide(pieceTranslator[(int)grid[x][y][0]], Current_Turn()))
            printf("\nYou may only move your pieces.\n");
    }
    while(Get_Total_Legal_Moves_For_Piece(grid, grid[x][y][0]) == 0);

    return grid[x][y][0];
}

int Convert_Coordinate(char coordinate)
{
    switch(coordinate)
    {
        case '8':
        case 'A':
            return 0;
        case '7':
        case 'B':
            return 1;
        case '6':
        case 'C':
            return 2;
        case '5':
        case 'D':
            return 3;
        case '4':
        case 'E':
            return 4;
        case '3':
        case 'F':
            return 5;
        case '2':
        case 'G':
            return 6;
        case '1':
        case 'H':
            return 7;
    }
}

//This function moves one piece to another location as dictated by the legal moves available to that piece
void Move_Piece(char grid[8][8][33], int piece, char pieceTranslator[33], char status[32])
{
    int     newX = 0,
            newY = 0,
            oldX = 0,
            oldY = 0,
            x = 0,
            y = 0,
            foundFlag = 0,
            loop;

    Print_Chess_Board_with_Legal(grid, pieceTranslator, piece);

    //Get new location
    printf("Please enter a pair of target coordinates: ");

    //Sentinel - Must be a legal position to move to
    while(newX = Get_First_Coordinate(), newY = Get_Second_Coordinate(), grid[newX][newY][piece] == 'I')
        printf("\nYou must enter coordinates of a valid legal move\n\n");

    //Determine the pieces current location
    for(x = 0; (x < 8) && (!foundFlag); ++x)
    {
        for(y = 0; (y < 8) && (!foundFlag); ++y)
            if((int)grid[x][y][0] == piece)
            {
                oldX = x;
                oldY = y;
                foundFlag = 1;
            }
    }
    foundFlag = 0;

    //Place the current piece in its new location
    grid[newX][newY][0] = piece;

    //Remove the current piece from its old location
    grid[oldX][oldY][0] = 0;

    //Remove Double move status with the idea of cooperating with En Passant when it gets coded
    for(loop = 0; loop <= 32; ++loop)
    {
        if(status[loop] == 'D')//Once the piece has moved, all previous double moves need to be cleared to just moves, this is for checking for en-passant
            status[loop] = 'M';
    }

    //Ensure the piece is known to have moved
    if(toupper(pieceTranslator[grid[newX][newY][0]]) == 'P')
        if(((newY - oldY) > 1) || ((oldY - newY) > 1))
            status[(int)grid[newX][newY][0]] = 'D';//The pawn performed a double move
        else
            status[(int)grid[newX][newY][0]] = 'M';
    else
        status[(int)grid[newX][newY][0]] = 'M';

    //End your turn via toggling the player who's turn it is
    boardStatus.turn ^= 1;

    return;
}

int Get_Total_Legal_Moves_For_Piece(char grid[8][8][33], int piece)
{
    int x,
        y,
        total = 0;

    for(x = 0; x < 8; ++x)
        for(y = 0; y < 8; ++y)
            if(grid[x][y][piece] == 'L')
                ++total;

    return total;
}
int Get_First_Coordinate()
{
    int coordinate;

    coordinate = toupper(getche());
    while((coordinate != 'A') && (coordinate != 'B') && (coordinate != 'C') && (coordinate != 'D') && (coordinate != 'E') && (coordinate != 'F') && (coordinate != 'G') && (coordinate != 'H'))
    {
        printf("\nYou must enter a letter between A and H for the first coordinate\n\n");
        coordinate = toupper(getche());
    }


    return Convert_Coordinate(toupper(coordinate));
}

int Get_Second_Coordinate()
{
    int coordinate;

    coordinate = toupper(getche());
    while((coordinate != '1') && (coordinate != '2') && (coordinate != '3') && (coordinate != '4') && (coordinate != '5') && (coordinate != '6') && (coordinate != '7') && (coordinate != '8'))
    {
        printf("\nYou must enter a number between 1 and 8 for the second coordinate\n\n");
        coordinate = toupper(getche());
    }

    return Convert_Coordinate(toupper(coordinate));
}
