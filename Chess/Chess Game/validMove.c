#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "initialize.h"
#include "chessPlay.h"
#include "AI.h"

char King_In_Check(char grid[8][8][33], char pieceTranslator[33]);
void copyGrid(char grid[8][8][33], char testGrid[8][8][33]);
void legalChessMoves(char grid[8][8][33], char status[33], char pieceTranslator[33]);
char judge(char attacker, char defender);
void rowColumnTest(char grid[8][8][33], int x, int y, char pieceTranslator[32]);
void diagonalTest(char grid[8][8][33], int x, int y, char pieceTranslator[32]);
void knightTest(char grid[8][8][33], int x, int y, char pieceTranslator[32]);
void kingTest(char grid[8][8][33], int x, int y, char pieceTranslator[33]);
void pawnTest(char grid[8][8][33], int x, int y, char status[33], char pieceTranslator[33]);
void twoKings(char grid[8][8][33], char pieceTranslator[33]);
void castling(char grid[8][8][33], char status[33], char pieceTranslator[33]);
void enPassant(char grid[8][8][33], char status[33]);
void check(char grid[8][8][33], char status[33], char pieceTranslator[33]);
int  sameSide(char piece1, char piece2);
void basicMoveValidation(char grid[8][8][33], char status[33], char pieceTranslator[33]);

void enPassant(char grid[8][8][33], char status[33])
{
    //En Passant      http://www.chessvariants.org/d.chess/enpassant.html
    return;
}

void check(char grid[8][8][33], char status[33], char pieceTranslator[33])
{
/*If King is in check
Tell the world which King is in check
repeat
	Go piece by piece (don't scan grid to find piece, use piece translator)
	Is it the same colour as the king in check
	If not, move onto the next piece
	repeat
		If they are different, find the first legal move
		copy the current top level grid with the piece moved to its new location
		rerun the valid move checks
		If the king is still in check, it is not a valid move
		otherwise it is a valid move
Scan entire legal grid for legal moves
If none are found, display checkmate
end game*/

    char    king,//The king that is currently in check
            testGrid[8][8][33];//Holds a copy of the grid for testing
    int     piece,//The current piece being looked at
            pieceX = 0,
            pieceY = 0,
            foundFlag = 0,
            legalX,//The legal X cooordinate currently being checked
            legalY,//The legal Y cooordinate currently being checked
            x = 0,//The X coordinate of the selected piece
            y = 0,//The Y coordinate of the selected piece
            totalMoves;

    //Determine if a king is in check
    king = King_In_Check(grid, pieceTranslator);

    if(king == 0)//If there is no check condition
        king = Current_Turn();//return;//No check, get out of the program
    else//There is a check condition
        printf("\n%c is in check!\n", king); //Official notification of being in check

    //Go piece by piece to find all legal moves
    for(piece = 1; piece < 33; ++piece)
    {
        //Determine if this piece is on the same side as the king
        if(!sameSide(pieceTranslator[piece], king))
            continue;//They're on different sides, carry on, nothing to do here
        else//They are on the same side
        {
            //Find the legal moves(int)
            for(legalX = 0; legalX < 8; ++legalX)
            {
                for(legalY = 0; legalY < 8; ++legalY)
                {
                    if(grid[legalX][legalY][piece] == 'L')//Are these coordinates a legal move for the current piece?
                    {
                        //Determine the pieces current location
                        for(x = 0; (x < 8) && (!foundFlag); ++x)
                        {
                            for(y = 0; (y < 8) && (!foundFlag); ++y)
                                if((int)grid[x][y][0] == piece)
                                {
                                    pieceX = x;
                                    pieceY = y;
                                    foundFlag = 1;
                                }
                        }
                        foundFlag = 0;

                        //Copy the grid so the original does not get mangled
                        copyGrid(grid, testGrid);

                        //Place the current piece in its new location
                        testGrid[legalX][legalY][0] = piece;

                        //Remove the current piece from its old location
                        testGrid[pieceX][pieceY][0] = 0;

                        //Test the new layout for all legal moves
                        basicMoveValidation(testGrid,status,pieceTranslator);

                        //If king is still in check
                        if(King_In_Check(testGrid, pieceTranslator) == king)
                            grid[legalX][legalY][piece] = 'I';//This location is now an illegal move
                    }
                }
            }
        }
    }

    //Scan for legal moves
    totalMoves = Number_of_Legal_Moves(grid, pieceTranslator, king);

    //If none are found, checkmate, yay?
    if(totalMoves == 0)
    {
        printf("\nCheckmate!\n\a");
        boardStatus.checkMate = 1;
    }

    return;
}

//Returns 1 of three values, 'k' = king is in check, 'K' = King is in check, 0 = everything is all right
char King_In_Check(char grid[8][8][33], char pieceTranslator[33])
{
    int x, y, z;

    for(x = 0; x < 8; ++x)//Search the Rows for a king
        for(y = 0; y < 8; ++y)//Search the columns for a king
            if(toupper(pieceTranslator[(int)grid[x][y][0]]) == 'K')//Is a King found?
                for(z = 0; z < 33; ++z)//It was, search all of the legal grids here for a potential check
                    if(grid[x][y][z] == 'L')//If a legal move is found, it must indicate a check condition
                        return pieceTranslator[(int)grid[x][y][0]];//Tell the calling function which piece is in check

    //Didn't find a king in check
    return 0;
}

void copyGrid(char grid[8][8][33], char testGrid[8][8][33])
{
	int	x,
		y;

	//Let the copying commence!
	for(y = 0; y < 8; ++y)
		for(x = 0; x < 8; ++x)
			testGrid[x][y][0] = grid[x][y][0];//Aww yeah

	return;
}

void basicMoveValidation(char grid[8][8][33], char status[33], char pieceTranslator[33])
{
    //Grid variables, used to target a specific cell in the grid
    int x,
        y;

    //Start with a blank legal slate
    initializeLegal(grid);

    //Iterates over each cell in the grid and updates the legalMoves variable
    for(y = 0; y < 8; ++y)
        for(x = 0; x < 8; ++x)
            switch(toupper(pieceTranslator[(int)grid[x][y][0]]))
            {
				case 'P'://Pawns
					pawnTest(grid, x, y, status, pieceTranslator);
					break;
				case 'R'://Rooks
					rowColumnTest(grid, x, y, pieceTranslator);
					break;
				case 'N'://kNights
					knightTest(grid, x, y, pieceTranslator);
					break;
				case 'B'://Bishop
					diagonalTest(grid, x, y, pieceTranslator);
					break;
				case 'Q'://Queen
					rowColumnTest(grid, x, y, pieceTranslator);
					diagonalTest(grid, x, y, pieceTranslator);
					break;
				case 'K'://King
					kingTest(grid, x, y, pieceTranslator);
					break;
				case ' '://Blank space
					break;
				default:
					printf("\nThat isn't a piece or a part of the game board '%c' (%d, %d)\n\n", pieceTranslator[(int)grid[x][y][0]], x, y);
					break;
            }

    return;
}

//Determines legal squares based on the attacking square and the defending square
//Returns either a 1 (Illegal move - or same side) or a 0 (Legal move - opposing side)
int sameSide(char piece1, char piece2)
{
    if(!((toupper(piece1) == piece1) ^ (toupper(piece2) == piece2)))//Xnor of the two pieces (trust me it works, don't change it now)
		return 1;//1 for it is the same team
	else
		return 0;//0 for it is the opposing team
}

//Returns an 'I' if the attack is illegal, or an 'L' if it is legal, if the space is blank it will return an 'L'
char judge(char attacker, char defender)
{
    //If the defender is a blank tile
    if(defender == ' ')
        return 'L';//Blank tiles are legal moves

    //Otherwise, its a piece on the board!!!
    if(sameSide(attacker, defender))
        return 'I';//They are both on the same side, this is not a legal move
    else
        return 'L';//They are on opposing sides, this is a legal move
}

void legalChessMoves(char grid[8][8][33], char status[33], char pieceTranslator[33])
{
    //Find the basic valid moves without any complications
    basicMoveValidation(grid, status, pieceTranslator);

    //looks for special cases, eg. castling and movement bringing two kings next to each other
    twoKings(grid, pieceTranslator);
    castling(grid, status, pieceTranslator);

    //Check for En Passant attack
    enPassant(grid, status);

    //Check for pawn Promotion
    pawnPromotion(grid, pieceTranslator);

    //Check for check
    printf("Check is disabled currently\n\n"); getch();
//    check(grid, status, pieceTranslator);

    return;
}

void rowColumnTest(char grid[8][8][33], int x, int y, char pieceTranslator[32])
{
    int testX,
        testY,
        loop;

    for(loop = 0; loop < 4; ++loop)
    {
        testX = x;
        testY = y;

        while((testX <= 7) && (testX >= 0) && (testY <= 7) && (testY >= 0))
        {
            switch(loop)
            {
            case 0:
                --testX;//Search to the left
                break;
            case 1:
                ++testX;//Search to the right
                break;
            case 2:
                --testY;
                break;
            case 3:
                ++testY;
                break;
            }

            if((testX <= 7) && (testX >= 0) && (testY <= 7) && (testY >= 0))
                grid[testX][testY][(int)grid[x][y][0]] = judge(pieceTranslator[(int)grid[x][y][0]], pieceTranslator[(int)grid[testX][testY][0]]);//test the space to see if it is a legal move

            if(grid[testX][testY][0] != 0)
                break;
        }
    }

    return;
}

void diagonalTest(char grid[8][8][33], int x, int y, char pieceTranslator[32])
{
    //Queens and Bishops
    int loop,
        testX,
        testY;

    for(loop = 0; loop < 4; ++loop)
    {
        testX = x;
        testY = y;
        while((testX <= 7) && (testX >= 0) &&(testY <= 7) && (testY >= 0))
        {
            switch(loop)
            {
            case 0:
                ++testX;
                ++testY;
                break;
            case 1:
                --testX;
                ++testY;
                break;
            case 2:
                --testX;
                --testY;
                break;
            case 3:
                ++testX;
                --testY;
                break;
            default:
                printf("Something has gone wrong in the diagonal test code");
                break;
            }

            if((testX <= 7) && (testX >= 0) &&(testY <= 7) && (testY >= 0))
                grid[testX][testY][(int)grid[x][y][0]] = judge(pieceTranslator[(int)grid[x][y][0]], pieceTranslator[(int)grid[testX][testY][0]]);//test the space to see if it is a legal move

            if(grid[testX][testY][0] != 0)
                break;
        }
    }

    return;
}

void knightTest(char grid[8][8][33], int x, int y, char pieceTranslator[32])
{
    //Perform 8 testes
    int loop,
        testX,
        testY;

    for(loop = 0; loop < 8; ++loop)
    {
        switch(loop)
        {
            case 0://Test Up and to the Left
                testX = x - 1;
                testY = y - 2;
                break;
            case 1://Test Up and to the Right
                testX = x + 1;
                testY = y - 2;
                break;
            case 2://Test Left and upwards
                testX = x - 2;
                testY = y - 1;
                break;
            case 3://Test Left and downwards
                testX = x - 2;
                testY = y + 1;
                break;
            case 4://Test Down and to the left
                testX = x - 1;
                testY = y + 2;
                break;
            case 5://Test Down and to the right
                testX = x + 1;
                testY = y + 2;
                break;
            case 6://Test Right and upwards
                testX = x + 2;
                testY = y - 1;
                break;
            case 7://Test Right and downwards
                testX = x + 2;
                testY = y + 1;
                break;
            default:
                printf("Knight legality test failure!");
                break;
        }
        if((testX >= 0) && (testX <= 7) && (testY >= 0) && (testY <= 7))
        {
            grid[testX][testY][(int)grid[x][y][0]] = judge(pieceTranslator[(int)grid[x][y][0]], pieceTranslator[(int)grid[testX][testY][0]]);//test the space to see if it is a legal move
        }
    }

    return;
}

void kingTest(char grid[8][8][33], int x, int y, char pieceTranslator[33])
{
    int     loop,
            testX,
            testY;

    for(loop = 0; loop < 8; ++loop)
    {
        switch(loop)
        {
            case 0://Test Up
                testX = x;
                testY = y - 1;
                break;
            case 1://Test Up and to the Right
                testX = x + 1;
                testY = y - 1;
                break;
            case 2://Test Right
                testX = x + 1;
                testY = y;
                break;
            case 3://Test Right and downwards
                testX = x + 1;
                testY = y + 1;
                break;
            case 4://Test Down
                testX = x;
                testY = y + 1;
                break;
            case 5://Test Down and to the left
                testX = x - 1;
                testY = y + 1;
                break;
            case 6://Test left
                testX = x - 1;
                testY = y;
                break;
            case 7://Test left and upwards
                testX = x - 1;
                testY = y - 1;
                break;
            default:
                printf("King legality test failure!");
                break;
        }

        if((testX >= 0) && (testX <= 7) && (testY >= 0) && (testY <= 7))
            grid[testX][testY][(int)grid[x][y][0]] = judge(pieceTranslator[(int)grid[x][y][0]], pieceTranslator[(int)grid[testX][testY][0]]);//test the space to see if it is a legal move
    }

    return;
}

void pawnTest(char grid[8][8][33], int x, int y, char status[33], char pieceTranslator[33])
{
//Double move on first move
//Single move after first move
//Attack only on diagonals
//Unidirectional movement
//Opposing player moves exactly opposite

    switch(pieceTranslator[(int)grid[x][y][0]])
    {
        case 'p':
            //Test for initial double move
            if((status[(int)grid[x][y][0]] == 'V') && (grid[x][y - 1][0] == 0) && (grid[x][y - 2][0] == 0) && ((y - 2) >= 0))
                grid[x][y - 2][(int)grid[x][y][0]] = 'L';

            //Test forward of the piece for an open space
            if(((y - 1) >= 0) && (grid[x][y - 1][0] == 0))
                grid[x][y - 1][(int)grid[x][y][0]] = 'L';//One space forward

            //Test to the forward left of the piece for a possible attack, only legal if it can attack something
            if(((x - 1) >= 0) && ((y - 1) >= 0) && (grid[x - 1][y - 1][0] != 0))
                grid[x - 1][y - 1][(int)grid[x][y][0]] = judge(pieceTranslator[(int)grid[x][y][0]], pieceTranslator[(int)grid[x - 1][y - 1][0]]);//test the space to see if it is a legal move

            //Test to the forward right of the piece for a possible attack, only legal if it can attack something
            if(((x + 1) <= 7) && ((y - 1) >= 0) && (grid[x + 1][y - 1][0] != 0))
                grid[x + 1][y - 1][(int)grid[x][y][0]] = judge(pieceTranslator[(int)grid[x][y][0]], pieceTranslator[(int)grid[x + 1][y - 1][0]]);//test the space to see if it is a legal move

            break;
        case 'P':
            //Test for initial double move
            if((status[(int)grid[x][y][0]] == 'V') && (grid[x][y + 1][0] == 0) && (grid[x][y + 2][0] == 0) && ((y + 2) >= 0))
                grid[x][y + 2][(int)grid[x][y][0]] = 'L';

            //Test forward of the piece for an open space
            if(((y + 1) >= 0) && (grid[x][y + 1][0] == 0))
                grid[x][y + 1][(int)grid[x][y][0]] = 'L';//One space forward

            //Test to the forward left of the piece for a possible attack, only legal if it can attack something
            if(((x - 1) >= 0) && ((y + 1) <= 7) && (grid[x - 1][y + 1][0] != 0))
                grid[x - 1][y + 1][(int)grid[x][y][0]] = judge(pieceTranslator[(int)grid[x][y][0]], pieceTranslator[(int)grid[x - 1][y + 1][0]]);//test the space to see if it is a legal move

            //Test to the forward right of the piece for a possible attack, only legal if it can attack something
            if(((x + 1) <= 7) && ((y + 1) <= 7) && (grid[x + 1][y + 1][0] != 0))
                grid[x + 1][y + 1][(int)grid[x][y][0]] = judge(pieceTranslator[(int)grid[x][y][0]], pieceTranslator[(int)grid[x + 1][y + 1][0]]);//test the space to see if it is a legal move

            break;
        default:
            printf("\nThis is not a pawn?\n");
            break;
    }

    return;
}

//Makes the movement of two opposing kings next to each other illegal
void twoKings(char grid[8][8][33], char pieceTranslator[33])
{
    int x,
        y,
        king = 0,
        KING = 0;

    //finds the kings and remembers their unique IDs
    for(x = 1; x < 33; ++x)
        if(pieceTranslator[x] == 'K')
            KING = x;//Probably 4
        else if(pieceTranslator[x] == 'k')
            king = x;//Probably 28

    //If a square is a legal move for both kings, make it an illegal square! This prevents any king from moving next to the other king
    for(x = 0; x < 8; ++x)
        for(y = 0; y < 8; ++y)
            if((grid[x][y][KING] == 'L') && (grid[x][y][king] == 'L'))//The same square is a grid move for both opposing kings
            {
                grid[x][y][KING] = 'I';
                grid[x][y][king] = 'I';
            }

    return;
}

void castling(char grid[8][8][33], char status[33], char pieceTranslator[33])
{
    //Castling        http://www.chessvariants.org/d.chess/castlefaq.html
    //King can't be in check
//King can't move through threatened squares
//King can't finish in check
    //Can't castle if King has previously moved
    //Can't castle if the castling Rook has previously moved
//Can't castle if there are pieces in the way of either the Rook or King
//Now code monkey, code like the wind!

    int                 x,//Temporary variable, used to test a location for viability
                        z,//Searching the vertical branch
                        distance,//Used for storing the distance between the rook and king
                        abort = 0,//Used to kick back out of a few loops
                        king,//Used to find & store the current king
                        rook;//Used to find & store the current rook
    struct coordinates  kingLocation,//Stores the currently selected kings locations
                        rookLocation;//Stores the currently selected rooks locations

    for(king = 1; king <= 32; ++king)
    {
        //Find the king
        if((pieceTranslator[king] != 'k') && (pieceTranslator[king] != 'K'))//If its not a king
            continue;//Keep searching
        else//Otherwise
            kingLocation = Get_Coordinates(grid, king);

        //If it actually wasn't found on the board...
        if((kingLocation.x >= 8) || (kingLocation.y >= 8))
            continue;//Continue on to the next piece

        //Determine if the king is a valid choice for castling
        switch(status[king])
        {
            case 'V'://Never before moved
            case 'S'://Previously found to be capable of short castling
            case 'L'://Previously found to be capable of long castling
            case 'B'://Previously found capable of both castles
                break;//Yay, we can still work with this king
            default://He is no longer a valid candidate for castling
                continue;//Continue on to the next king
        }

        //Check that the king isn't currently in check
        for(z = 1; z < 33; ++z)
        {
            if(grid[kingLocation.x][kingLocation.y][z] == 'L')
                continue;//We're in check, move onto the next king
        }

        for(rook = 1; rook <= 32; ++rook)
        {
            //Find the rook
            if((pieceTranslator[rook] != 'r') && (pieceTranslator[rook] != 'R'))//If its not a Rook
                continue;//Keep searching
            else//Otherwise
                rookLocation = Get_Coordinates(grid, rook);

            //If it actually wasn't found on the board...
            if((rookLocation.x >= 8) || (rookLocation.y >= 8))
                continue;//Continue on to the next piece

            //Determine if the rook is a valid choice for castling
            switch(status[rook])
            {
                case 'V'://Never before moved
                case 'S'://Previously found to be capable of short castling
                case 'L'://Previously found to be capable of long castling
                    break;//Yay, we can still work with this rook
                default://He is no longer a valid candidate for castling
                    continue;//Continue on to the next rook
            }

            //Check that the king and rook on both on the same line!
            if(kingLocation.y != rookLocation.y)
                continue;//Castling will never work, move on to the next rook

            //Is it in a position where it can castle?
            distance = abs(kingLocation.x - rookLocation.x);
            if((distance != 3) && (distance != 4))
                continue;

            //Make sure abort is cleared before continuing (in case it was set last time a rook was found
            abort = 0;

            //Assign the starting point, we check from left to right
            if(kingLocation.x < rookLocation.x)
                x = kingLocation.x;//The king is furthest left, start there
            else
                x = rookLocation.x;//The rook is furthest left, start there

            //Check that the intervening spaces between the king and rook are viable for check
            while(++x, (x < rookLocation.x) || (x < kingLocation.x))
            {
                //Check for a piece in the way
                if(grid[x][kingLocation.y][0] != 0)
                {
                    abort = 1;//There is a piece in the way
                    break;
                }

                //Search for legal moves from non-allied pieces
                for(z = 1; z < 33; ++z)
                {
                    if(grid[x][kingLocation.y][z] != 'L')//If a legal move isn't found
                        continue;//All is well, keep going
                    why does !same side work? it shouldn't!'
                    else if(sameSide(king, pieceTranslator[z]))//Else, if they are on the same side
                        continue;//Its ok
                    else//Else, its bad news for castling
                    {
                        printf("Problem at (%d, %d, %d) for %c with %c\n",x,kingLocation.y, z, pieceTranslator[king],pieceTranslator[rook]);
                        abort = 1;//There is a piece threatening the castling path
                        break;
                    }
                }

                //Got to keep backing out, no sense continuing with any other squares
                if(abort)
                    break;
            }

            //This will pop it back out to look for the next rook, if it failed a test somewhere
            if(abort)
                continue;

            //Make most glorius changes, we can castle!
            if(distance == 3)//Is is a short castle
            {
                status[rook] = 'S';//The rook is available for castling

                //The king can either be a L, S or B
                if((status[king] == 'V') || (status[king] == 'S'))
                    status[king] = 'S';
                else
                    status[king] = 'B';
            }
            else if(distance == 4)//Or a long castle
            {
                status[rook] = 'L';//The rook is available for castling

                //The king can either be a L, S or B
                if((status[king] == 'V') || (status[king] == 'L'))
                    status[king] = 'L';
                else
                    status[king] = 'B';
            }

            //Assign the correct square for castling
            if(kingLocation.x < rookLocation.x)
                grid[rookLocation.x-1][rookLocation.y][king] = 's';//The location will only accept the short castle
            else
                grid[rookLocation.x+1][rookLocation.y][king] = 's';//The location will only accept the short castle

        }
    }

    return;
}
