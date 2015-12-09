#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h> 
#include <stdexcept>
/*
Christopher Puglia
pug-3a
10/11/2015
Compiled on Visual Studio

g++ - o list pug - 3a.cpp WordList.cpp WordList.h Grid.cpp Grid.h - std = c++0x

*/
using namespace std;
class WordList
{
public:
	WordList();
	void build(std::string st);
	void insertionSort();
	void quickSort(int p, int r);
	int partition(int p, int r);
	void mergeSort(int low, int high);
	int size();
	void merge(int low, int mid, int high);
	bool binarySearch(std::string str);
	friend ostream& operator<<(ostream& os, const WordList& wl);

private:
	std::vector<std::string> myLines;

};