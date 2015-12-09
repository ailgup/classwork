#include "WordList.h"

/*
Christopher Puglia
pug-3a
10/11/2015
Compiled on Visual Studio

g++ - o list pug - 3a.cpp WordList.cpp WordList.h Grid.cpp Grid.h - std = c++0x

Functions:
WordList();
	-constructs an empty wordList
void build(std::string st);
	-builds a WordList from file st
void insertionSort();
	-runs the insertion sort on the WordList
void quickSort(int p, int r);
	- performs the quick sort on the WordList
int partition(int p, int r);
	- helper function for the quick sort algorithm
void mergeSort(int low, int high);
	-uses merge sort algorithm to sort the WordList
int size();
	-returns size of WordList
void merge(int low, int mid, int high);
	- merge sort helper function
bool binarySearch(std::string str);
	-uses binary search to find str in WordList, returns true if found
	false if not
friend ostream& operator<<(ostream& os, const WordList& wl);
	-overloaded print operator to print out list
*/
/*
WordList();
-constructs an empty wordList
*/
WordList::WordList()
{
}
/*
void build(std::string st);
-builds a WordList from file st
*/
void WordList::build(std::string st)
{
	ifstream infile;
	infile.open(st);
	if (infile.fail())
	{
		throw std::invalid_argument("Invalid file name\n");
	}
	std::string line;
	while (getline(infile, line))
	{
		myLines.push_back(line);
	}
	infile.close();
	
}
/*
friend ostream& operator<<(ostream& os, const WordList& wl);
-overloaded print operator to print out list
*/
ostream& operator<<(ostream& os, const WordList& wl)
{
	for (std::vector<string>::const_iterator i = wl.myLines.begin(); i != wl.myLines.end(); ++i)
		os << *i << ' '; 
	return os;
}

/*
void insertionSort();
-runs the insertion sort on the WordList
*/

void WordList::insertionSort()
{
	clock_t t;
	t = clock();
	int maxIdx;
	for (unsigned int i = 0; i<myLines.size() - 1; i++) {
		maxIdx = i;
		for (unsigned int j = i + 1; j<myLines.size(); j++)
			if (myLines[j] < myLines[maxIdx])
				maxIdx = j;

		// swap values
		if (maxIdx != i) {
			string temp = myLines[i];
			myLines[i] = myLines[maxIdx];
			myLines[maxIdx] = temp;
		}
	}
	t = clock() - t;
	cout << "Time for insertionSort = " << (((float)t) / CLOCKS_PER_SEC) << "secs"<<endl;
}
//start ith p=0, r=piviot=last
/*
void quickSort(int p, int r);
- performs the quick sort on the WordList
*/
void WordList::quickSort(int p, int r)
{

	if (p < r)
	{
		int q = partition(p, r);
		quickSort(p, q-1);
		quickSort(q + 1, r);
	}
	
}
/*
int partition(int p, int r);
- helper function for the quick sort algorithm
*/
int WordList::partition(int left, int right)
{
	string x = myLines[right]; //piviot
	string temp;
	int j = right;
	int i = left - 1;

	while (true)
	{
		while (myLines[++i] < x);

		while (myLines[--j] > x) {
			if (j == left)
				break;
		}

		if (i >= j)
			break;

		temp = myLines[i];
		myLines[i] = myLines[j];
		myLines[j] = temp;
	}

	temp = myLines[i];
	myLines[i] = myLines[right];
	myLines[right] = temp;

	return i;
}
/*
void mergeSort(int low, int high);
-uses merge sort algorithm to sort the WordList
*/
void WordList::mergeSort(int low, int high)
{
	if (low >= high) return;
	int mid = (low + high) / 2;
	mergeSort(low, mid);  //left half
	mergeSort(mid + 1, high);  //right half
	merge(low, mid, high);  //merge them
}
void WordList::heapSort()
{
	Heap <string> h1;
	h1.initalizeHeap(myLines);
	h1.heapSort();
	//h1.heapSort(h1.heapSize()-1);
	//h1.printHeap();
	myLines = h1.getHeap();
}
/*
int size();
-returns size of WordList
*/
int WordList::size()
{
	return myLines.size();
}
/*
void merge(int low, int mid, int high);
- merge sort helper function
*/
void WordList::merge(int low, int mid, int high)
{
	string *temp = new string[high - low + 1];
	int left = low;
	int right = mid + 1;
	int current = 0;
	// Merges the two arrays into temp[] 
	while (left <= mid && right <= high) {
		if (myLines[left] <= myLines[right]) {
			temp[current] = myLines[left];
			left++;
		}
		else { // if right element is smaller that the left
			temp[current] = myLines[right];
			right++;
		}
		current++;
	}

	// Completes the array 
	if (left > mid) {
		for (int i = right; i <= high; i++) {
			temp[current] = myLines[i];
			current++;
		}
	}
	// So, the left side of array a will be used to fill temp.
	else {
		for (int i = left; i <= mid; i++) {
			temp[current] = myLines[i];
			current++;
		}
	}
	// into the original array
	for (int i = 0; i <= high - low; i++) {
		myLines[i + low] = temp[i];
	}
	delete[] temp;

}
/*
bool binarySearch(std::string str);
-uses binary search to find str in WordList, returns true if found
false if not
*/
bool WordList::binarySearch(std::string key)
{
	int iteration = 0, left = 0, right = myLines.size() - 1, mid;

	while (left <= right) {
		iteration++;
		mid = (int)((left + right) / 2);
		if (key == myLines[mid]) {
			//cout << "Binary search found " << myLines[mid] << " after " << iteration << " iterations.\n";
			iteration++;
			return true;
		}
		else if (key > myLines[mid])
			left = mid + 1;
		else
			right = mid - 1;
	}
	
	return false;
}


