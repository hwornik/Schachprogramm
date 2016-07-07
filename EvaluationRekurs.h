#pragma once
#include "Board.h"
#include "Movement.h"
#include "Pieces.h"


class EvaluationRekurs
{
public:
	EvaluationRekurs();
	~EvaluationRekurs();
	int computeMovesfigure(int vx, int vy, Board *myboard);
	bool makeNextMovesfigure();
	int getZug(bool xwert);
	Board *possibleMoves(Board *myboard);
	int getFigurenwert();
private:
	Movement *moving;
	int movesFigure;
	int movesFields;
	int hits;
	int movenr;
	int bewertung;
	bool trade;
	char tradefig;
	int moveperFigure[36][2];
	int zahlermoves;
	bool noticeMovesandHits(char pie, Movement * moving, int vx, int vy);
	bool compMovesandHits(bool searchhits, char pie, Movement *moving, int vx, int vy, Board *moveboard);
	bool nightTest(bool searchhits, char pie, bool notfoundfigure, bool ishit, int vx, int vy, int nx, int ny, Board * moveboard);
	Pieces *pie;
	int figurenBewertung(Movement * moving);
	Board *moveboard;
};

