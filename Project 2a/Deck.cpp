/* Algorithms Project 2a
Christopher Puglia
9/26/2015

Compiled on Windows using C++11
also tested on COE Linux using the following command

g++ main.cpp Deck.cpp Card.cpp Node.cpp -o main
*/

#include "Deck.h"
#include <vector>
#include <algorithm>
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
