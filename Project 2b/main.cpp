/* Algorithms Project 2b
Christopher Puglia
9/30/2015

Compiled on Windows using C++11 
also tested on COE Linux using the following command

	g++ -o main Card.cpp Deck.cpp Node.cpp main.cpp -std=c++0x


*/
#include <string>
#include <iostream>
#include "Deck.h"
#include <stdexcept>
using namespace std;
void playFlip();

int main()
{
	try
	{
	playFlip();

	cin.get(); //to pause the program after completion
	cin.get();
	return 0;
	}
	catch(const std::invalid_argument& e) //Catch all errors and exit gracefully
	{
		cout << e.what()<<endl;
	}
	
}
/*
Function playFlip()
	This function plays the flip game taking input from the user and outputing the score
*/
void playFlip()
{
	Deck d1;
	double points = 0;
	int cont = 1;
	cout << "Welcome to Flip\nShuffling 3 times" << endl;
	d1.shuffle(); //triple shuffle
	d1.shuffle();
	d1.shuffle();

	cout << "Enter 1 to flip again or 0 to quit the game\n"<<endl;
	while (cont = 1) //loop that allows game to continue
	{
		cin >> cont;
		if (cont != 1 && cont != 0) //if illegal value entered
		{
			throw std::invalid_argument("Invalid value entered, only 0 or 1\n");
		}
		if (cont == 0)
			break;
		Card cn = d1.deal();
		d1.replace(cn);
		if (cn.getValue() == 0) //if at end of deck break out
		{
			cout << "Reached end of deck\n" << endl;
			break;
		}
		//Scoring portion
		if (cn.getValue() == 14)
			points += 10;
		else if (cn.getValue() == 11 || cn.getValue() == 12 || cn.getValue() == 13)
			points += 5;
		else if (cn.getValue() == 7)
			points = points / 2.0;
		else if (cn.getValue() >= 2 && cn.getValue() <= 6)
			points =0;
		if (cn.getSuit() == 'H')
			points++;
		cout << "Flip: " << cn << "\n  Score: " <<points<< endl; //display score
	}
	cout << "Game Over!! - Your Score: " << points << endl; //display final score
}

