#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void Board(char board[][8])
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			board[i][j] = '.';
	board[3][3] = 'X';
	board[3][4] = 'O';
	board[4][3] = 'O';
	board[4][4] = 'X';
}

void displayBoard(char board[][8])
{
	for (int y = 7; y >= 0; y--)
	{
		cout << y << " ";
		for (int x = 0; x < 8; x++)
			cout << " " << board[x][y];
		cout << endl;
	}
	cout << "   0 1 2 3 4 5 6 7" << endl;
}

int score(char board[][8], char piece)
{
	int total = 0;
	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 8; y++)
		{
			if (board[x][y] == piece)
				total++;
		}
	return total;
}

bool gameOver(char board[][8])
{
	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 8; y++)
		{
		    if (board[x][y] == '.')
                return false;
		}
    return true;
}

void flipPieces(char board[][8], int x, int y, int deltaX, int deltaY, char Piece, char opponent)
{
	while (board[x][y] == opponent)
	{
		board[x][y] = Piece;
		x = x+ deltaX;
		y = y+ deltaY;
	}
}

bool checkFlip(char board[][8], int x, int y, int deltaX, int deltaY, char Piece, char opponent)
{
	if (board[x][y] == opponent)
	{
		while ((x >= 0) && (x < 8) && (y >= 0) && (y < 8))
		{
			x = x + deltaX;
			y = y + deltaY;
			if ((x >= 0) && (x < 8) && (y >= 0) && (y < 8))
			{
				if (board[x][y] == '.')
					return false;
				if (board[x][y] == Piece)
					return true;
				else{

				}
			}
		}
	}
	return false;
}

void makeMove(char board[][8], int x, int y, char piece)
{
	board[x][y] = piece;
	char opponent;

	if (piece == 'O')
		opponent = 'X';
    if (piece == 'X')
		opponent = 'O';

	if (checkFlip(board, x - 1, y, -1, 0, piece, opponent))
		flipPieces(board, x - 1, y, -1, 0, piece, opponent);

	if (checkFlip(board, x + 1, y, 1, 0, piece, opponent))
		flipPieces(board, x + 1, y, 1, 0, piece, opponent);

	if (checkFlip(board, x, y-1, 0, -1, piece, opponent))
		flipPieces(board, x, y-1, 0, -1, piece, opponent);

	if (checkFlip(board, x, y + 1, 0, 1, piece, opponent))
		flipPieces(board, x, y + 1, 0, 1, piece, opponent);

	if (checkFlip(board, x-1, y - 1, -1, -1, piece, opponent))
		flipPieces(board, x-1, y - 1, -1, -1, piece, opponent);

	if (checkFlip(board, x + 1, y - 1, 1, -1, piece, opponent))
		flipPieces(board, x + 1, y - 1, 1, -1, piece, opponent);

	if (checkFlip(board, x - 1, y + 1, -1, 1, piece, opponent))
		flipPieces(board, x - 1, y + 1, -1, 1, piece, opponent);

	if (checkFlip(board, x + 1, y + 1, 1, 1, piece, opponent))
		flipPieces(board, x + 1, y + 1, 1, 1, piece, opponent);
}

bool validMove(char board[][8], int x, int y, char piece)
{
	if (board[x][y] != '.')
		return false;
	char opponent;

	if (piece == 'O')
		opponent = 'X';
    if (piece == 'X')
		opponent = 'O';

	if (checkFlip(board, x - 1, y, -1, 0, piece, opponent))
		return true;

	if (checkFlip(board, x + 1, y, 1, 0, piece, opponent))
		return true;

	if (checkFlip(board, x, y - 1, 0, -1, piece, opponent))
		return true;

	if (checkFlip(board, x, y + 1, 0, 1, piece, opponent))
		return true;

	if (checkFlip(board, x - 1, y - 1, -1, -1, piece, opponent))
		return true;

	if (checkFlip(board, x + 1, y - 1, 1, -1, piece, opponent))
		return true;

	if (checkFlip(board, x - 1, y + 1, -1, 1, piece, opponent))
		return true;

	if (checkFlip(board, x + 1, y + 1, 1, 1, piece, opponent))
		return true;

	return false;
}

void getMoveList(char board[][8], int moveX[], int moveY[], int &numMoves, char piece)
{
	numMoves = 0;
	for (int x = 0; x < 8; x++)
    {
		for (int y = 0; y < 8; y++)
		{
			if (validMove(board, x, y, piece))
			{
				moveX[numMoves] = x;
				moveY[numMoves] = y;
				numMoves++;
			}
		}
    }
}

void ComputerMove(char board[][8], int &x, int &y, char piece)
{
	int moveX[60], moveY[60], numMoves;
	getMoveList(board, moveX, moveY, numMoves, piece);
	if (numMoves == 0)
	{
		x = -1;
		y = -1;
	}
	else
	{
		int i = rand() % numMoves;
		x = moveX[i];
		y = moveY[i];
	}
}

int main()
{
	srand(time(NULL));
	char board[8][8];
	char curPlayer = 'X';
	Board(board);

	while(!gameOver(board))
	{
		displayBoard(board);
		cout << "X's score= " << score(board, 'X')<< endl;
        cout << "O's score= " << score(board, 'O') <<endl;
		cout << "It is player " << curPlayer << "'s turn." <<endl;
		int x, y;

		if (curPlayer == 'O')
        {
            ComputerMove(board, x, y, 'O');
        }
		else
		{
		    cout << "Enter a move (col row): ";
			cin >> x >> y;
		}
		if (validMove(board, x, y, curPlayer) || (x == -1))
		{
			if (x != -1)
				makeMove(board, x, y, curPlayer);

			if (curPlayer == 'X')
				curPlayer = 'O';
			else
				curPlayer = 'X';
		}
		else
            cout << "Invalid move.Enter move again." << endl;
	}
	cout << endl << "The game is over!"<< endl;
	displayBoard(board);
	int x= score(board, 'X');
	int y= score(board, 'O');
	cout << "X's score: " << x << endl;
	cout << "O's score: " << y << endl;
	if(x > y)
        cout << "X - Human Player is winner."<<endl;

	if(y > x)
        cout << "O - Computer Player is winner."<<endl;

	if(x == y)
	    cout << "The game is tied."<<endl;
	system("pause");
}
