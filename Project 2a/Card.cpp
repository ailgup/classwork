
/* Algorithms Project 2a
Christopher Puglia
9/26/2015

Compiled on Windows using C++11
also tested on COE Linux using the following command

g++ main.cpp Deck.cpp Card.cpp Node.cpp -o main
*/

#include "Card.h"
/*
Card();
		Overloaded default constructor makes a Card with suit ' ' and value 0
*/
Card::Card()
{
	value = 0;
	suit = ' ';
}
/*
Card(int v, char s);
Constructor makes a Card with value v and suit s
*/
Card::Card(int v, char s)
{
	suit = s;
	value = v;
}
/*
void setValue(int v);
	sets Card value to give int v
	legal values are fron 2-14
*/
void Card::setValue(int v)
{
	value = v;
}
/*
void setSuit(char s);
	sets suit to s,
	legal values are 'C','D','H','S'
*/
void Card::setSuit(char s)
{
	suit = s;
}
/*
int getValue();
	returns card value as int 2-14
*/
int Card::getValue()
{
	return value;
}
/*
char getSuit();
	returns card suit as char 'C','D','H','S'
*/
char Card::getSuit()
{
	return suit;
}
/*
void printCond();
	prints a consensed representation of a card eg. '2S'
	instead of '2 of spades'*/
void Card::printCond()
{
	std::stringstream ss;
	std::string y;
	
	if (value > 10)
	{
		if (value == 11)
			y = "J";
		else if (value == 12)
			y = "Q";
		else if (value == 13)
			y = "K";
		else if (value == 14)
			y = "A";
	}
	else //need to convert itn to string
	{
		ss << value;
		y = ss.str();
	}
	std::cout << y << " " << suit;
	
}
