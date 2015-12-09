/* Mastermind Class

Description: allows user to play game by creating a secert code and allowing users to try and guess it,
returning a responce each timg, dependent on Response and Code

Functions:
Mastermind();
-constructs a Mastermind object and generates the secert code
void playGame();
- function that allows user to play, uses humanGuess and getResponse to do much of the heavy lifting
bool isSolved(Response a);
-returns true if the user has won the game
Response getResponse(Code guess, Code secret);
-returns a Response from two codes, the guess which the user inputs and the secert
Code humanGuess();
- takes in the guess from the user and stores it in a Code, also some error checking
void printSecret();
-prints secert out using the printCode()
*/

#include "Mastermind.h"

/*			Mastermind();
-constructs a Mastermind object and generates the secert code*/
Mastermind::Mastermind()
{
	secret.genRandom();
}

/*void playGame();
- function that allows user to play, uses humanGuess and getResponse to do much of the heavy lifting
*/
void Mastermind::playGame()
{
	bool winning = false;
	cout << "Welcome to Mastermind\n\nRandom Code:\n";
	
	/*
	USed to hard code test cases
	vector<int> secret2{ 1,2,3,4 };
	secret.setCode(secret2);
	*/


	secret.printCode();
	for (int i = 1; i <= 10; i++)
	{
		cout << "\n Guess #" << i << "\n";
		Response resp = getResponse(humanGuess(), secret);
		resp.printResponse();
		if (isSolved(resp))
		{
			cout << "\n\nYOU WON!!!!!";
			winning = true;
			break;
		}
	}
	if (!winning)
		cout << "You Lost";
}
/*bool isSolved(Response a);
-returns true if the user has won the game
*/
bool Mastermind::isSolved(Response a)
{
	return a.compResponse();
}
/*Response getResponse(Code guess, Code secret);
-returns a Response from two codes, the guess which the user inputs and the secert
*/
Response Mastermind::getResponse(Code guess, Code secret)
{
	Response r1(guess.checkCorrect(secret), secret.checkIncorrect(guess));
	return r1;
}
/*Code humanGuess();
- takes in the guess from the user and stores it in a Code, also some error checking
*/
Code Mastermind::humanGuess()
{
	std::cout << "Enter 4 digits [0,5] :\n";
	vector<int> temp;
	bool guicci = true; //loop controll var
	while (guicci)
	{

		for (int i = 0; i < 4; i++)
		{
			temp.push_back(0); //fill with empty values '0'
		}
		cin >> temp[0] >> temp[1] >> temp[2] >> temp[3]; //take in all the vars
		if (cin.fail() || temp[0]>5 || temp[1]>5 || temp[2]>5 || temp[3]>5
			|| temp[0]<0 || temp[1]<0 || temp[2]<0 || temp[3]<0) //if not an int or the int is Out of Bounds error
		{
			cout << "Wrong data entered!! Try Again\n";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear buffer and retry
		}
		else
			guicci = false; //otherwise we are good to go
	}
	Code c1; //create guessed code
	c1.setCode(temp); //fill it with temp

	return c1;
}
/*			void printSecret();
-prints secert out using the printCode()
*/
void Mastermind::printSecret()
{
	secret.printCode();
}