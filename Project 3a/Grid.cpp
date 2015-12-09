#include "Grid.h"
/*
Christopher Puglia
pug-3a
10/11/2015
Compiled on Visual Studio

g++ - o list pug - 3a.cpp WordList.cpp WordList.h Grid.cpp Grid.h - std = c++0x

Functions:
Grid();
	- Grid constructor, buildsan empty grid
void buildGrid(std::string file);
	-opens file and builds a grid from that file
void printGrid();
	-prints out the grid to the screen
int getRows();
	-returns the number of rows in the grid
int getCols();
	-returns the number of columns in the grid
void setCols(int c);
	-sets the number of columns in the grid
void setRows(int r);
	-sets the number of rows in the grid
char getPos(int row, int col);
	returns the char at the given position [row,col]
std::string readWord(int row, int col, int dir, int length);
	-reads a word from the grid, starting at [row,col] moving
	in dir, direction and of length length. 
*/
/*
Grid();
- Grid constructor, buildsan empty grid
*/
Grid::Grid()
{
	curR = 0;
	curC = 0;
}
/*
void buildGrid(std::string file);
-opens file and builds a grid from that file
*/
void Grid::buildGrid(std::string file)
{
	ifstream infile;
	infile.open(file);
	if (infile.fail())
	{
		throw std::invalid_argument("Invalid file name\n");
	}
	std::string line;
	infile >> rows;
	infile >> cols;
	ary = new char*[rows];
	for (int i = 0; i < rows; ++i)
		ary[i] = new char[cols];
	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
		if (infile >> ary[i][j]) {
				//cout << ary[i][j]<<" ";
			}
		}
		//cout << "\n";
	}
	

		// read succeeded, use grid_i
		
	infile.close();
	
	
}
/*
void printGrid();
-prints out the grid to the screen
*/
void Grid::printGrid()
{
}
/*
int getRows();
-returns the number of rows in the grid
*/
int Grid::getRows()
{
	return rows;
}
/*
int getCols();
-returns the number of columns in the grid
*/
int Grid::getCols()
{
	return cols;
}
/*
void setCols(int c);
-sets the number of columns in the grid
*/
void Grid::setCols(int c)
{
	cols = c;
}
/*
void setRows(int r);
-sets the number of rows in the grid
*/
void Grid::setRows(int r)
{
	rows = r;
}
/*
char getPos(int row, int col);
returns the char at the given position [row,col]
*/
char Grid::getPos(int row, int col)
{
	return ary[row][col];
}
/*
std::string readWord(int row, int col, int dir, int length);
-reads a word from the grid, starting at[row, col] moving
in dir, direction and of length length.
*/
std::string Grid::readWord(int row, int col, int dir, int length)
{
	curR = row;
	curC = col;
	std::string daWord;
	for (int i = 0; i < length; i++)
	{
		if (curR > rows-1)
			curR = 0;
		if (curR < 0)
			curR = rows-1;
		if (curC > cols-1)
			curC = 0;
		if (curC < 0)
			curC = cols-1;

		//directional
		if (dir == 0) //N
		{
			daWord+=ary[curR][curC];
			curR--;
		}
		else if (dir == 1) //NE
		{
			daWord += ary[curR][curC];
			curR--;
			curC++;
		}
		else if (dir == 2) //E
		{
			daWord += ary[curR][curC];
			curC++;
		}
		else if (dir == 3) //SE
		{
			daWord += ary[curR][curC];
			curR++;
			curC++;
		}
		else if (dir == 4) //S
		{
			daWord += ary[curR][curC];
			curR++;
		}
		else if (dir == 5) //SW
		{
			daWord += ary[curR][curC];
			curR++;
			curC--;
		}
		else if (dir == 6) //W
		{
			daWord += ary[curR][curC];
			curC--;
		}
		else if (dir == 7) //NW
		{
			daWord += ary[curR][curC];
			curR--;
			curC--;
		}
	}
	return daWord;
}
