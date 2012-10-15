#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "chess.h"

void enPassant(char grid[8][8][33], char status[33])
{
    //En Passant      http://www.chessvariants.org/d.chess/enpassant.html
    return;
}

//Whittles down the potential moves of a single piece
void whittleMoves(char grid[8][8][33], char pieceTranslator[33], short int testX, short int testY, short int king)
{
    short int   x,
                y,
                testHi,
                testLo;
    char        testGrid[8][8][33];

    if((king >= 0) && (king <= 16))
    {
        testHi = 16;
        testLo = 0;
    }
    else if((king >= 17) && (king <= 32))
    {
        testHi = 32;
        testLo = 17;
    }

    for(y = 0; y < 8; ++y)
        for(x = 0; x < 8; ++x)
            if(((int)grid[x][y][0] >= testLo) && ((int)grid[x][y][0] <= testHi))//if its on the same team

    return;
}

void check(char grid[8][8][33], char pieceTranslator[33])
{
/*    Check - Determine all legal moves, then determine if a king is in check. If they are, run a routine that
 is similar to the AI script in that it will test each legal move to see if it ends check, if it does end
 check then it is legal, otherwise it is illegal!
 Assuming that only one king can ever be in check at a time!
 */
    short int   king,
                x,
                y,
                z,
                testX,
                testY,
                copyX,
                copyY;
    char        testGrid[8][8][33];

    for(y = 0; y < 8; ++y)//Columns
        for(x = 0; x < 8; ++x)//Rows
            if((pieceTranslator[(int)grid[x][y][0]] == 'k') || (pieceTranslator[(int)grid[x][y][0]] == 'K'))//Test if the location is a king
                for(z = 1; z < 33; ++z) //There are 33 levels to the grid, 0 is the display grid, 1 to 32 are unique levels(32 pieces)
                    if(grid[x][y][z] == 'L')//The king is in check! Oh noes!!!! Enter into the legal move reduction scripts
                    {
                        printf("\n%c is in check!\n", pieceTranslator[(int)grid[x][y][0]]); //Official notification of being in check

                        //Start eliminating legal moves
                        for(testY = 0; testY < 8; ++testY)
                            for(testX = 0; testX < 8; ++testX)
                            {
                                //copy grid[x][y][0] to testGrid[x][y][0] for further testing
                                for(copyY = 0; copyY < 8; ++copyY)
                                    for(copyX = 0; copyX < 8; ++copyX)
                                        testGrid[copyX][copyY][0] = grid[copyX][copyY][0];

                                king = grid[x][y][0];
                                whittleMoves(grid, pieceTranslator, testX, testY, king);
                            }
                    }

    return;
}

//Returns an 'I' if the attack is illegal, or an 'L' if it is legal, if the space is blank it will return an 'L'
char judge(char attacker, char defender)
{
    if(defender == ' ')
        return 'L';

    if(toupper(attacker) == attacker)//Capital is attacking
        if(toupper(defender) == defender)//Capital is defending
            return 'I';//I for Illegal
        else
            return 'L';//L for Legal
    else//Lower case is attacking
        if(toupper(defender) == defender)//Capital is defending
            return 'L';//L for Legal
        else
            return 'I';//I for Illegal
}

void legalChessMoves(char grid[8][8][33], char status[33], char pieceTranslator[33])
{
    //Grid variables, used to target a specific cell in the grid
    int x,
        y;

    //Start with a blank slate
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

    //looks for special cases, eg. castling and movement bringing two kings next to each other
    twoKings(grid, pieceTranslator);
    castling(grid, status, pieceTranslator);

    //Check for En Passant attack
    enPassant(grid, status);

    //Check for pawn Promotion
    pawnPromotion(grid, pieceTranslator);
    printf("Remove this statement /|\, it doesn't belong in piece validation");

    //Check for Check...
        //Remove legal locations for king that would RESULT in check
        //Detect when check has occured
        //Remove all legal moves that don't result in removing check
        //Detect checkmate
    check(grid, pieceTranslator);

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

        while((testX < 7) && (testX > 0) && (testY < 7) && (testY > 0))
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
        while((testX < 7) && (testX > 0) &&(testY < 7) && (testY > 0))
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
            //Ahhhh test code for Queens and Bishops

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
        {
            if(toupper(pieceTranslator[(int)grid[testX][testY][0]]) != 'K')//Tests to ensure that the space isn't a king
                grid[testX][testY][(int)grid[x][y][0]] = judge(pieceTranslator[(int)grid[x][y][0]], pieceTranslator[(int)grid[testX][testY][0]]);//test the space to see if it is a legal move
            else
                printf("\nTwo kings next to each other!\n");
        }
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

            //Test forward of the piece for a open space
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

            //Test forward of the piece for a open space
            if(((y + 1) >= 0) && (grid[x][y + 1][0] == 0))
                grid[x][y + 1][(int)grid[x][y][0]] = 'L';//One space forward

            //Test to the forward left of the piece for a possible attack, only legal if it can attack something
            if(((x - 1) >= 0) && ((y + 1) >= 0) && (grid[x - 1][y + 1][0] != 0))
                grid[x - 1][y + 1][(int)grid[x][y][0]] = judge(pieceTranslator[(int)grid[x][y][0]], pieceTranslator[(int)grid[x - 1][y + 1][0]]);//test the space to see if it is a legal move

            //Test to the forward right of the piece for a possible attack, only legal if it can attack something
            if(((x + 1) <= 7) && ((y + 1) >= 0) && (grid[x + 1][y + 1][0] != 0))
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
        king,
        KING;

    //finds the kings and remembers their unique IDs
    for(x = 0; x < 32; ++x)
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

    int     x,
            y,
            z,
            testX,
            rookPosition,
            loop,
            checkFlag = 0;
    char    castlingFlag;//What castling type is being tested for (S and L)

    for(y = 0; y < 8; ++y)
    {
        for(x = 0; x < 8; ++x)
        {
            if((pieceTranslator[(int)grid[x][y][0]] == 'k') || (pieceTranslator[(int)grid[x][y][0]] == 'K'))
            {
                //Is the king tecnically even allowed to castle?
                if((status[(int)grid[x][y][0]] == 'V') || (status[(int)grid[x][y][0]] == 'S') || (status[(int)grid[x][y][0]] == 'L') || (status[(int)grid[x][y][0]] == 'B'))
                {
                    for(loop = 0; loop < 4; ++loop)
                    {
                        switch(loop)
                        {
                            case 0://Short castle one way
                                castlingFlag = 'S';
                                testX = x + 3;
                                break;
                            case 1://Short castle other way
                                castlingFlag = 'S';
                                testX = x - 3;
                                break;
                            case 2://Long Castle one way (needs extra test here, compared to Short Castling)
                                castlingFlag = 'L';
                                testX = x + 4;

                                //Tests for the open space
                                if(grid[testX - 1][y][0] != 0)
                                    continue;

                                break;
                            case 3://Long Castle other way (needs extra test here, compared to Short Castling)
                                castlingFlag = 'L';
                                testX = x - 4;

                                //Tests for the open space
                                if(grid[testX + 1][y][0] != 0)
                                    continue;

                                break;
                            default:
                                printf("Castling failed\n");
                                break;
                        }
                        //Find an appropriate rook
                        //Tests to make sure both are the same case
                        //Tests that the piece being tested is a rook
                        //Tests that the rook has not moved yet
                        //So basically is its an allied rook continue testing
                        if((!((pieceTranslator[(int)grid[testX][y][0]] == toupper(pieceTranslator[(int)grid[testX][y][0]])) ^ (pieceTranslator[(int)grid[x][y][0]] == toupper(pieceTranslator[(int)grid[x][y][0]])))) && (toupper(pieceTranslator[(int)grid[testX][y][0]]) == 'R') && (status[(int)grid[testX][y][0]] == 'V')) //Is it a rook and more importantly is it an allied rook
                        {
                            //Save the rooks position for later use
                            rookPosition = testX;

                            //Bring the Kings test into the range that he can move, modifies Long castling numbers to short castling numbers
                            if((testX - x) == 4)
                                --testX;
                            else if((testX - x) == -4)
                                ++testX;

                            //Find the open spaces and potential checks for the king
                            while((testX != x) && (checkFlag == 0))
                            {
                                //Change the position of test
                                //NOTE: It is important that it happen first, otherwise you would be testing the rooks location as well, which is unimportant as both a free space and a potential place of attack
                                if(testX < x)
                                    ++testX;
                                else if(testX > x)
                                    --testX;

                                if((grid[testX][y][0] != 0) && (testX != x))
                                    checkFlag = 1; //Jumps out of this while loop, thus preventing it from ever assigning the coveted castling status

                                //Look for potential attacks
                                if((grid[x][y][0] <= 16) && (grid[x][y][0] >= 1))
                                {
                                    for(z = 17; z <= 32; ++z)
                                        //If a potential attack is found, set the checkFlag to 1
                                        if(grid[testX][y][z] == 'L')
                                            checkFlag = 1;//Jumps out of this while loop, thus preventing it from ever assigning the coveted castling status
                                }
                                else if((grid[x][y][0] <= 32) && (grid[x][y][0] >= 17))
                                {
                                    for(z = 1; z <= 16; ++z)
                                        //If a potential attack is found, set the checkFlag to 1
                                        if(grid[testX][y][z] == 'L')
                                            checkFlag = 1;//Jumps out of this while loop, thus preventing it from ever assigning the coveted castling status
                                }

                                if((testX == x) && (checkFlag == 0))
                                {
                                    if((loop == 0) || (loop == 1))
                                    {
                                        //Set the Rook to be able to castle with the king
                                        status[(int)grid[rookPosition][y][0]] = 'S';

                                        //If the King can already castle, set to a B for both, otherwise set to S
                                        if((status[(int)grid[x][y][0]] == 'S') || (status[(int)grid[x][y][0]] == 'L'))
                                            status[(int)grid[x][y][0]] = 'B';
                                        else
                                            status[(int)grid[x][y][0]] = 'S';

                                    }
                                    else if((loop == 2) || (loop == 3))
                                    {
                                        //Set the Rook to be able to castle with the king
                                        status[(int)grid[rookPosition][y][0]] = 'L';

                                        //If the King can already castle, set to a B for both, otherwise set to L
                                        if((status[(int)grid[x][y][0]] == 'S') || (status[(int)grid[x][y][0]] == 'L'))
                                            status[(int)grid[x][y][0]] = 'B';
                                        else
                                            status[(int)grid[x][y][0]] = 'L';
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return;
}
