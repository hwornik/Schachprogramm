#include "stdafx.h"
#include "Board.h"


Board::Board()
{
	this->init();
}

void Board::init()
{
	bewertung = 0;
	castleKs[0] = 1;
	castleKs[1] = 1;
	castleQs[0] = 1;
	castleQs[1] = 1;
	zugnr = 0;
	halbzug = 1;
	wieder = 0;
	whiteKing[0] = 0;
	whiteKing[1] = 0;
	blackKing[0] = 0;
	blackKing[1] = 0;
	remie[0] = false;
	remie[1] = false;
	for (int i = 7; i >= 0; i--)
	{
		for (int j = 0; j < 8; j++)
		{
			this->chessboard[j][i] = 'e';
		}
	}
	isenpassant = false;
}


Board::~Board()
{
}


int Board::loadFromFen(char pos[100])
{
	int z = 0;
	for (int i = 7; i >= 0; i--)
	{
		for (int j = 0; j < 8; j++)
		{
			if (pos[z] == '/')
			{
				j--;
			}
			else if (pos[z] == '1')
			{
				this->chessboard[j][i] = 'e';
			}
			else if (pos[z] == '2')
			{
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
			}
			else if (pos[z] == '3')
			{
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
			}
			else if (pos[z] == '4')
			{
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
			}
			else if (pos[z] == '5')
			{
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
			}
			else if (pos[z] == '6')
			{
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
			}
			else if (pos[z] == '7')
			{
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
			}
			else if (pos[z] == '8')
			{
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
				j++;
				this->chessboard[j][i] = 'e';
			}
			else
			{
				this->chessboard[j][i] = pos[z];
			}
			z++;
		}
	}
	z++;
	if (pos[z] == 'w')
	{
		this->whitetoMove = 1;
	}
	else
	{
		this->whitetoMove = 0;
	}
	z++;
	z++;
	if (pos[z] == 'K')
	{
		this->castleKs[0] = 1;
		z++;
	}
	else
	{
		this->castleKs[0] = 0;
	}
	if (pos[z] == 'Q')
	{
		this->castleQs[0] = 1;
		z++;
	}
	else
	{
		this->castleQs[0] = 0;
	}
	if (pos[z] == 'k')
	{
		this->castleKs[1] = 1;
		z++;
	}
	else
	{
		this->castleKs[1] = 0;
	}
	if (pos[z] == 'q')
	{
		this->castleQs[1] = 1;
		z++;
	}
	else
	{
		this->castleQs[1] = 0;
	}
	z++;
	if (pos[z] == '-')
	{
		this->enpassant[0] = 0;
		this->enpassant[1] = 0;
	}
	else
	{
		this->enpassant[0] = pos[z];
		z++;
		this->enpassant[0] = pos[z];
	}
	while (!isdigit(pos[z]))
		z++;
	this->halbzug = pos[z] - 48;
	z++;
	while (isdigit(pos[z]))
	{
		this->halbzug = (pos[z] - 48) * 10;
		z++;
	}
	while (!isdigit(pos[z]))
		z++;
	this->zugnr = pos[z] - 48;
	z++;
	while (isdigit(pos[z]))
	{
		this->zugnr = (pos[z] - 48) * 10;
		z++;
	}
	this->searchKings();
	return 0;
}

bool Board::makeMove(int vx, int vy, int nx, int ny)
{
	bool hit = false;
	if (chessboard[nx - 1][ny - 1] != 'e')
	{
		hit = true;
	}
	int col = 1;
	if (this->whitetoMove)
		col = 0;
	if (zugnr < 6)
	{
		wiederholung[zugnr - 1][col][0] = vx * 10 + vy;
		wiederholung[zugnr - 1][col][1] = nx * 10 + ny;

	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			wiederholung[i][col][0] = wiederholung[i + 1][col][0];
			wiederholung[i][col][1] = wiederholung[i + 1][col][0];
		}
		wiederholung[5][col][0] = vx * 10 + vy;
		wiederholung[5][col][1] = nx * 10 + ny;
	}
	int rem = 0;
	if (this->zugnr > 4)
	{
		for (int i = 0; i < 3; i++)
		{
			if (wiederholung[i][col][0] == wiederholung[i + 2][col][0] &&
				wiederholung[i][col][1] == wiederholung[i + 2][col][0] &&
				wiederholung[i + 1][col][0] == wiederholung[i + 3][col][0] &&
				wiederholung[i + 1][col][1] == wiederholung[i + 3][col][0])
			{
				rem++;
			}
		}
		if (rem == 3)
		{
			remie[col] = true;
		}
	}
	if (this->getwhitetoMove() && (this->castleKs[0] || this->castleQs[0]))
	{
		if (chessboard[vx - 1][vy - 1] == 'R' && vx == 1)
		{
			this->castleQs[0] = 0;
		}
		if (chessboard[vx - 1][vy - 1] == 'R' && vx == 8)
		{
			this->castleKs[0] = 0;
		}
		if (chessboard[vx - 1][vy - 1] == 'K')
		{
			this->castleQs[0] = 0;
			this->castleKs[0] = 0;
		}
	}
	else if (!this->getwhitetoMove() && (this->castleKs[1] || this->castleQs[1]))
	{
		if (chessboard[vx - 1][vy - 1] == 'r' && vx == 1)
		{
			this->castleQs[1] = 0;
		}
		if (chessboard[vx - 1][vy - 1] == 'r' && vx == 8)
		{
			this->castleKs[1] = 0;
		}
		if (chessboard[vx - 1][vy - 1] == 'k')
		{
			this->castleQs[1] = 0;
			this->castleKs[1] = 0;
		}
	}
	char fig = chessboard[vx - 1][vy - 1];
	if (fig == 'K')
	{
		this->whiteKing[0] = nx;
		this->whiteKing[1] = ny;
	}
	if (fig == 'k')
	{
		this->blackKing[0] = nx;
		this->blackKing[1] = ny;
	}
	chessboard[nx - 1][ny - 1] = fig;
	chessboard[vx - 1][vy - 1] = 'e';
	int ix = 0;
	if (this->whitetoMove)
		ix = 1;
	this->enpassant[ix] = 0;
	this->whitetoMove = !this->whitetoMove;
	this->boardString();
	if (!this->whitetoMove)
	{
		this->halbzug++;
		if (chessboard[nx - 1][ny - 1] == 'P' || chessboard[nx - 1][ny - 1] == 'p' || hit)
			this->halbzug = 0;
		this->zugnr++;
	}
	return 1;

}


char * Board::toString()
{
	return fenstring;
}

char Board::getPieceonPos(int abc, int zahl)
{
	return this->chessboard[abc - 1][zahl - 1];
}

bool Board::getwhitetoMove()
{
	return this->whitetoMove;
}

bool Board::setwhitetoMove(bool white)
{
	this->whitetoMove = white;
	return this->whitetoMove;
}

bool Board::getcastleKs(int col)
{
	return this->castleKs[col];
}

bool Board::getcastleQs(int col)
{
	return this->castleQs[col];
}

bool Board::setcastleKs(int col, bool castle)
{
	this->castleKs[col] = castle;
	return this->castleKs[col];
}

bool Board::setcastleQs(int col, bool castle)
{
	this->castleQs[col] = castle;
	return this->castleQs[col];
}

int Board::getHalbzug()
{
	return this->halbzug;
}

bool Board::setHalbzug(int zug)
{
	this->halbzug = zug;
	return 0;
}

int Board::getZugNr()
{
	return this->zugnr;
}

bool Board::setZugNr(int zug)
{
	this->zugnr = zug;
	return false;
}

bool Board::setPiece(char p, int nx, int ny)
{

	chessboard[nx - 1][ny - 1] = p;
	this->toString();
	return true;
}
bool Board::setPieceTrade(char p, int nx, int ny)
{
	if (chessboard[nx - 1][ny - 1] == 'p' || chessboard[nx - 1][ny - 1] == 'P')
	{
		if (p == 'q' || p == 'Q')
		{
			if (this->whitetoMove)
			{
				p = 'q';
			}
			else
			{
				p = 'Q';
			}
		}
		if (p == 'r' || p == 'R')
		{
			if (this->whitetoMove)
			{
				p = 'r';
			}
			else
			{
				p = 'R';
			}
		}
		if (p == 'b' || p == 'B')
		{
			if (this->whitetoMove)
			{
				p = 'b';
			}
			else
			{
				p = 'B';
			}
		}
		if (p == 'n' || p == 'N')
		{
			if (this->whitetoMove)
			{
				p = 'n';
			}
			else
			{
				p = 'N';
			}
		}
		chessboard[nx - 1][ny - 1] = p;
		this->toString();
		return true;
	}
	else
		return false;
}

bool Board::setEnPassant(int ny, bool xwert)
{
	int i = 1;
	if (xwert)
		i = 0;
	this->enpassant[i] = ny;
	return true;
}
bool Board::setEnPassantFalse()
{
	isenpassant = false;
	return true;
}
bool Board::getEnPassant()
{
	return isenpassant;
}

char Board::maketestmove(int vx, int vy, int nx, int ny)
{
	char old;
	old = chessboard[nx - 1][ny - 1];
	chessboard[nx - 1][ny - 1] = chessboard[vx - 1][vy - 1];
	chessboard[vx - 1][vy - 1] = 'e';
	return old;
}

bool Board::takebacktestmove(int vx, int vy, int nx, int ny, char old)
{
	chessboard[vx - 1][vy - 1] = chessboard[nx - 1][ny - 1];
	chessboard[nx - 1][ny - 1] = old;
	return false;
}

int Board::getWhiteKingPos(bool xpos)
{
	if (xpos)
		return whiteKing[0];
	else
		return whiteKing[1];
}

int Board::getBlackKingPos(bool xpos)
{
	if (xpos)
		return blackKing[0];
	else
		return blackKing[1];
}

bool Board::setWhiteKingPos(int wert, bool xpos)
{
	int ix = 1;
	if (xpos)
		ix = 0;
	this->whiteKing[ix] = wert;
	return 0;
}

bool Board::setBlackKingPos(int wert, bool xpos)
{
	int ix = 1;
	if (xpos)
		ix = 0;
	this->blackKing[ix] = wert;
	return 0;
}

bool Board::makeRochade(Board * myboard, int vx, int vy, int nx, int ny)
{
	int col = 1;
	if (this->whitetoMove)
		col = 0;
	if (zugnr < 6)
	{
		wiederholung[zugnr - 1][col][0] = -1;
		wiederholung[zugnr - 1][col][1] = vx * 10 + nx;

	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			wiederholung[i][col][0] = wiederholung[i + 1][col][0];
			wiederholung[i][col][1] = wiederholung[i + 1][col][0];
		}
		wiederholung[5][col][0] = vx * 10 + vy;
		wiederholung[5][col][1] = nx * 10 + ny;
	}
	char fig = chessboard[vx - 1][vy - 1];
	if (fig == 'K')
	{
		this->whiteKing[0] = nx;
		this->whiteKing[1] = ny;
	}
	if (fig == 'k')
	{
		this->blackKing[0] = nx;
		this->blackKing[1] = ny;
	}
	chessboard[nx - 1][ny - 1] = fig;
	chessboard[vx - 1][vy - 1] = 'e';
	if (nx == 3)
	{
		chessboard[3][ny - 1] = chessboard[0][vy - 1];
		chessboard[0][vy - 1] = 'e';
	}
	if (nx == 7)
	{
		chessboard[5][ny - 1] = chessboard[7][vy - 1];
		chessboard[7][vy - 1] = 'e';
	}
	if (this->whitetoMove)
	{
		this->castleKs[0] = 0;
		this->castleQs[0] = 0;
		this->whiteKing[0] = nx;
		this->whiteKing[1] = ny;

	}
	else
	{
		this->castleKs[0] = 0;
		this->castleQs[0] = 0;
		this->blackKing[0] = nx;
		this->blackKing[1] = ny;
	}
	this->whitetoMove = !this->whitetoMove;
	return true;
}

int Board::getFigurenwert()
{
	return this->figurenwert;
}

bool Board::setBewertung(int bewert)
{
	this->bewertung = bewert;
	return 0;
}

int Board::getBewertung()
{
	return this->bewertung;
}

bool Board::setFigurenwert(int wert)
{
	this->figurenwert = wert;
	return true;
}

bool Board::setWiederHol(int wert, int a, int b, int c)
{
	this->wiederholung[a][b][c] = wert;
	return false;
}

int Board::getWiederHol(int a, int b, int c)
{
	return this->wiederholung[a][b][c];

}

int Board::getWiederCount()
{
	return this->wieder;
}

bool Board::setWiederCount(int wert)
{
	this->wieder = wert;
	return false;
}

bool Board::setRemie(bool rem, bool white)
{
	int ix = 1;
	if (white)
		ix = 0;
	this->remie[ix] = rem;
	return false;
}

bool Board::getRemie(bool white)
{
	int ix = 1;
	if (white)
		ix = 0;
	return this->remie[ix];
}



void Board::boardString()
{
	for (register int i = 0; i < 85; i++)
	{
		fenstring[i] = ' ';
	}
	fenstring[84] = '\0';
	int z = 0;
	int leer;
	for (int i = 7; i >= 0; i--)
	{
		leer = 0;
		for (int j = 0; j < 8; j++)
		{
			if (this->chessboard[j][i] == 'e')
			{
				leer++;
			}
			else
			{
				if (leer > 0)
				{
					fenstring[z] = (char)leer + 48;
					leer = 0;
					z++;
				}
				fenstring[z] = this->chessboard[j][i];
				z++;
			}
		}
		if (leer > 0)
		{
			fenstring[z] = (char)leer + 48;
			leer = 0;
			z++;
		}
		if (i >0)
		{
			fenstring[z] = '/';
			z++;
		}
	}
	fenstring[z] = ' ';
	z++;
	if (this->whitetoMove)
	{
		fenstring[z] = 'w';
	}
	else
	{
		fenstring[z] = 'b';
	}
	//Für richtigen FenString notwendig
	z++;
	fenstring[z] = ' ';
	z++;
	if (chessboard[4][0] == 'K')
	{
		if (this->castleKs[0])
		{
			fenstring[z] = 'K';
			z++;
		}
		if (this->castleQs[0])
		{
			fenstring[z] = 'Q';
			z++;
		}
	}
	if (chessboard[4][7] == 'k')
	{
		if (this->castleKs[1])
		{
			fenstring[z] = 'k';
			z++;
		}
		if (this->castleQs[1])
		{
			fenstring[z] = 'q';
			z++;
		}
	}
	fenstring[z] = ' ';
	z++;
	int i = 0;
	if (this->whitetoMove)
		i = 1;
	if (this->enpassant[i] == 0)
	{
		fenstring[z] = '-';
	}
	else
	{
		if (this->enpassant[i] == 1)
			fenstring[z] = 'a';
		if (this->enpassant[i] == 2)
			fenstring[z] = 'b';
		if (this->enpassant[i] == 3)
			fenstring[z] = 'c';
		if (this->enpassant[i] == 4)
			fenstring[z] = 'd';
		if (this->enpassant[i] == 5)
			fenstring[z] = 'e';
		if (this->enpassant[i] == 6)
			fenstring[z] = 'f';
		if (this->enpassant[i] == 7)
			fenstring[z] = 'g';
		if (this->enpassant[i] == 8)
			fenstring[z] = 'h';
		z++;
		if (!this->whitetoMove)
		{
			fenstring[z] = '3';
		}
		else
		{
			fenstring[z] = '6';
		}
	}
	/*
	z++;
	fenstring[z] = ' ';
	z++;
	fenstring[z] = this->halbzug;
	z++;
	fenstring[z] = ' ';
	z++;
	fenstring[z] = this->zugnr;
	*/
}

bool Board::searchKings()
{

	bool black = true, white = true;
	for (register int i = 1; i < 9; i++)
	{
		for (register int j = 1; j < 9; j++)
		{
			if (black && chessboard[i - 1][j - 1] == 'k')
			{
				blackKing[0] = i;
				blackKing[1] = j;
				black = false;
			}
			if (white && chessboard[i - 1][j - 1] == 'K')
			{
				whiteKing[0] = i;
				whiteKing[1] = j;
				white = false;
			}
		}
	}
	if (!white && !black)
		return true;
	else
		return false;
}

int Board::getEnPassantField(bool xwert)
{
	isenpassant = true;
	int i = 1;
	if (xwert)
		i = 0;
	return this->enpassant[i];
}

Board *Board::copyBoard()
{
	Board *newboard = new Board();
	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			newboard->setPiece(this->getPieceonPos(i, j), i, j);
		}
	}
	newboard->setBewertung(this->getBewertung());
	newboard->setFigurenwert(this->getFigurenwert());
	newboard->setcastleQs(0, this->getcastleQs(0));
	newboard->setcastleQs(1, this->getcastleQs(1));
	newboard->setcastleKs(0, this->getcastleKs(0));
	newboard->setcastleKs(1, this->getcastleKs(1));
	newboard->setwhitetoMove(this->getwhitetoMove());
	newboard->setEnPassant(this->getEnPassantField(true), true);
	newboard->setEnPassant(this->getEnPassantField(false), false);
	newboard->setZugNr(this->getZugNr());
	newboard->setHalbzug(this->getHalbzug());
	for (int i = 0; i < 6; i++)
	{
		newboard->setWiederHol(this->getWiederHol(i, 0, 0), i, 0, 0);
		newboard->setWiederHol(this->getWiederHol(i, 0, 1), i, 0, 1);
		newboard->setWiederHol(this->getWiederHol(i, 1, 0), i, 1, 0);
		newboard->setWiederHol(this->getWiederHol(i, 1, 1), i, 1, 1);
	}
	newboard->setWiederCount(this->getWiederCount());
	newboard->setWhiteKingPos(this->getWhiteKingPos(true), true);
	newboard->setWhiteKingPos(this->getWhiteKingPos(false), false);
	newboard->setBlackKingPos(this->getBlackKingPos(true), true);
	newboard->setBlackKingPos(this->getBlackKingPos(false), false);
	newboard->setRemie(this->getRemie(true), true);
	newboard->setRemie(this->getRemie(true), true);
	return newboard;
}