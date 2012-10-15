//For Initialize.c
void initializeBoard(char grid[8][8][33]);
void initializeLegal(char grid[8][8][33]);
void initializeStatus(char status[33]);
void initializePieces(char pieceTranslator[33]);
void initializeAll(char grid[8][8][33], char status[33], char pieceTranslator[33]);

//For display.c
void printChessBoard(char grid[8][8][33], char pieceTranslator[33]);
void horizontalLine(short int length);
void printExpandedChessBoard(char grid[8][8][33]);
#define width   17

//For validMove.c
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
void check(char grid[8][8][33], char pieceTranslator[33]);
void whittleMoves(char grid[8][8][33], char pieceTranslator[33], short int testX, short int testY, short int king);

//For testCode,c
void test();
void clearBoard(char grid[8][8][33]);
void legalDisplay(char grid[8][8][33], int piece);
int validMoves(char grid[8][8][33], int piece);
void statusDisplay(char grid[8][8][33], char status[33]);

//For chessPlay.c
void pawnPromotion(char grid[8][8][33], char pieceTranslator[33]);

/*
Assumptions
-----------
1)Pieces 1-16(uppercase) will always be on the same team, just like 17-32(Lowercase) will be on the other
*/
