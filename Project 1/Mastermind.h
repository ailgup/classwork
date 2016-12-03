#pragma once
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

#include "Response.h"
#include "Code.h"
#include <iostream>

class Mastermind
{
public:
	Mastermind();
	void playGame();
	bool isSolved(Response a);
	Response getResponse(Code guess, Code secret);
	Code humanGuess();
	void printSecret();

private:
	Code secret;
};
