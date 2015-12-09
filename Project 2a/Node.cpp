/* Algorithms Project 2a
Christopher Puglia
9/26/2015

Compiled on Windows using C++11
also tested on COE Linux using the following command

g++ main.cpp Deck.cpp Card.cpp Node.cpp -o main
*/

#include "Node.h"
/*
Node(Card c, Node* nxt);
	Constructor creates a node with a Card and a pointer to the next Node.
*/
Node::Node(Card c, Node * nxt)
{
	next = nxt;
	card = c;
}
/*
Node(Card c);
	Constructor creates a node with a Card and a NULL pointer, can be used for end
*/
Node::Node(Card c)
{
	card = c;
	next = NULL;
}
/*
Node();
	default constructor created a node with NULL pointer and a NULL card
*/
Node::Node()
{
	next = NULL;
}
