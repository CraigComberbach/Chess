//A 1 indicates that it is a legal move for that piece whereas a 0 means that it is an illega move
struct	legalMoves
{
//One side
	int R1 : 1;
	int R2 : 1;
	int N1 : 1;
	int N2 : 1;
	int B1 : 1;
	int B2 : 1;
	int Q : 1;
	int K : 1;
	int P1 : 1;
	int P2 : 1;
	int P3 : 1;
	int P4 : 1;
	int P5 : 1;
	int P6 : 1;
	int P7 : 1;
	int P8 : 1;

//Other side
	int r1 : 1;
	int r2 : 1;
	int n1 : 1;
	int n2 : 1;
	int b1 : 1;
	int b2 : 1;
	int q : 1;
	int k : 1;
	int p1 : 1;
	int p2 : 1;
	int p3 : 1;
	int p4 : 1;
	int p5 : 1;
	int p6 : 1;
	int p7 : 1;
	int p8 : 1;
};

