/*
Engineering Algotithms
Project 1
Christopher Puglia
9/15/2015

Compiled and Run on MS Visual Studio 

Program allows the user to play the game Mastermind against the 
computer, the user is given 10 chances to guess the 4 digit code
each time getting a reply in the syntax (num correct, num incorrect)

*/

#include "Mastermind.h"

/* main()
	-Creates a Mastermind object and runs it using playGame()*/

int main()
{
	Mastermind m1;
	m1.playGame();

	cin.get(); //to pause the program after completion
	cin.get();
	return 0;
}