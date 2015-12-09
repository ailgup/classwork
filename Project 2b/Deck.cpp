/* Algorithms Project 2b
Christopher Puglia
9/30/2015

Compiled on Windows using C++11
also tested on COE Linux using the following command

g++ -o main Card.cpp Deck.cpp Node.cpp main.cpp -std=c++0x


*/

#include "Deck.h"
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>
/*	Deck();
		Default Constructor that creates a Deck of 52 Nodes with Card's 2-A C-S
		and places then in a linked list of Nodes. Instance variable first holds the 
		pointer to the first Node of the list*/
Deck::Deck()
{
	Node *prev = NULL;
	Node *now;
	char suits[] = { 'C','D','H','S'}; //Suits are denoted by char's
	for (int i = 3; i >= 0; i--) //itterate thru the suits
	{
		for (int j = 14; j >= 2; j--) //itterate theu the values
		{
			now = new Node (Card(j, suits[i]));
			now->next = prev;
			prev = now;
		}
	}
	first = prev;
}
/* Overloaded Copy COnstructor
		This copies the pointer of the first card to a new pointer and assins it to first
*/
Deck::Deck(const Deck & obj)
{
	first = new Node(*obj.first);
}
/* Overloaded Assignment Operator
		This overloads the = operator to allow for assignment of one Deck to another.
*/
Deck & Deck::operator=(const Deck & d2)
{
	*first = *d2.first;
	return *this;
}
/* Deck destructor */
Deck :: ~Deck()
{
	delete first;
}
/*
Node* getFirst();
	Returns the Node on the top of the deck
*/
Node * Deck::getFirst()
{
	return first;
}

/*
void shuffle();
	Shuffles the deck randomly using a intermediate vector and the std::random_shuffle function*/
void Deck::shuffle()
{
	srand((unsigned int)time(NULL));
	std::vector <Card> lst;
	Node *p = first;
	while (p != NULL) //go thru the linked list
	{
		lst.push_back(p->card); //push cards onto the vector
		p = p->next;
	}
	std::random_shuffle(lst.begin(), lst.end()); //shuffle the vector
	//now rebuild the linked list
	Node *prev = NULL;
	Node *now;
	for (size_t i = 0; i < lst.size(); i++) // go thru all the Nodes
	{
		now = new Node(lst.at(i));
		now->next = prev;
		prev = now;

	}
	first = prev; //re set first the the new first node
	
}
void Deck::replace(Card c)
{
	Node *add  = new Node(c, NULL);
	Node *p = first;
	while (p->next != NULL) //go thru the linked list
	{
		p = p->next;
	}
	p->next = add;

}
Card Deck::deal()
{
	if (first == NULL)
		return Card();
	Node *p = first;
	first = p->next;
	return p->card;
}
/*
void printDeck();
	Prints out the contents of the deck to the screen
*/
void Deck::printDeck()
{
	Node *p = first;

	while (p != NULL) //itterate thru all nodes
	{
		p->card.printCond();
		std::cout << "\n"; //uses overloaded << operator for Cards
		p = p->next;
	}
}
