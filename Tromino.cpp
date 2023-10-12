#include <iostream>
using namespace std;

static int c = 0;
class Array
{
private:
	int cap;
	int* arr;
public:
	Array(int cap) : cap(cap)
	{
		arr = new int[cap];
		for (int i = 0; i < cap; i++)
			arr[i] = 0;
	}
	Array(Array& ref) : cap(ref.cap)
	{
		arr = new int[cap];
		for (int i = 0; i < cap; i++)
			arr[i] = ref.arr[i];
	}
	~Array() { delete[]arr; }

	//Overload
	int& operator[](int idx)
	{
		if (idx < 0 || idx >= cap)
		{
			cout << "Out of Bounds" << endl;
			exit(1);
		}

		return arr[idx];
	}
	friend ostream& operator<<(ostream& os, Array& array);
};

ostream& operator<<(ostream& os, Array& array)
{
	for (int i = 0; i < array.cap; i++)
		os << array.arr[i] << ' ';
	os << endl;
	return os;
}

using Arrayptr = Array*;
class Board
{
private:
	int rows, cols;
	Arrayptr* board;
public:
	Board(int row, int col) :rows(row), cols(col)
	{
		board = new Arrayptr[rows];
		for (int i = 0; i < cols; i++)
		{
			board[i] = new Array(cols);
		}
	}
	Board(Board& ref) :rows(ref.rows), cols(ref.cols)
	{
		board = new Arrayptr[rows];
		for (int i = 0; i < rows; i++)
		{
			board[i] = new Array(cols);
		}
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				board[i][j] = ref.board[i][j];
	}

	~Board()
	{
		for (int i = 0; i < rows; i++)
			delete board[i];
		delete[] board;
	}

	//Overload
	Array& operator[](int idx)
	{
		if (idx < 0 || idx >= rows)
		{
			cout << "Out of Bounds" << endl;
			exit(1);
		}
		return *board[idx];
	}

	friend ostream& operator<<(ostream& os, Board& board);
};

ostream& operator<<(ostream& os, Board& board)
{
	for (int i = 0; i < board.rows; i++)
		os << board[i];
	os << endl;
	return os;
}


void Tromino(Board& board, int n, int a, int b, int y, int x)
{
	//n = 2일때
	if (n == 2)
	{
		c++;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (board[a + i][b + j] == 0)
				{
					board[a + i][b + j] = c;
				}
			}
		}
		return;
	}

	c++;
	if (a <= y && y < a + n / 2 && b <= x && x < b + n / 2)//1사분면
	{
		board[a + n / 2][b + n / 2] = c; //4
		board[a + n / 2 - 1][b + n / 2] = c; //3
		board[a + n / 2][b + n / 2 - 1] = c; //2
		Tromino(board, n / 2, a, b, y, x); //1
		Tromino(board, n / 2, a + n / 2, b, a + n / 2, b + n / 2 - 1); //2
		Tromino(board, n / 2, a, b + n / 2, a + n / 2 - 1, b + n / 2); //3
		Tromino(board, n / 2, a + n / 2, b + n / 2, a + n / 2, b + n / 2); //4

	}
	else if (a + n / 2 <= y && y < a + n && b <= x && x < b + n / 2)//2사분면
	{
		board[a + n / 2][b + n / 2] = c; //4
		board[a + n / 2 - 1][b + n / 2 - 1] = c; //1
		board[a + n / 2 - 1][b + n / 2] = c; //3
		Tromino(board, n / 2, a, b, a + n / 2 - 1, b + n / 2 - 1);
		Tromino(board, n / 2, a + n / 2, b, y, x);
		Tromino(board, n / 2, a, b + n / 2, a + n / 2 - 1, b + n / 2);
		Tromino(board, n / 2, a + n / 2, b + n / 2, a + n / 2, b + n / 2);
	}
	else if (a <= y && y < a + n / 2 && b + n / 2 <= x && x < b + n)//3사분면
	{
		board[a + n / 2][b + n / 2] = c; // 4
		board[a + n / 2 - 1][b + n / 2 - 1] = c; //1
		board[a + n / 2][b + n / 2 - 1] = c; //2
		Tromino(board, n / 2, a, b, a + n / 2 - 1, b + n / 2 - 1);
		Tromino(board, n / 2, a + n / 2, b, a + n / 2, b + n / 2 - 1);
		Tromino(board, n / 2, a, b + n / 2, y, x);
		Tromino(board, n / 2, a + n / 2, b + n / 2, a + n / 2, b + n / 2);
	}
	else//4사분면
	{
		board[a + n / 2 - 1][b + n / 2 - 1] = c; //1
		board[a + n / 2][b + n / 2 - 1] = c; //2
		board[a + n / 2 - 1][b + n / 2] = c; // 3
		Tromino(board, n / 2, a, b, a + n / 2 - 1, b + n / 2 - 1);
		Tromino(board, n / 2, a + n / 2, b, a + n / 2, b + n / 2 - 1);
		Tromino(board, n / 2, a, b + n / 2, a + n / 2 - 1, b + n / 2);
		Tromino(board, n / 2, a + n / 2, b + n / 2, y, x);
	}

}


int main(void)
{
	int k, x, y;
	cin >> k;
	cin >> x >> y;

	k = 2 << k - 1;

	Board board(k, k);
	y--;
	x--;
	board[y][x] = -1;

	Tromino(board, k, 0, 0, y, x);


	cout << board;
}