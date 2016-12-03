#include <string>
#include <iostream>
#include <sstream>
/* Card Class
	Functions:
	Card();
		Overloaded default constructor makes a Card with suit ' ' and value 0
	Card(int v, char s);
		Constructor makes a Card with value v and suit s
	void setValue(int v);
		sets Card value to give int v
		legal values are fron 2-14
	void setSuit(char s);
		sets suit to s, 
		legal values are 'C','D','H','S'
	int getValue();
		returns card value as int 2-14
	char getSuit();
		returns card suit as char 'C','D','H','S'
	void printCond();
		prints a consensed representation of a card eg. '2S'
		instead of '2 of spades'
	*/
class Card
{
public:
	Card();
	Card(int v, char s);
	void setValue(int v);
	void setSuit(char s);
	int getValue();
	char getSuit();
	void printCond();
	/*
	Overloaded cout operator
		prints out the Caard's value in verbose format
	*/
	friend std::ostream &operator<<(std::ostream &output, Card &C)
	{
		std::stringstream ss;
		std::string x,y;
		if (C.getSuit() == 'H')
			x = "Hearts";
		else if (C.getSuit() == 'D')
			x = "Diamonds";
		else if (C.getSuit() == 'S')
			x = "Spades";
		else if (C.getSuit() == 'C')
			x = "Clubs";
		else
			x = "Illegal";

		if (C.getValue() > 10)
		{
			if (C.getValue() == 11)
				y = "Jack";
			else if (C.getValue() == 12)
				y = "Queen";
			else if (C.getValue() == 13)
				y = "King";
			else if (C.getValue() == 14)
				y = "Ace";
		}
		else
		{	ss << C.getValue();
			y = ss.str();
		}
		output << y << " of " << x;
		return output;
	}

private:
	int value;
	char suit;
};
