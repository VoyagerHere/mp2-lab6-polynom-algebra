#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"

using namespace std;

class TPostfix
{
	string infix;
	string postfix;
	//operation stack
	TStack <char> sc;
	//operand stack
	TStack <double> sd;
	//to store the values of variables
	double* p;
public:
	TPostfix()
	{
		p = new double[10];
	}
	~TPostfix()
	{
		delete[] p;
	}

	// Changed in accordance with the coding rules

	int prior(char a);
	void set_infix(string t);
	string get_infix() { return infix; }
	string get_postfix() { return postfix; }
	string to_postfix();
	// gets variables and calculates following postfix form
	double calculate();
};

#endif
