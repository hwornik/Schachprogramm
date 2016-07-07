#pragma once
#include <istream>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <sstream>
#include <string>
#include "Movement.h"

class Communicate
{
public:
	Communicate();
	~Communicate();
	bool init();
	bool setMovement(Movement *mymove);
	int input();
	//int com();
	bool send(std::string command);
	int sendmove(char move1[6]);
	bool setMode(int mode);
	int sendpondermove(char move1[6], char move2[6]);
	int sendmoves(char move1[6], char move2[6]);
	void setPonder();
protected:

private:
	int pipe;
	typedef void* HANDLE;
	HANDLE hstdin;
	int inputmethod;
	bool ponder;
	Movement *mymove;
};

