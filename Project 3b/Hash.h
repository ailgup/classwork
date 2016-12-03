#include <vector>
#include <cstdlib>
#include <functional>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
/*
Christopher Puglia
pug-3b
10/18/2015
Compiled on Visual Studio

g++ -o list pug-3b.cpp Hash.h Heap.h WordList.cpp WordList.h Grid.cpp Grid.h -std=c++0x
*/

using namespace std;
template <class T>
class HashTable
{
public:
	HashTable(int length);
	int Hash(T &ele);
	void addItem(T ele);
	bool deleteItem(T ele);
	bool inList(T ele);
	void buildTable(std::string file);


private:
	std::vector< std::vector<T> > hashTable;
	int size;
};



template<class T>
HashTable<T>::HashTable(int length)
{
	size = length;
	hashTable.resize(length);
}



template<class T>
int HashTable<T>::Hash(T &item) {
	std::hash<T> h; // specializes h() to work on obj type T
	return h(item) % size;
}

template<class T>
void HashTable<T>::addItem(T ele)
{
	int index = Hash(ele);
	hashTable[index].push_back(ele);

}

template<class T>
bool HashTable<T>::deleteItem(T ele)
{
	int index = Hash(ele);
	int len = hashTable[index].size();
	for (int i = 0; i < len; i++)
	{
		if (hashTable[index].at(i) == ele)
		{
			hashTable[index].erase(i+ hashTable[index].begin());
			return true;
		}
	}
	return false;
}

template<class T>
bool HashTable<T>::inList(T ele)
{
	int index = Hash(ele);
	int len = hashTable[index].size();
	for (int i = 0; i < len; i++)
	{
		if (hashTable[index].at(i) == ele)
		{
			return true;
		}
	}
	return false;
}

template<class T>
void HashTable<T>::buildTable(std::string file)
{
	std::vector <T> temp;
	int tempSize = 0;
	std::ifstream infile;
	infile.open(file);
	if (infile.fail())
	{
		throw std::invalid_argument("Invalid file name\n");
	}
	std::string line;
	while (getline(infile, line))
	{
		temp.push_back(line);
		tempSize++;
	}
	infile.close();
	size = tempSize;
	hashTable.resize(size);
	for (int i = 0; i < temp.size(); i++)
	{
		addItem(temp.at(i));
	}
}
