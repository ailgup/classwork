#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
/*
Christopher Puglia
pug-3a
10/11/2015
Compiled on Visual Studio

g++ - o list pug - 3a.cpp WordList.cpp WordList.h Grid.cpp Grid.h - std = c++0x

*/

using namespace std;
class Grid{
public:
	Grid();
	void buildGrid(std::string file);
	void printGrid();
	int getRows();
	int getCols();
	void setCols(int c);
	void setRows(int r);
	char getPos(int row, int col);
	std::string readWord(int row, int col, int dir, int length);

private:
	char** ary;
	int rows;
	int cols;
	int curR;
	int curC;
};