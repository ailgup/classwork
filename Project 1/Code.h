#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>       /* time */
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
class Code
{
	//Function definitions
public:
	Code();
	void printCode();
	void genRandom();
	void setCode(vector<int> i);
	vector<int> getCode();
	int checkCorrect(Code b);
	int checkIncorrect(Code b);
private:
	//Instance variable code
	vector <int> code;
};