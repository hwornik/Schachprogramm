#pragma once
#include <stdio.h>
#include "Board.h"
#include "Pieces.h"
#include "Movement.h"
#include <iostream>
class Evaluation
{
public:
	Evaluation();
	~Evaluation();
	Board *possibleMoves(Board *myboard);
	int possibleMovesFigure();
	int possibleFields();
	int possibleHits();
	bool printStats();
	int getMovesFigures();
	bool makeNextMovesfigure();
	bool makeThisMovesfigure(Board *myboard, int vx, int vy, int nx, int ny);
	int computeMovesfigure(int vx, int vy, Board *myboard);
	int getZuege();
	int getHits();
	char *getZugStr();
	int figurenBewertung(Movement * moving);
	int getKontrolFields();
	int getFigurenwert();
	int getZug(bool xwert);
	int getZugNr();
	Zuege getAktZueg();
	int getZug(bool von,bool xwert);
	bool isPosunderAttack(Board *myboard,int posx,int posy, bool whitetomove);
	Pieces **whichFigureAttacks(Board *myboard,int posx,int posy, bool whitetomove);
private:
	bool noticeMovesandHits(char pie, Movement * moving, int vx, int vy);
	bool compMovesandHits(bool searchhits, char pie, Movement *moving, int vx, int vy, Board *moveboard);
	bool nightTest(bool searchhits, char pie, bool notfoundfigure, bool ishit, int vx, int vy, int nx, int ny, Board * moveboard);
	int countXFields(Board *hitboard, bool whitetomove);
	int movesFigure;
	int movesFields;
	int hits;
	int moveperFigure[36][2];
	int zahlermoves;
	int movenr;
	char notat[8];
	Movement *moving;
	int kontrolleF;
	int bewertung;
	bool trade;
	char tradefig;
	int compzugnr;
	Board *hitboard;
	Board *hitmvboard;
	Board *moveboard;
	Pieces *pie;
};

