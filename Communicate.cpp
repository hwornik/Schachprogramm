#include "stdafx.h"
#include "Communicate.h"


Communicate::Communicate()
{
	inputmethod = 0;
}


Communicate::~Communicate()
{
}

bool Communicate::init()
{
	unsigned long dw;
	hstdin = GetStdHandle(STD_INPUT_HANDLE);
	pipe = !GetConsoleMode(hstdin, &dw);
	ponder = false;
	if (!pipe) {
		SetConsoleMode(hstdin, dw&~(ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT));
		FlushConsoleInputBuffer(hstdin);
	}
	else {
		setvbuf(stdin, NULL, _IONBF, 0);
		setvbuf(stdout, NULL, _IONBF, 0);
	}

	return 0;
}

int Communicate::input() {

	unsigned long dw = 0;

	if (inputmethod == 0) return 1;

	//if (stdin->_cnt > 0) return 1; //Standartinput ?????? ausgeschalten...

	if (pipe) {
		if (!PeekNamedPipe(hstdin, 0, 0, 0, &dw, 0)) return 1;
		return dw;
	}
	else {
		GetNumberOfConsoleInputEvents(hstdin, &dw);
		if (dw > 1) inputmethod = 0;
	}

	return 0;
}

bool Communicate::send(std::string command) {
	std::cout << command << "\r\n";
	//printf("%s\r\n", command);
	return true;// go
}

int Communicate::sendmove(char move1[6]) {

	char command[20];
	switch (inputmethod) {
	case 2: strcpy(command, "move "); break;
	case 1: strcpy(command, "bestmove "); break;
	default: {strcpy(command, "my move: "); break; // this->mymove->movePieces(move1); break;
	}
	}
	strcat(command, move1);
	send(command);

	return 0;
}

int Communicate::sendpondermove(char move1[6], char move2[6]) {

	char command[20];
	switch (inputmethod) {
	case 2: strcpy(command, "move "); break;
	case 1: strcpy(command, "bestmove "); break;
	default: {strcpy(command, "my move"); this->mymove->movePieces(move1); break; }
	}
	strcat(command, move1);
	strcat(command, " ponder ");
	strcat(command, move2);
	send(command);

	return 0;
}

/** @brief (one liner)
*
* (documentation goes here)
*/
bool Communicate::setMode(int mode)
{
	this->inputmethod = mode;
	return true;
}

int Communicate::sendmoves(char move1[6], char move2[6])
{
	if (ponder)
	{
		this->sendpondermove(move1, move2);
	}
	else
	{
		this->sendmove(move1);
	}
	return true;
}

bool Communicate::setMovement(Movement *mymove)
{
	this->mymove = mymove;
	return true;
}

void Communicate::setPonder()
{
	this->ponder = true;
}
