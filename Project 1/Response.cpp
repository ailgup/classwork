/* Respose Class
Description: Response is used to process the number of correct and incorrect digits
between the secert code and the user generated code, it also makes the message
to send out to the user after each turn
Functions:
Response();
-overloads default constuctor, sets both correct and incorrect to 0
Response(int cor, int incor);
-overloads constructor, sets correct to cor and incorrect to incor
void setCor(int cor);
-just sets the correct variable
void setIncor(int incor);
-just sets incorrect
int getCor();
-returns correct
int getIncor();
-returns incorrect
bool compResponse();
-returns true if the codes are identical, aka correct=length and false if they are not
void printResponse();
-prints response to screen using syntax (correct, incorrect)
*/


#include "Response.h"
#include <iostream>
/*Function Response();
-overloads default constuctor, sets both correct and incorrect to 0
*/

Response::Response()
{
	correct = 0;
	incorrect = 0;
}
/*Function Response(int cor, int incor);
-overloads constructor, sets correct to cor and incorrect to incor
*/
Response::Response(int cor, int incor)
{
	correct = cor;
	incorrect = incor;
}
/*void setCor(int cor);
-just sets the correct variable
*/
void Response::setCor(int cor)
{
	correct = cor;
}
/*void setIncor(int incor);
-just sets incorrect
*/
void Response::setIncor(int incor)
{
	incorrect = incor;
}
/*int getCor();
-returns integer correct
*/
int Response::getCor()
{
	return correct;
}
/*	int getIncor();
-returns incorrect
*/
int Response::getIncor()
{
	return incorrect;
}
/* bool compResponse();
-returns true if the codes are identical, aka correct=length and false if they are not*/
bool Response::compResponse()
{
	if (correct == 4)
		return true;
	return false;
}
/*void printResponse();
-prints response to screen using syntax (correct, incorrect)
*/
void Response::printResponse()
{
	std::cout << "(" << correct << "," << incorrect << ")\n";
}