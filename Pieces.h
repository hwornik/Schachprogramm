#pragma once
#include "Board.h"
class Pieces
{
public:
	Pieces();
	~Pieces();
	void init();
	bool setName(char name);
	char getName();
	bool setPos(int x, int y);
    int getPos(bool xwert);
	Board *getActMoves();
	int getWert();
private:
	char name; //{ 'k','q','r','b','k','p','e'};
	int wert;
	int moves;
	int hits;
	Board *actmoves;
	bool isalive;
	int actpos[2];
	bool getMoves(int nx, int ny);
};

