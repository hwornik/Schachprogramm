#pragma once
#include <string>

#pragma once
#include "Board.h"
#include "Pieces.h"
#include "Zuege.h"
#include "Notation.h"
#include <stdio.h>
#include <string.h>

class Movement
{
public:
	Movement();
	~Movement();
	bool movePiece(std::string command);
	bool movePieces(std::string command);
	bool moveisHit();
	bool proofNextMove(bool searchhits, int vx, int vy, int nx, int ny, char p);
	bool proofRochade(int vx, int vy, int nx, int ny);
	int figureisunderAttack(int vx, int vy, bool whitetomove);
	bool loadFromFen(std::string pos);
	char getPieceonPos(int abc, int zahl);
	bool getWhitehasMove();
	bool setBoard(Board *mynewBoard);
	Board *copyBoard();
	char setPiece(char pie, int vx, int vy);
	int getZugNr();
	void printZuege();
	void init();
private:
	bool makenextMove(int vx, int vy, int nx, int ny, char p);
	Pieces *mypieces;
	Board *myboard;
	Zuege *myzuege;
	Zuege *aktuell;
	//Board *attacks;
	Notation *mynot;
	bool hit;
	char hitpiece;
};

