#pragma once
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

class Response
{
public:
	Response();
	Response(int cor, int incor);
	void setCor(int cor);
	void setIncor(int incor);
	int getCor();
	int getIncor();
	bool compResponse();
	void printResponse();

private:
	int correct;
	int incorrect;
};