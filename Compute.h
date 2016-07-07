#pragma once
#include <ctime>
// *** END ***
// *** ADDED BY HEADER FIXUP ***
#include <istream>
#include <string>
// *** END ***
#pragma once
#include "Board.h"
#include "Pieces.h"
#include "Movement.h"
#include "Evaluation.h"
//#include "calculus.h"
#include "Communicate.h"
#include "Zuege.h"
#include "Notation.h"
#include "Unit1.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <time.h>

#define NAKED 0
#define UCI 1
#define XBOARD 2
#define STARTFEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0"
#define WHITE 0
#define BLACK 1
#define VERSION_STRING "1.1"
#define COMPILE_STRING " compiled 23.03.2016"

class Compute
{
public:
	Compute();
	~Compute();
	void init();
	bool start();
private:
	Communicate *mycomp;
	bool end;
	void readInput();
	std::string  command;
	bool uci(std::string command);
	bool xboard(std::string  command);
	bool naked(std::string  command);
	bool setSearchmoves(std::string command);
	CalculusTopTh *mycalc;
	Movement *mymoves;
	Notation *mynot;
	int mode;
	int myside;
	int ismove(char * command);
	void displayBoard();
	void printSearchHeader();
	void printStats();
	void printHelp();
	void printWelcome();
	char starUpCalc();
	clock_t movetime;
	Zuege *myzug;
	bool searchmvs;
	void loadFromFen(std::string pos);
};

