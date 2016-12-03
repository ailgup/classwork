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

#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>       /* time */
#include "Code.h"
using namespace std;
/*
Code Class
Description:
Contains a vector of integers that make up a "code" which is 4 digits long
Functions:
void printCode();
- prints out code to screen
void genRandom();
-fills code with random int's [0-5]
void setCode(vector<int> i);
-fills code with vector i
vector<int> getCode();
- returns the code as a vector
int checkCorrect(Code b);
- returns number of correct digits between code and b
int checkIncorrect(Code b);
- returns number of incorrect digits between code and b

*/
/*
Code Constructor
Overloads the default constructor to fill code with 0's
*/
Code::Code()
{
	for (int i = 0; i < 4; i++)
		code.push_back(0);
}
/*
genRandom()
Fills the code with 4 random integers [0,5]
*/
void Code::genRandom()
{
	//seeding the random int
	srand(time(NULL));
	for (int i = 0; i < 4; i++)
		code[i] = (rand() % (int)(6));
}
/*
setCode(vector<int> i);
Fills code with vector i
*/
void Code::setCode(vector<int> i)
{
	code = i;
}
/*
getCode()
return code as a vector of integers*/
vector<int> Code::getCode()
{
	return code;
}
/*
printCode()
prints the code out to the screen
*/
void Code::printCode()
{
	std::cout << "[";
	for (auto v : code)
	{
		std::cout << v << " ";
	}
	std::cout << "\b]\n";
}
/*
checkCorrect(Code b)
Returns the number of integrs in the same location
in both code and b
*/
int Code::checkCorrect(Code b)
{
	vector<int> a = b.getCode();
	int correct = 0;
	//itterare thru b
	for (int i = 0; i < a.size(); i++)
	{
		//we found a match!!
		if (a.at(i) == code.at(i))
			correct++;
	}
	return correct;
}
/*
checkIncorrect(Code b)
Returns the number of integers that are in code and b, but are in the
incorrect position, taking care not to count a digit twice*/
int Code::checkIncorrect(Code b)
{
	vector<bool> prev{ false, false, false, false}; //used to store digits that match or are already counted

	for (int i = 0; i < b.getCode().size(); i++) //pre check for matches and put them in prev to ignore later
	{
		//we found a match!!
		if (b.getCode().at(i) == code.at(i))
			prev[i] = true;
	}


	int incorrect = 0;
	for (int i = 0; i < b.getCode().size(); i++) //itterare thru b
	{
		if (code[i] != b.getCode()[i]) //if the two are not matches we can look deeper
		{
			for (int j = 0; j < code.size(); j++) //now itterate thru code to find a match
			{
				if (code[j] == b.getCode()[i]) //we found a match
				{
					if(prev[j]) //if prev has code[j] in it then we don't want it
					{
						/* prev contains code[j], don't want to double count it */
						break;
					}
					else //not yet in prev, then we want to count it
					{
						prev[j] = true; //add to prev so we don't count it again
						incorrect++; //increment
						break;
					}	
				}
			}
		}
	}
	return incorrect;
}