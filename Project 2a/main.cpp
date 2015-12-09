/* Algorithms Project 2a
Christopher Puglia
9/26/2015

Compiled on Windows using C++11 
also tested on COE Linux using the following command

	g++ main.cpp Deck.cpp Card.cpp Node.cpp -o main
*/
#include <string>
#include <iostream>
#include "Deck.h"
using namespace std;

int main()
{
	try
	{
	Deck d1; //create deck
	cout << d1; //use overloaded operator
	//d1.shuffle();
	//cout << "\n\n\nShuffled:\n" << d1;

	cin.get(); //to pause the program after completion
	cin.get();
	return 0;
	}
	catch(...) //Catch all errors and exit gracefully
	{
		cout << "Error in program runtime\n";
	}
	
}

