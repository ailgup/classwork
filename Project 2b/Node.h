#include "Card.h"
#include <iostream>
/*
Class node
	Used in creation of a linked list of Card's includes a Card and a pointer to the next Node

	Functions:
		Node(Card c, Node* nxt);
			Constructor creates a node with a Card and a pointer to the next Node.
		Node(Card c);
			Constructor creates a node with a Card and a NULL pointer, can be used for end
		Node();
			default constructor created a node with NULL pointer and a NULL card
*/
class Node
{
public:
	Node(Card c, Node* nxt);
	Node(Card c);
	Node();

	Node *next;
	Card card;

};