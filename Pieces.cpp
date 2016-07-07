#include "stdafx.h"
#include "Pieces.h"


Pieces::Pieces()
{
	this->actmoves = new Board();
}


Pieces::~Pieces()
{
	delete this->actmoves;
}

void Pieces::init()
{
	name = ' ';
	wert = 0;
	this->actmoves->init();
	moves=0;
	hits=0;
	bool isalive=false;
	actpos[0]=0;
	actpos[1] = 0;
}

bool Pieces::setName(char name)
{
	this->name = name;
	if (name == 'p' || name == 'P')
		wert = 1;
	else if (name == 'r' || name == 'R')
		wert = 5;
	else if (name == 'n' || name == 'N')
		wert = 3;
	else if (name == 'b' || name == 'B')
		wert = 3;
	else if (name == 'q' || name == 'Q')
		wert = 9;
	else if (name == 'k' || name == 'K')
		wert = 250;
	else
		wert = 0;
	return true;
}

char Pieces::getName()
{
	return this->name;
}

bool Pieces::setPos(int x, int y)
{
	actpos[0] = x;
	actpos[1] = y;
	if (this->getMoves(x, y))
		return true;
	else
		return false;
}

int Pieces::getPos(bool xwert)
{
	if(xwert)
		return actpos[0];
	else
    	return actpos[1];
}

bool Pieces::getMoves(int nx, int ny)
{
	// Pawn Regeln !!!!!
	if (this->name == 'P')
	{
		this->actmoves->setPiece('m', nx, ny + 1);
		if (nx>1)
			this->actmoves->setPiece('h', nx - 1, ny + 1);
		if (nx<8)
			this->actmoves->setPiece('h', nx + 1, ny + 1);
		if (ny == 2)
		{
			this->actmoves->setPiece('m', nx, ny + 2);
		}
	}
	if (this->name == 'p')
	{

		this->actmoves->setPiece('m', nx, ny - 1);
		if (nx>1)
			this->actmoves->setPiece('h', nx - 1, ny - 1);
		if (nx<8)
			this->actmoves->setPiece('h', nx + 1, ny - 1);
		if (ny == 7)
		{
			this->actmoves->setPiece('m', nx, ny - 2);
		}
	}
	if (this->name == 'b' || this->name == 'B' || this->name == 'q' || this->name == 'Q')
	{
		for (int i = 1; i < 8; i++)
		{
			if (((nx + i)<9) && ((ny + i)<9))
				this->actmoves->setPiece('x', nx + i, ny + i);
			if (((nx - i)>0) && ((ny - i)>0))
				this->actmoves->setPiece('x', nx - i, ny - i);
			if (((nx - i)>0) && ((ny + i)<9))
				this->actmoves->setPiece('x', nx - i, ny + i);
			if (((nx + i)<9) && ((ny - i)>0))
				this->actmoves->setPiece('x', nx + i, ny - i);

		}
	}
	if (this->name == 'r' || this->name == 'R' || this->name == 'q' || this->name == 'Q')
	{
		for (int i = 1; i < 8; i++)
		{
			if ((ny + i)<9)
				this->actmoves->setPiece('x', nx, ny + i);
			if ((ny - i)>0)
				this->actmoves->setPiece('x', nx, ny - i);
			if ((nx - i)>0)
				this->actmoves->setPiece('x', nx - i, ny);
			if ((nx + i)<9)
				this->actmoves->setPiece('x', nx + i, ny);
		}
	}
	if (this->name == 'k' || this->name == 'K')
	{
		if ((ny + 1)<9)
			this->actmoves->setPiece('x', nx, ny + 1);
		if ((ny - 1)>0)
			this->actmoves->setPiece('x', nx, ny - 1);
		if ((nx - 1)>0)
			this->actmoves->setPiece('x', nx - 1, ny);
		if ((nx + 1)<9)
			this->actmoves->setPiece('x', nx + 1, ny);
		if (((nx + 1)<9) && ((ny + 1)<9))
			this->actmoves->setPiece('x', nx + 1, ny + 1);
		if (((nx - 1)>0) && ((ny - 1)>0))
			this->actmoves->setPiece('x', nx - 1, ny - 1);
		if (((nx - 1)>0) && ((ny + 1)<9))
			this->actmoves->setPiece('x', nx - 1, ny + 1);
		if (((nx + 1)<9) && ((ny - 1)>0))
			this->actmoves->setPiece('x', nx + 1, ny - 1);
	}
	if (this->name == 'n' || this->name == 'N')
	{
		if (((nx + 2)<9) && ((ny + 1)<9))
			this->actmoves->setPiece('x', nx + 2, ny + 1);
		if (((nx + 2)<9) && ((ny - 1)>0))
			this->actmoves->setPiece('x', nx + 2, ny - 1);
		if (((nx - 2)>0) && ((ny + 1)<9))
			this->actmoves->setPiece('x', nx - 2, ny + 1);
		if (((nx - 2)>0) && ((ny - 1)>0))
			this->actmoves->setPiece('x', nx - 2, ny - 1);
		if (((nx + 1)<9) && ((ny + 2)<9))
			this->actmoves->setPiece('x', nx + 1, ny + 2);
		if (((nx - 1)>0) && ((ny + 2)<9))
			this->actmoves->setPiece('x', nx - 1, ny + 2);
		if (((nx - 1)>0) && ((ny - 2)>0))
			this->actmoves->setPiece('x', nx - 1, ny - 2);
		if (((nx + 1)<9) && ((ny - 2)>0))
			this->actmoves->setPiece('x', nx + 1, ny - 2);
	}
	return true;
}


Board * Pieces::getActMoves()
{
	return this->actmoves;
}

int Pieces::getWert()
{
	return this->wert;
}

