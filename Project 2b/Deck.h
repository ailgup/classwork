#include "Node.h"
/*
Deck Class
Conatins:
	Deck();
		Default Constructor that creates a Deck of 52 Nodes with Card's 2-A C-S
	Node* getFirst();
		Returnes the Node on the top of the deck
	void shuffle();
		Shuffles the deck randomly
	void printDeck();
		Prints out the contents of the deck to the screen
	
*/
class Deck
{
public:
	Deck();
	Deck(const Deck & obj);
	Deck & operator= (const Deck& d2);
	~Deck();
	Node* getFirst();
	void shuffle();
	void replace(Card c);
	Card deal();
	void printDeck();
	/* Print opperator overload
		Prints out each "Card" in the deck
	*/
	friend std::ostream &operator<<(std::ostream &output, Deck &D)
	{
		Node *p = D.getFirst();
		while (p != NULL)
		{
			output << p->card << "\n";
			p = p->next;
		}
		return output;
	}
private:
	Node* first;


};