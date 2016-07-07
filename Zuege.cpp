#include "stdafx.h"
#include "Zuege.h"


Zuege::Zuege()
{
	this->init();
}

void Zuege::init()
{
	zugnr = 0;
	for (int i = 0; i<5; i++)
	{
		whitemove[i] = ' ';
		blackmove[i] = ' ';
	}
	blvx = 0;
	blvy = 0;
	blnx = 0;
	blny = 0;
	whvx = 0;
	whvy = 0;
	whnx = 0;
	whny = 0;
	bltr = 0;
	whtr = 0;
	whitetrade = false;
	blacktrade = false;
	this->next = 0;

}

Zuege::~Zuege()
{
}

int Zuege::getZugNr()
{
	return zugnr;
}

void Zuege::setZugNr(int zug)
{
	this->zugnr = zug;
}

int Zuege::getWhitePiece(bool from, bool xwert)
{
	if (from)
	{
		if (xwert)
		{
			return whvx;
		}
		else
		{
			return whvy;
		}
	}
	else
	{
		if (xwert)
		{
			return whnx;
		}
		else
		{
			return whny;
		}
	}
}

bool Zuege::setWhitePiece(int vx, int vy, int nx, int ny)
{
	if (vx > 0 && vy > 0 && nx > 0 && ny > 0 && vx < 9 && vy < 9 && nx < 9 && ny < 9)
	{
		this->whvx = vx;
		this->whvy = vy;
		this->whnx = nx;
		this->whny = ny;
		return true;
	}
	else
	{
		return false;
	}
}
int Zuege::getBlackPiece(bool from, bool xwert)
{
	if (from)
	{
		if (xwert)
		{
			return blvx;
		}
		else
		{
			return blvy;
		}
	}
	else
	{
		if (xwert)
		{
			return blnx;
		}
		else
		{
			return blny;
		}
	}
}

bool Zuege::setBlackPiece(int vx, int vy, int nx, int ny)
{
	if (vx > 0 && vy > 0 && nx > 0 && ny > 0 && vx < 9 && vy < 9 && nx < 9 && ny < 9)
	{
		this->blvx = vx;
		this->blvy = vy;
		this->blnx = nx;
		this->blny = nx;
		return true;
	}
	else
	{
		return false;
	}
}
char Zuege::getWhiteTrade()
{
	return figure[1][whtr];
}

char Zuege::getBlackTrade()
{
	return figure[1][bltr];
}

bool Zuege::setWhitePiece(char movenot[5])
{
	return this->convert(movenot, true);
}

bool Zuege::setBlackPiece(char movenot[5])
{
	return this->convert(movenot, false);
}

char* Zuege::getWhiteMove()
{
	char* zug = new char[5];
	zug[0] = row[whvx - 1];
	zug[1] = whvy + 48;
	zug[2] = row[whnx - 1];
	zug[3] = whny + 48;
    zug[4]='\0';
	if (this->whitetrade)
	{
		zug[4] = figure[0][this->whtr];
		zug[5]='\0';
	}
	return zug;
}

char* Zuege::getBlackMove()
{
	char* zug = new char[5];
	zug[0] = row[blvx - 1];
	zug[1] = blvy + 48;
	zug[2] = row[blnx - 1];
	zug[3] = blny + 48;
    zug[4]='\0';
	if (this->blacktrade)
	{
		zug[4] = figure[1][this->bltr];
		zug[5]='\0';
	}
	return zug;
}
bool Zuege::convert(char movenot[5], bool white)
{
	if (white)
	{
		whitetrade = false;
	}
	else
	{
		blacktrade = false;
	}
	int z, vx, vy, nx, ny;
	z = 0;
	vx = 0;
	vy = 0;
	nx = 0;
	ny = 0;
	//printf("Z: %d Char: %c\n",z,movenot[z]);
	if (movenot[z] == 'a')
	{
		vx = 1;
	}
	else if (movenot[z] == 'b')
	{
		vx = 2;
	}
	else if (movenot[z] == 'c')
	{
		vx = 3;
	}
	else if (movenot[z] == 'd')
	{
		vx = 4;
	}
	else if (movenot[z] == 'e')
	{
		vx = 5;
	}
	else if (movenot[z] == 'f')
	{
		vx = 6;
	}
	else if (movenot[z] == 'g')
	{
		vx = 7;
	}
	else if (movenot[z] == 'h')
	{
		vx = 8;
	}
	else
	{
		return false;
	}
	z++;
	if (movenot[z] == '1')
	{
		vy = 1;
	}
	else if (movenot[z] == '2')
	{
		vy = 2;
	}
	else if (movenot[z] == '3')
	{
		vy = 3;
	}
	else if (movenot[z] == '4')
	{
		vy = 4;
	}
	else if (movenot[z] == '5')
	{
		vy = 5;
	}
	else if (movenot[z] == '6')
	{
		vy = 6;
	}
	else if (movenot[z] == '7')
	{
		vy = 7;
	}
	else if (movenot[z] == '8')
	{
		vy = 8;
	}
	else
	{
		return false;
	}
	z++;
	// to Move
	if (movenot[z] == 'a')
	{
		nx = 1;
	}
	else if (movenot[z] == 'b')
	{
		nx = 2;
	}
	else if (movenot[z] == 'c')
	{
		nx = 3;
	}
	else if (movenot[z] == 'd')
	{
		nx = 4;
	}
	else if (movenot[z] == 'e')
	{
		nx = 5;
	}
	else if (movenot[z] == 'f')
	{
		nx = 6;
	}
	else if (movenot[z] == 'g')
	{
		nx = 7;
	}
	else if (movenot[z] == 'h')
	{
		nx = 8;
	}
	else
	{
		return false;
	}
	z++;
	if (movenot[z] == '1')
	{
		ny = 1;
	}
	else if (movenot[z] == '2')
	{
		ny = 2;
	}
	else if (movenot[z] == '3')
	{
		ny = 3;
	}
	else if (movenot[z] == '4')
	{
		ny = 4;
	}
	else if (movenot[z] == '5')
	{
		ny = 5;
	}
	else if (movenot[z] == '6')
	{
		ny = 6;
	}
	else if (movenot[z] == '7')
	{
		ny = 7;
	}
	else if (movenot[z] == '8')
	{
		ny = 8;
	}
	else
	{
		return false;
	}
	if (white)
	{
		whvx = vx;
		whvy = vy;
		whnx = nx;
		whny = ny;
	}
	else
	{
		blvx = vx;
		blvy = vy;
		blnx = nx;
		blny = ny;
	}
	z++;
	if (movenot[z] == 'Q' || movenot[z] == 'q' || movenot[z] == 'B' || movenot[z] == 'b' || movenot[z] == 'R' || movenot[z] == 'r' || movenot[z] == 'N' || movenot[z] == 'n')
	{
		if (white)
		{
			for (int i = 0; i<4; i++)
			{
				if (figure[0][i] == movenot[z])
				{
					whtr = i;
				}
			}

			whitetrade = true;
		}
		else
		{
			for (int i = 0; i<4; i++)
			{
				if (figure[1][i] == movenot[z])
				{
					bltr = i;
				}
			}
			blacktrade = true;
		}
	}
	return true;
}

bool Zuege::isWhiteTrade()
{
	return this->whitetrade;
}
bool Zuege::isBlackTrade()
{
	return this->blacktrade;
}

void Zuege::setWhiteTrade(char pie)
{
	this->whitetrade = true;
	int x = 0;
	for (int i = 0; i<4; i++)
	{
		if (pie == figure[0][i])
		{
			x = i;
			break;
		}
	}
	this->whtr = x;
}
void Zuege::setBlackTrade(char pie)
{
	this->blacktrade = true;
	int x = 0;
	for (int i = 0; i<4; i++)
	{
		if (pie == figure[1][i])
		{
			x = i;
			break;
		}
	}
	this->bltr = x;
}
