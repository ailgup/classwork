/* Christopher Puglia
Sudoko Project 4b

g++ -o sud Board.cpp d_matrix.h d_except.h -std=c++0x -Wno-deprecated


*/


// Declarations and functions for the Sudoku project

#include <iostream>
#include <limits.h>
#include <vector>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>

using namespace std;

typedef int ValueType; // The type of the value in a cell
const int blank = -1;  // Indicates that a cell is blank

const int squareSize = 3;  //  The number of cells in a small square
						   //  (usually 3).  The board has
						   //  SquareSize^2 rows and SquareSize^2
						   //  columns.

const int boardSize = squareSize * squareSize;

const int minValue = 1;
const int maxValue = 9;
int calls;
int numSolutions = 0;
int numFalse(vector <bool> v);
class Board
	// Stores the entire Sudoku board
{
public:
	Board(int);
	bool solve();
	bool AllPossible();
	void Clear();
	void Initialize(ifstream &fin);
	bool isConflict(int i, int j, int num);
	bool isSolved();
	bool isLegal(int r, int c, int num);
	bool findEmpty(int & irow, int & icol, int & val);
	int findOther1(int x);
	int findOther2(int x);
	int SquareNumber(int i, int j);
	void Print();
	int getCalls();
	bool IsBlank(int, int);
	ValueType GetCell(int, int);
	void  SetCell(int i, int j, ValueType val);
	void ClearCell(int i, int j);
private:

	// The following matrices go from 1 to BoardSize in each
	// dimension.  I.e. they are each (BoardSize+1) X (BoardSize+1)
	matrix <bool> row;
	matrix <bool> col;
	matrix <bool> box;
	matrix<ValueType> value;
};
Board::Board(int sqSize)
	: value(boardSize + 1, boardSize + 1)
{
	row.resize(11, 10);
	col.resize(11, 10);
	box.resize(11, 10);
	calls = 0;
}
bool Board::solve()
{
	int r, c,val;
	calls++;
	if (isSolved())
		return true;
	findEmpty(r, c, val);
	for (val; val <= 9; val++)
	{
		if (isLegal(r, c, val))
		{
			SetCell(r, c, val);
			if (solve())
				return true;
			ClearCell(r, c);
		}
	}
	return false;
}

// Board constructor

bool Board::AllPossible()
{
	for (int k = 1; k < 10; k++)
	{
		for (int j = 1; j < 10; j++)
		{
			bool possible = false;
			if (IsBlank(k, j))
			{
				for (int z = 1; z < 10; z++)
				{
					if (!isConflict(k, j, z))
					{
						z = 10;
						possible = true;
					}
				}

				if (!possible)
					return false;
			}
		}
	}
	return true;
}
void Board::Clear()
// Clear the entire board.
{
	for (int i = 1; i <= boardSize; i++)
	{
		for (int j = 1; j <= boardSize; j++)
		{
			for (int val = 0; val < 10; val++)
			{
				value[i][j] = 0;
				row[i][val] = false;
				col[j][val] = false;
				box[SquareNumber(i, j)][val] = false;
			}
		}
	}
}

void  Board::SetCell(int i, int j, ValueType val)
// set cell i,j to val and update conflicts
{
	if (isConflict(i, j, val))
		throw rangeError("trying to add conflicting cell");
	//cout << "ERROR";
	value[i][j] = val;
	row[i][val] = true;
	col[j][val] = true;
	box[SquareNumber(i, j)][val] = true;
}

void  Board::ClearCell(int i, int j)
// set cell i,j to val and update conflicts
{
	int val = value[i][j];
	value[i][j] = 0;
	row[i][val] = false;
	col[j][val] = false;
	box[SquareNumber(i, j)][val] = false;
}

void Board::Initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
	char ch;

	Clear();
	for (int i = 1; i <= boardSize; i++)
		for (int j = 1; j <= boardSize; j++)
		{
			fin >> ch;

			// If the read char is not Blank
			if (ch != '.')
			{
				SetCell(i, j, ch - '0');   // Convert char to int
			}
			if (ch == '.')
				ClearCell(i, j);
		}
}

bool Board::isConflict(int i, int j, int num)
{
	if (row[i][num] == 1 || col[j][num] == 1 || box[SquareNumber(i, j)][num] == 1)
		return true;
	return false;
}

bool Board::isSolved()
{
	for (int i = 1; i <= boardSize; i++)
	{
		for (int j = 1; j <= boardSize; j++)
		{
			if (IsBlank(i, j))
				return false;
		}
	}
	return true;
}

bool Board::isLegal(int r, int c, int num)
{
	if (isConflict(r, c, num))
		return false;
	SetCell(r, c, num);
	if (!AllPossible())
	{
		ClearCell(r, c);
		return false;
	}
	ClearCell(r, c);
	return true;
}

bool Board::findEmpty(int & irow, int & icol, int & val)
{
	int lowestx = 0;
	int lowesty = 0;
	int lowestnums = 9;
	val = 1; //default value
	for (irow = 1; irow <= 9; irow++)
	{
		for (icol = 1; icol <= 9; icol++)
		{
			if (value[irow][icol] == 0)
			{

				vector <bool> r1 = row[irow];
				vector <bool> c1 = col[icol];
				vector <bool> b1 = box[SquareNumber(irow, icol)];
				if (numFalse(r1) <= lowestnums || numFalse(c1) <= lowestnums || numFalse(b1) <= lowestnums)
				{
					if (numFalse(r1) <= lowestnums)
						lowestnums = numFalse(r1);
					if (numFalse(c1) <= lowestnums)
						lowestnums = numFalse(c1);
					if (numFalse(b1) <= lowestnums)
						lowestnums = numFalse(b1);

					lowesty = irow;
					lowestx = icol;
					if (lowestnums == 1)
						return true;
				}
				
			}
		}
	}


	if (lowestnums == 0)
	{
		return false;
	}
	irow = lowesty;
	icol = lowestx;
	return true;
}


int numFalse(vector <bool> v)
{
	int count = 0;
	for (int i = 1; i < 10; i++)
	{
		if (v.at(i) == 0)
			count++;
	}
	if (count == 9)
		return 999; //case of solved row
	return count;
}
int Board::findOther1(int x)
{
	if (x % 3 == 1)
		return x + 1;
	else if (x % 3 == 2)
		return x - 1;
	else if (x % 3 == 0)
		return x - 2;
}
int Board::findOther2(int x)
{
	if (x % 3 == 1)
		return x + 2;
	else if (x % 3 == 2)
		return x + 1;
	else if (x % 3 == 0)
		return x - 1;
}

int Board::SquareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
	// Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
	// coordinates of the square that i,j is in.  

	return squareSize * ((i - 1) / squareSize) + (j - 1) / squareSize + 1;
}

ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
	for (int i = 0; i < (int)v.size(); i++)
		ostr << v[i] << " ";
	ostr << endl;
	return ostr;
}

ValueType Board::GetCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
	if (i >= 1 && i <= boardSize && j >= 1 && j <= boardSize)
		return value[i][j];
	else
		throw rangeError("bad value in GetCell");
}

bool Board::IsBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
	if (i < 1 || i > boardSize || j < 1 || j > boardSize)
		throw rangeError("bad value in isBlank");
	if (value[i][j] == 0)
		return true;
	return false;
}

void Board::Print()
// Prints the current board.
{
	for (int i = 1; i <= boardSize; i++)
	{
		if ((i - 1) % squareSize == 0)
		{
			cout << " -";
			for (int j = 1; j <= boardSize; j++)
				cout << "---";
			cout << "-";
			cout << endl;
		}
		for (int j = 1; j <= boardSize; j++)
		{
			if ((j - 1) % squareSize == 0)
				cout << "|";
			if (!IsBlank(i, j))
				cout << " " << GetCell(i, j) << " ";
			else
				cout << "   ";
		}
		cout << "|";
		cout << endl;
	}
	cout << " -";
	for (int j = 1; j <= boardSize; j++)
		cout << "---";
	cout << "-";
	cout << endl;

	//print conflicts
	for (int i = 1; i <= boardSize; i++)
	{
		cout << "Conflict Row #" << i << " ";
		for (int j = 1; j <= boardSize; j++)
		{
			cout << row[i][j] << " ";
		}
		cout << endl;
	}cout << endl;
	for (int i = 1; i <= boardSize; i++)
	{
		cout << "Conflict Col #" << i << " ";
		for (int j = 1; j <= boardSize; j++)
		{
			cout << col[i][j] << " ";
		}
		cout << endl;
	}cout << endl;
	for (int i = 1; i <= boardSize; i++)
	{
		cout << "Conflict Box #" << i << " ";
		for (int j = 1; j <= boardSize; j++)
		{
			cout << box[i][j] << " ";
		}
		cout << endl;
	}cout << endl;
	cout << "Calls=" << calls << endl;
}
int Board::getCalls()
{
	int c = calls;
	calls = 0;
	return c;
}

int main()
{
	ifstream fin;

	// Read the sample grid from the file.
	string fileName = "sudoku.txt";
	int squareSize = 9;
	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	try
	{
		Board b1(squareSize);
		double count = 0;
		int avg = 0;
		while (fin && fin.peek() != 'Z')
		{
			b1.Initialize(fin);
			//b1.Print();
			b1.solve();

			
			int c = b1.getCalls();
			cout << c << endl;
			count++;
			avg +=c;





			if (!b1.isSolved())
				cout << "Board is not solved" << endl;
			else
				cout << "Board is solved" << endl;

			//	b1.PrintConflicts();

		}
		cout << endl << endl << "AVERAGE CALLS= " << avg / count << endl;
		cin.get(); //to pause the program after completion
		cin.get();
		return 0;
	}
	catch (rangeError &ex)
	{
		cout << ex.what() << endl;
		exit(1);
	}
}
