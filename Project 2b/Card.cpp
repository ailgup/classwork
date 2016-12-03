/* Algorithms Project 2b
Christopher Puglia
9/30/2015

Compiled on Windows using C++11
also tested on COE Linux using the following command

g++ -o main Card.cpp Deck.cpp Node.cpp main.cpp -std=c++0x


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
/* Overloaded Copy COnstructor
This copies the value and suit variables over to the new object
*/
Card::Card(const Card & obj)
	: value(obj.value), suit(obj.suit)
{
	//std::cout << "CPY" << std::endl;
}
/* Overloaded Assignment Operator
This overloads the = operator to allow for assignment of one Card to another.
*/
Card & Card::operator=(const Card & c2)
{
	value = c2.value;
	suit = c2.suit;
	return *this;
}
/*
Card(int v, char s);
Constructor makes a Card with value v and suit s
*/
Card::Card(int v, char s)
{
	if (v > 14 || v < 2)
	{
		throw std::invalid_argument("Value of Card is out of range");
	}
	if(s!='C'&& s != 'D' && s != 'H' && s != 'S')
	{
		throw std::invalid_argument("Suit of Card is Illegal");
	}
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
	if (v > 14 || v < 2)
	{
		throw std::invalid_argument("Value of Card is out of range");
	}
	else
	value = v;
}
/*
void setSuit(char s);
	sets suit to s,
	legal values are 'C','D','H','S'
*/
void Card::setSuit(char s)
{
	if (s != 'C'&& s != 'D' && s != 'H' && s != 'S')
	{
		throw std::invalid_argument("Suit of Card is Illegal");
	}
	else
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
