/*
Christopher Puglia
pug-3a
10/11/2015
Compiled on Visual Studio

g++ - o list pug - 3a.cpp WordList.cpp WordList.h Grid.cpp Grid.h - std = c++0x

Functions
void findMatches(WordList w1, Grid g1);
	-function takes in a WordList and a Grid and finds al the words from the 
	wordlist that are in the Grid
void search(int sort, WordList w1);
	-function takes in an unsorted WordList and sorts it using the algorithm
	selected with the sort int 
	(1) Selection Sort
	(2) Merge Sort
	(3)QuickSort
int main()
	-main function asks user for the desired sort method and then calls search()

*/
#include "WordList.h"
#include "Grid.h"
#include <stdexcept>

using namespace std;
void findMatches(WordList w1, Grid g1);
void search(int sort, WordList w1);
/*
int main()
-main function asks user for the desired sort method and then calls search()
*/

int main()
{
	try {
		WordList l1,l2,l3;

		l2.build("wordlist.txt");
		cout << "Using Merge Sort.." << endl;
		search(2, l2);
		l1.build("wordlist.txt");
		cout << "Using Insertion Sort.." << endl;
		search(1, l1);
		l3.build("wordlist.txt");
		cout << "Using Quick Sort.." << endl;
		search(3, l3);


		cin.get(); //to pause the program after completion
		cin.get();
		return 0;
	}
	catch (const std::invalid_argument& e) //Catch all errors and exit gracefully
	{
		cout << e.what() << endl;
	}
}
/*
void findMatches(WordList w1, Grid g1);
-function takes in a WordList and a Grid and finds al the words from the
wordlist that are in the Grid
*/
void findMatches(WordList w1, Grid g1)
{
	const int MAX_WORD_LEN = 23;
	for (int c = 0; c < g1.getCols(); c++)
	{
		//cout << "C:" << c << endl;
		for (int r = 0; r < g1.getRows(); r++)
		{
			for (int d = 0; d < 8; d++)
			{
				for (int l = 5; l < MAX_WORD_LEN; l++)
				{
					if (w1.binarySearch(g1.readWord(r, c, d, l)))
						cout << g1.readWord(r, c, d, l) << endl;
				}
			}
		}
	}
}
/*
void search(int sort, WordList w1);
-function takes in an unsorted WordList and sorts it using the algorithm
selected with the sort int
(1) Selection Sort
(2) Merge Sort
(3)QuickSort
*/
void search(int sort, WordList w1)
{
	string st1;
	cout << "Enter filename of grid:";
	cin >> st1;
	clock_t t;
	clock_t tot;
	tot = clock();
	//start time
	Grid g1;
	g1.buildGrid(st1);
	if (sort == 1)
	{//time
		t = clock();
		w1.insertionSort();
		t = clock() - t;
		cout << "Insertion sort took " << ((float)t) / CLOCKS_PER_SEC << "seconds" << endl;
	}
	else if (sort == 2)
	{//time
		t = clock();
		w1.mergeSort(0, w1.size() - 1);
		t = clock() - t;
		cout << "Merge sort took " << ((float)t) / CLOCKS_PER_SEC << "seconds" << endl;
	}
	else if (sort == 3)
	{//time
		t = clock();
		w1.quickSort(0, w1.size() - 1);
		t = clock() - t;
		cout << "Quick sort took " << ((float)t) / CLOCKS_PER_SEC << "seconds" << endl;
	}
	//time
	t = clock();
	findMatches(w1, g1);
	t = clock() - t;
	tot = clock() - tot;
	cout << "Search took " << ((float)t) / CLOCKS_PER_SEC << "seconds" << endl;
	cout << "Total Process took " << ((float)tot) / CLOCKS_PER_SEC << "seconds" << endl;
	//end time

}


