#include "stdafx.h"
#include "Movement.h"


Movement::Movement()
{
	hit = false;
	this->myboard = new Board();
	this->mynot = new Notation();
	//this->attacks = new Board();
	this->mypieces = new Pieces();
	aktuell = new Zuege();
}


Movement::~Movement()
{
	delete myboard;
	delete mynot;
	delete aktuell;
	//delete attacks;
	delete mypieces;
	//delete mynot;
}

bool Movement::movePiece(std::string command)
{
	char *pch, *mystring;
	int lang = command.size();
	//command=command+" ";
	// lang =command.size();
	pch = strdup(command.c_str());

	bool enpassante = false;
	bool correct = false;
	int vx, vy, nx, ny;
	int z = 0, index = 0;
	bool istrade = false;
	char lsttrd;
	z = lang - 1;
	lsttrd = pch[z];
	if (pch[z] == 'Q' || pch[z] == 'q' || pch[z] == 'B' || pch[z] == 'b' || pch[z] == 'R' || pch[z] == 'r' || pch[z] == 'N' || pch[z] == 'n')
	{
		istrade = true;
		//printf("lasttrade");
	}
	z = 0;
	//while (lang>z)
	{
		while (z <= lang && pch[z] == ' ')
			z++;
		// if(pch[z]==' ')
		//    z++;
		//lang=sizeof(pch)/sizeof(char);
		// printf ("%d %c\n",lang,pch[z]);
		if (z>lang)
			return correct;
		vx = 0;
		vy = 0;
		nx = 0;
		ny = 0;
		//printf("Z: %d Char: %c\n",z,command[z]);
		if (pch[z] == 'a')
		{
			vx = 1;
		}
		else if (pch[z] == 'b')
		{
			vx = 2;
		}
		else if (pch[z] == 'c')
		{
			vx = 3;
		}
		else if (pch[z] == 'd')
		{
			vx = 4;
		}
		else if (pch[z] == 'e')
		{
			vx = 5;
		}
		else if (pch[z] == 'f')
		{
			vx = 6;
		}
		else if (pch[z] == 'g')
		{
			vx = 7;
		}
		else if (pch[z] == 'h')
		{
			vx = 8;
		}
		else
		{
			return correct;
		}
		z++;
		if (pch[z] == '1')
		{
			vy = 1;
		}
		else if (pch[z] == '2')
		{
			vy = 2;
		}
		else if (pch[z] == '3')
		{
			vy = 3;
		}
		else if (pch[z] == '4')
		{
			vy = 4;
		}
		else if (pch[z] == '5')
		{
			vy = 5;
		}
		else if (pch[z] == '6')
		{
			vy = 6;
		}
		else if (pch[z] == '7')
		{
			vy = 7;
		}
		else if (pch[z] == '8')
		{
			vy = 8;
		}
		else
		{
			return correct;
		}
		z++;
		// to Move
		if (pch[z] == 'a')
		{
			nx = 1;
		}
		else if (pch[z] == 'b')
		{
			nx = 2;
		}
		else if (pch[z] == 'c')
		{
			nx = 3;
		}
		else if (pch[z] == 'd')
		{
			nx = 4;
		}
		else if (pch[z] == 'e')
		{
			nx = 5;
		}
		else if (pch[z] == 'f')
		{
			nx = 6;
		}
		else if (pch[z] == 'g')
		{
			nx = 7;
		}
		else if (pch[z] == 'h')
		{
			nx = 8;
		}
		else
		{
			return correct;
		}
		z++;
		if (pch[z] == '1')
		{
			ny = 1;
		}
		else if (pch[z] == '2')
		{
			ny = 2;
		}
		else if (pch[z] == '3')
		{
			ny = 3;
		}
		else if (pch[z] == '4')
		{
			ny = 4;
		}
		else if (pch[z] == '5')
		{
			ny = 5;
		}
		else if (pch[z] == '6')
		{
			ny = 6;
		}
		else if (pch[z] == '7')
		{
			ny = 7;
		}
		else if (pch[z] == '8')
		{
			ny = 8;
		}
		else
		{
			return correct;
		}
		z++;
		if (vx > 0 && vy > 0 && nx > 0 && ny > 0 && vx < 9 && vy < 9 && nx < 9 && ny < 9)
		{
			//int lang=sizeof(command)/sizeof(char);
			enpassante = this->myboard->getEnPassant();
			char pawn;
			pawn = 'p';
			if (this->myboard->getwhitetoMove())
				pawn = 'P';
			if (enpassante)
			{
				this->myboard->setPiece(pawn, this->myboard->getEnPassantField(true), this->myboard->getEnPassantField(false));
			}
			//printf("%c |",pch[z]);
			if (z<lang)
			{
				//printf("trade z<lang \n");
				if (pch[z] == 'Q' || pch[z] == 'q' || pch[z] == 'B' || pch[z] == 'b' || pch[z] == 'R' || pch[z] == 'r' || pch[z] == 'N' || pch[z] == 'n')
				{
					//printf("trade\n");
					correct = this->proofNextMove(false, vx, vy, nx, ny, pch[z]);
					if (correct)
					{
						this->myboard->setEnPassantFalse();
						this->makenextMove(vx, vy, nx, ny, pch[z]);
					}
					z++;
				}
				else
				{
					correct = this->proofNextMove(false, vx, vy, nx, ny, ' ');
					if (correct)
					{
						this->myboard->setEnPassantFalse();
						this->makenextMove(vx, vy, nx, ny, ' ');
						//printf("makeit\n");
					}
				}
			}
			else
			{
				//printf("proof it %d\n",lang);
				if (istrade)
				{
					correct = this->proofNextMove(false, vx, vy, nx, ny, lsttrd);
				}
				else {
					correct = this->proofNextMove(false, vx, vy, nx, ny, ' ');
				}

				if (correct)
				{
					//printf("makeit\n");
					this->myboard->setEnPassantFalse();
					this->makenextMove(vx, vy, nx, ny, ' ');
					//printf("makeit\n");
				}

			}
		}
		if (enpassante)
		{
			this->myboard->setPiece('e', this->myboard->getEnPassantField(true), this->myboard->getEnPassantField(false));
			if (nx == this->myboard->getEnPassantField(true) && ny == this->myboard->getEnPassantField(false))
			{
				this->myboard->setPiece('e', this->myboard->getEnPassantField(true), this->myboard->getEnPassantField(false) + 1);
			}
		}
		vx = 0;
		vy = 0;
		nx = 0;
		ny = 0;
	}
	return correct;
}

bool Movement::movePieces(std::string command)
{
	char *pch, *mystring;
	char delimiter[] = " ";
	bool enpassante = false;
	bool correct = true;
	int vx, vy, nx, ny;
	int z = 0, index = 0;
	bool istrade = false;
	char lsttrd;
	mystring = strdup(command.c_str());
	pch = strtok(mystring, delimiter);
	while (pch != NULL)
	{
		char pawn;
		pawn = 'p';
		if (this->myboard->getwhitetoMove())
			pawn = 'P';
		if (enpassante)
		{
			this->myboard->setPiece(pawn, this->myboard->getEnPassantField(true), this->myboard->getEnPassantField(false));
		}
		aktuell->init();
		aktuell->setWhitePiece(pch);
		if (aktuell->isWhiteTrade())
		{
			this->myboard->setEnPassantFalse();
			this->makenextMove(aktuell->getWhitePiece(true, true), aktuell->getWhitePiece(true, false), aktuell->getWhitePiece(false, true), aktuell->getWhitePiece(false, false), aktuell->getWhiteTrade());
		}
		else
		{
			this->myboard->setEnPassantFalse();
			this->makenextMove(aktuell->getWhitePiece(true, true), aktuell->getWhitePiece(true, false), aktuell->getWhitePiece(false, true), aktuell->getWhitePiece(false, false), ' ');
		}
		if (enpassante)
		{
			this->myboard->setPiece('e', this->myboard->getEnPassantField(true), this->myboard->getEnPassantField(false));
			if (nx == this->myboard->getEnPassantField(true) && ny == this->myboard->getEnPassantField(false))
			{
				this->myboard->setPiece('e', this->myboard->getEnPassantField(true), this->myboard->getEnPassantField(false) + 1);
			}
		}
		vx = 0;
		vy = 0;
		nx = 0;
		ny = 0;
		pch = strtok(NULL, delimiter);
	}
	//delete pch;
	//delete aktuell;
	return correct;
}

bool Movement::moveisHit()
{
	return this->hit;
}


bool Movement::proofNextMove(bool searchhits, int vx, int vy, int nx, int ny, char p)
{
	//Pieces *mypieces;
	this->hit = false;
	char pie = myboard->getPieceonPos(vx, vy);
   	if (!myboard->getwhitetoMove())
	{
		if (isupper(pie))
			return false;
	}
	else
	{
		if (!isupper(pie))
			return false;
	}
	Board *piecmove;
	char zielpiece, myzielpiece;
	int divx = 0, divy = 0, posx, posy;
	this->hit = false;
	if (pie == 'e')
		return false;
	if (vx == nx && vy == ny)
		return false;
	//mypieces = new Pieces();
	mypieces->init();
	mypieces->setName(pie);
	mypieces->setPos(vx, vy);
	piecmove = mypieces->getActMoves();
	if (pie == 'k' || 'K')
	{
		if (vx == 5 && (nx == 7 || nx == 3) && ((ny == 1 && vy == 1) || (ny == 8 && vy == 8)))
		{
			bool tr= this->proofRochade(vx, vy, nx, ny);
			//delete piecmove;
			//delete mypieces;
			return tr;
		}
	}
	int x = 0, y = 0;
	if (pie != 'n' && pie != 'N')
	{
		if ((nx - vx) > 0)
		{
			x = 1;
		}
		else
		{
			x = -1;
		}
		if ((nx - vx) == 0)
			x = 0;
		if ((ny - vy) > 0)
		{
			y = 1;
		}
		else
		{
			y = -1;
		}
		if ((ny - vy) == 0)
			y = 0;
		posx = vx;
		posy = vy;
		while (posx != nx || posy != ny)
		{
			posx = posx + x;
			posy = posy + y;
			zielpiece = piecmove->getPieceonPos(posx, posy);
			myzielpiece = myboard->getPieceonPos(posx, posy);
			if (zielpiece == 'm' || zielpiece == 'h' || zielpiece == 'x')
			{

				if (myzielpiece != 'e')
				{
					if (posx == nx && posy == ny)
					{
						if (zielpiece == 'm')
						{
							//delete piecmove;
							//delete mypieces;
							return false;
						}
						if (myboard->getwhitetoMove() && isupper(myzielpiece))
						{
							//delete piecmove;
							//delete mypieces;
							return false;
						}
						if (!myboard->getwhitetoMove() && !isupper(myzielpiece))
						{
							//delete piecmove;
							//delete mypieces;
							return false;
						}
						this->hit = true;
					}
					else
					{
						//delete piecmove;
						//delete mypieces;
						return false;
					}
				}
				else
				{
					if (posx == nx && posy == ny)
					{
						if (zielpiece == 'h' && !searchhits)
						{
							//delete piecmove;
							//delete mypieces;
							return false;
						}
						if (searchhits && zielpiece == 'm')
						{
							//delete piecmove;
							//delete mypieces;
							return false;
						}
					}
				}

			}
			else
			{
				//delete piecmove;
				//delete mypieces;
				return false;
			}
		}
	}
	else
	{
		myzielpiece = myboard->getPieceonPos(nx, ny);
		if (myzielpiece != 'e')
		{
			if (piecmove->getPieceonPos(nx, ny) == 'x')
			{
				if (myboard->getwhitetoMove() && isupper(myzielpiece))
				{
					//delete piecmove;
					//delete mypieces;
					return false;
				}
				if (!myboard->getwhitetoMove() && !isupper(myzielpiece))
				{
					//delete piecmove;
					//delete mypieces;
					return false;
				}
				this->hit = true;
			}
			else
			{
				//delete piecmove;
				//delete mypieces;
				return false;
			}
		}
	}
	int posWhiteKing[2];
	int posBlackKing[2];

	// Führe Zug testweise aus
	// teste wenn der König die figur ist ob der andere könig zu nahe wäre
	if (pie == 'k' || pie == 'K') // für schwarzen künig
	{
		//Test auf König
		if ((ny + 1) < 9)
		{
			if (myboard->getwhitetoMove())
			{
				if (myboard->getPieceonPos(nx, ny + 1) == 'k')
				{
					//delete piecmove;
					//delete mypieces;
					return false;
				}
			}
			else
			{
				if (myboard->getPieceonPos(nx, ny + 1) == 'K')
				{
					//delete piecmove;
					//delete mypieces;
					return false;
				}
			}

		}
		if ((ny - 1)>0)
		{
			if (myboard->getwhitetoMove())
			{
				if (myboard->getPieceonPos(nx, ny - 1) == 'k')
				{
					//delete piecmove;
					//delete mypieces;
					return false;
				}
			}
			else
			{
				if (myboard->getPieceonPos(nx, ny - 1) == 'K')
				{
					//delete piecmove;
					//delete mypieces;
					return false;
				}
			}

		}
		if ((nx - 1)>0)
		{
			if (myboard->getwhitetoMove())
			{
				if (myboard->getPieceonPos(nx - 1, ny) == 'k')
				{
					//delete piecmove;
					//delete mypieces;
					return false;
				}
			}
			else
			{
				if (myboard->getPieceonPos(nx - 1, ny) == 'K')
				{
					//delete piecmove;
					//delete mypieces;
					return false;
				}
			}

		}
		if ((nx + 1)<9)
		{
			if (myboard->getwhitetoMove())
			{
				if (myboard->getPieceonPos(nx + 1, ny) == 'k')
				{
					//delete piecmove;
					//delete mypieces;
					return false;
				}
			}
			else
			{
				if (myboard->getPieceonPos(nx + 1, ny) == 'K')
				{
					//delete piecmove;
					//delete mypieces;
					return false;
				}
			}

		}
		if (((nx + 1)<9) && ((ny + 1)<9))
		{
			if (myboard->getwhitetoMove())
			{
				if (myboard->getPieceonPos(nx + 1, ny + 1) == 'k')
				{
					//delete piecmove;
					//delete mypieces;
					return false;
				}
			}
			else
			{
				if (myboard->getPieceonPos(nx + 1, ny + 1) == 'K')
				{
					//delete piecmove;
					//delete mypieces;
					return false;
				}
			}

		}
		if (((nx - 1)>0) && ((ny - 1)>0))
		{
			if (myboard->getwhitetoMove())
			{
				if (myboard->getPieceonPos(nx - 1, ny - 1) == 'k')
				{
					//delete piecmove;
					//delete mypieces;
					return false;
				}
			}
			else
			{
				if (myboard->getPieceonPos(nx - 1, ny - 1) == 'K')
				{
					//delete piecmove;
					//delete mypieces;
					return false;
				}
			}

		}
		if (((nx - 1)>0) && ((ny + 1)<9))
		{
			if (myboard->getwhitetoMove())
			{
				if (myboard->getPieceonPos(nx - 1, ny + 1) == 'k')
				{
					//delete piecmove;
					//delete mypieces;
					return false;
				}
			}
			else
			{
				if (myboard->getPieceonPos(nx - 1, ny + 1) == 'K')
				{
					//delete piecmove;
					//delete mypieces;
					return false;
				}
			}

		}
		if (((nx + 1)<9) && ((ny - 1)>0))
		{
			if (myboard->getwhitetoMove())
			{
				if (myboard->getPieceonPos(nx + 1, ny - 1) == 'k')
				{
					//delete piecmove;
					//delete mypieces;
					return false;
				}
			}
			else
			{
				if (myboard->getPieceonPos(nx + 1, ny - 1) == 'K')
				{
					//delete piecmove;
					//delete mypieces;
					return false;
				}
			}

		}
	}
	// teste ob König nach diesen Zug attackiert würde
	char oldpie = myboard->maketestmove(vx, vy, nx, ny);
	int attacks;
	if (myboard->getwhitetoMove())
	{
		if (pie == 'K')
		{
			posWhiteKing[0] = nx;
			posWhiteKing[1] = ny;
		}
		else
		{
			posWhiteKing[0] = myboard->getWhiteKingPos(true);
			posWhiteKing[1] = myboard->getWhiteKingPos(false);;
		}
		attacks = this->figureisunderAttack(posWhiteKing[0], posWhiteKing[1], true);
		myboard->takebacktestmove(vx, vy, nx, ny, oldpie);
		if (attacks > 0)
		{
			//delete piecmove;
			//delete mypieces;
			return false;
		}
	}
	else
	{
		if (pie == 'k')
		{
			posBlackKing[0] = nx;
			posBlackKing[1] = ny;
		}
		else
		{
			posBlackKing[0] = myboard->getBlackKingPos(true);
			posBlackKing[1] = myboard->getBlackKingPos(false);;
		}
		attacks = this->figureisunderAttack(posBlackKing[0], posBlackKing[1], false);
		myboard->takebacktestmove(vx, vy, nx, ny, oldpie);
		if (attacks > 0)
		{
			//delete piecmove;
			//delete mypieces;
			return false;
		}
	}
	//delete piecmove;
	//delete mypieces;
	return true;
}

bool Movement::proofRochade(int vx, int vy, int nx, int ny)
{
	if (vy == 1)
	{
		if (nx == 3 && myboard->getcastleQs(0))
		{
			if (myboard->getPieceonPos(2, 1) == 'e' && myboard->getPieceonPos(3, 1) == 'e' && myboard->getPieceonPos(4, 1) == 'e')
			{
				if ((this->figureisunderAttack(5, 1, true)>0) && (this->figureisunderAttack(4, 1, true)>0) && (this->figureisunderAttack(3, 1, true)>0))
					return false;
				else
					return true;
			}
			else
				return false;
		}
		if (nx == 7 && myboard->getcastleKs(0))
		{
			if ((myboard->getPieceonPos(6, 1) == 'e') && (myboard->getPieceonPos(7, 1) == 'e'))
			{
				if ((this->figureisunderAttack(5, 1, true)>0) && (this->figureisunderAttack(6, 1, true)>0) && (this->figureisunderAttack(7, 1, true)>0))
					return false;
				else
					return true;
			}
			else
				return false;
		}
	}
	if (vy == 8)
	{
		if (nx == 3 && myboard->getcastleQs(1))
		{
			if (myboard->getPieceonPos(2, 8) == 'e' && myboard->getPieceonPos(3, 8) == 'e' && myboard->getPieceonPos(4, 8) == 'e')
			{
				if ((this->figureisunderAttack(5, 8, false)>0) && (this->figureisunderAttack(4, 8, false)>0) && (this->figureisunderAttack(3, 8, false)>0))
					return false;
				else
					return true;
			}
			else
				return false;
		}
		if (nx == 7 && myboard->getcastleKs(1))
		{
			if (myboard->getPieceonPos(6, 8) == 'e' && myboard->getPieceonPos(7, 8) == 'e')
			{
				if ((this->figureisunderAttack(5, 8, false)>0) && (this->figureisunderAttack(6, 8, false)>0) && (this->figureisunderAttack(7, 8, false)>0))
					return false;
				else
					return true;
			}
			else
				return false;
		}
	}
	return false;
}

int Movement::figureisunderAttack(int vx, int vy, bool whitetomove)
{
	//Pieces *mypiecx = new Pieces();
	Board *test;
	//attacks = new Board();
	int attackcount = 0;
	register int i, j;
	mypieces->init();
	// Test for night
	if (whitetomove)
		mypieces->setName('n');
	else
		mypieces->setName('N');
	mypieces->setPos(vx, vy);
	test = mypieces->getActMoves();
	for (i = 1; i < 9; i++)
	{
		for (j = 1; j < 9; j++)
		{
			if (test->getPieceonPos(i, j) == 'x')
			{
				if (myboard->getPieceonPos(i, j) == mypieces->getName())
				{
					//attacks->setPiece(mypieces->getName(), i, j);
					attackcount++;
				}
			}
		}
	}
	//delete mypieces;
	// Test for Pawn
	//white
	if (whitetomove)
	{
		if ((myboard->getPieceonPos(vx - 1, vy + 1) == 'p') && ((vx - 1)>0) && ((vy + 1)<9))
		{
			//attacks->setPiece('p', vx - 1, vy + 1);
			attackcount++;
		}
		if ((myboard->getPieceonPos(vx + 1, vy + 1) == 'p') && ((vx + 1)<9) && ((vy + 1)<9))
		{
			//attacks->setPiece('p', vx + 1, vy + 1);
			attackcount++;
		}
	}
	else
	{
		if ((myboard->getPieceonPos(vx - 1, vy - 1) == 'P') && ((vx - 1)>0) && ((vy - 1)>0))
		{
			//attacks->setPiece('P', vx - 1, vy - 1);
			attackcount++;
		}
		if ((myboard->getPieceonPos(vx + 1, vy - 1) == 'P') && ((vx + 1)<9) && ((vy - 1)>0))
		{
			//attacks->setPiece('P', vx + 1, vy - 1);
			attackcount++;
		}
	}
	char piece;
	// Test für Turm und Dame
	//gerade Linie nach oben
	for (j = vy + 1; j < 9; j++)
	{
		piece = myboard->getPieceonPos(vx, j);
		if (piece != 'e')
		{
			if (whitetomove)
			{
				if (isupper(piece))
				{
					break;
				}
				else
				{
					if (piece == 'q' || piece == 'r')
					{
						//attacks->setPiece(piece, vx, j);
						attackcount++;
					}
				}
			}
			else
			{
				if (!isupper(piece))
				{
					break;
				}
				else
				{
					if (piece == 'Q' || piece == 'R')
					{
						//attacks->setPiece(piece, vx, j);
						attackcount++;
					}
				}
			}
		}
	}
	//gerade Linie nach unten
	for (j = 1; j < vy; j++)
	{
		piece = myboard->getPieceonPos(vx, vy - j);
		if (piece != 'e')
		{
			if (whitetomove)
			{
				if (isupper(piece))
				{
					break;
				}
				else
				{
					if (piece == 'q' || piece == 'r')
					{
						//attacks->setPiece(piece, vx, vy - j);
						attackcount++;
					}
				}
			}
			else
			{
				if (!isupper(piece))
				{
					break;
				}
				else
				{
					if (piece == 'Q' || piece == 'R')
					{
						//attacks->setPiece(piece, vx, vy - j);
						attackcount++;
					}
				}
			}
		}
	}
	//gerade Linie nach rechte
	for (j = vx + 1; j < 9; j++)
	{
		piece = myboard->getPieceonPos(j, vy);
		if (piece != 'e')
		{
			if (whitetomove)
			{
				if (isupper(piece))
				{
					break;
				}
				else
				{
					if (piece == 'q' || piece == 'r')
					{
						//attacks->setPiece(piece, j, vy);
						attackcount++;
					}
				}
			}
			else
			{
				if (!isupper(piece))
				{
					break;
				}
				else
				{
					if (piece == 'Q' || piece == 'R')
					{
						//attacks->setPiece(piece, j, vy);
						attackcount++;
					}
				}
			}
		}
	}
	//gerade Linie nach links
	for (j = vx - 1; j>0; j--)
	{
		piece = myboard->getPieceonPos(j, vy);
		//printf("teste %d dame rook pie %c \n",j,piece);
		if (piece != 'e')
		{
			if (whitetomove)
			{
				if (isupper(piece))
				{
					break;
				}
				else
				{
					if ((piece == 'q') || (piece == 'r'))
					{
						//attacks->setPiece(piece, j, vy);
						attackcount++;
					}
				}
			}
			else
			{
				if (!isupper(piece))
				{
					break;
				}
				else
				{
					if ((piece == 'Q') || (piece == 'R'))
					{
						//attacks->setPiece(piece, j, vy);
						attackcount++;
					}
				}
			}
		}
	}
	// Test für Läufer und Dame
	//Linie nach rechts oben
	for (j = 1; j < 9; j++)
	{
		if (((vx + j) > 8) || ((vy + j) > 8))
			break;
		piece = myboard->getPieceonPos(vx + j, vy + j);
		if (piece != 'e')
		{
			if (whitetomove)
			{
				if (isupper(piece))
				{
					break;
				}
				else
				{
					if (piece == 'q' || piece == 'b')
					{
						//attacks->setPiece(piece, vx + j, vy + j);
						attackcount++;
					}
				}
			}
			else
			{
				if (!isupper(piece))
				{
					break;
				}
				else
				{
					if (piece == 'Q' || piece == 'B')
					{
						//attacks->setPiece(piece, vx + j, vy + j);
						attackcount++;
					}
				}
			}
		}
	}
	//Linie rechts unten
	for (j = 1; j < 9; j++)
	{
		if (((vx + j) > 8) || ((vy - j) < 1))
			break;
		piece = myboard->getPieceonPos(vx + j, vy - j);
		if (piece != 'e')
		{
			if (whitetomove)
			{
				if (isupper(piece))
				{
					break;
				}
				else
				{
					if (piece == 'q' || piece == 'b')
					{
						//attacks->setPiece(piece, vx + j, vy - j);
						attackcount++;
					}
				}
			}
			else
			{
				if (!isupper(piece))
				{
					break;
				}
				else
				{
					if (piece == 'Q' || piece == 'B')
					{
						//attacks->setPiece(piece, vx + j, vy - j);
						attackcount++;
					}
				}
			}
		}
	}
	//Linie nach links unten
	for (j = 1; j < 9; j++)
	{
		if (((vx - j) < 1) || ((vy - j) < 1))
			break;
		piece = myboard->getPieceonPos(vx - j, vy - j);
		if (piece != 'e')
		{
			if (whitetomove)
			{
				if (isupper(piece))
				{
					break;
				}
				else
				{
					if (piece == 'q' || piece == 'b')
					{
						//attacks->setPiece(piece, vx - j, vy - j);
						attackcount++;
					}
				}
			}
			else
			{
				if (!isupper(piece))
				{
					break;
				}
				else
				{
					if (piece == 'Q' || piece == 'B')
					{
						//attacks->setPiece(piece, vx - j, vy - j);
						attackcount++;
					}
				}
			}
		}
	}
	//Linie nach links oben
	for (j = 1; j < 9; j++)
	{
		if (((vx - j) < 1) || ((vy + j) > 8))
			break;
		piece = myboard->getPieceonPos(vx - j, vy + j);
		if (piece != 'e')
		{
			if (whitetomove)
			{
				if (isupper(piece))
				{
					break;
				}
				else
				{
					if (piece == 'q' || piece == 'b')
					{
						//attacks->setPiece(piece, vx - j, vy + j);
						attackcount++;
					}
				}
			}
			else
			{
				if (!isupper(piece))
				{
					break;
				}
				else
				{
					if (piece == 'Q' || piece == 'B')
					{
						//attacks->setPiece(piece, vx - j, vy + j);
						attackcount++;
					}
				}
			}
		}
	}
	//Test auf König
	if ((vy + 1) < 9)
	{
		if (whitetomove)
		{
			if (myboard->getPieceonPos(vx, vy + 1) == 'k')
			{
				//attacks->setPiece('k', vx, vy + 1);
				attackcount++;
			}
		}
		else
		{
			if (myboard->getPieceonPos(vx, vy + 1) == 'K')
			{
				//attacks->setPiece('K', vx, vy + 1);
				attackcount++;
			}
		}

	}
	if ((vy - 1)>0)
	{
		if (whitetomove)
		{
			if (myboard->getPieceonPos(vx, vy - 1) == 'k')
			{
				//attacks->setPiece('k', vx, vy - 1);
				attackcount++;
			}
		}
		else
		{
			if (myboard->getPieceonPos(vx, vy - 1) == 'K')
			{
				//attacks->setPiece('K', vx, vy - 1);
				attackcount++;
			}
		}

	}
	if ((vx - 1)>0)
	{
		if (whitetomove)
		{
			if (myboard->getPieceonPos(vx - 1, vy) == 'k')
			{
				//attacks->setPiece('k', vx - 1, vy);
				attackcount++;
			}
		}
		else
		{
			if (myboard->getPieceonPos(vx - 1, vy) == 'K')
			{
				//attacks->setPiece('K', vx - 1, vy);
				attackcount++;
			}
		}

	}
	if ((vx + 1)<9)
	{
		if (whitetomove)
		{
			if (myboard->getPieceonPos(vx + 1, vy) == 'k')
			{
				//attacks->setPiece('k', vx + 1, vy);
				attackcount++;
			}
		}
		else
		{
			if (myboard->getPieceonPos(vx + 1, vy) == 'K')
			{
				//attacks->setPiece('K', vx + 1, vy);
				attackcount++;
			}
		}

	}
	if (((vx + 1)<9) && ((vy + 1)<9))
	{
		if (whitetomove)
		{
			if (myboard->getPieceonPos(vx + 1, vy + 1) == 'k')
			{
				//attacks->setPiece('k', vx + 1, vy + 1);
				attackcount++;
			}
		}
		else
		{
			if (myboard->getPieceonPos(vx + 1, vy + 1) == 'K')
			{
				//attacks->setPiece('K', vx + 1, vy + 1);
				attackcount++;
			}
		}

	}
	if (((vx - 1)>0) && ((vy - 1)>0))
	{
		if (whitetomove)
		{
			if (myboard->getPieceonPos(vx - 1, vy - 1) == 'k')
			{
				//attacks->setPiece('k', vx - 1, vy - 1);
				attackcount++;
			}
		}
		else
		{
			if (myboard->getPieceonPos(vx - 1, vy - 1) == 'K')
			{
				//attacks->setPiece('K', vx - 1, vy - 1);
				attackcount++;
			}
		}

	}
	if (((vx - 1)>0) && ((vy + 1)<9))
	{
		if (whitetomove)
		{
			if (myboard->getPieceonPos(vx - 1, vy + 1) == 'k')
			{
				//attacks->setPiece('k', vx - 1, vy + 1);
				attackcount++;
			}
		}
		else
		{
			if (myboard->getPieceonPos(vx - 1, vy + 1) == 'K')
			{
				//attacks->setPiece('K', vx - 1, vy + 1);
				attackcount++;
			}
		}

	}
	if (((vx + 1)<9) && ((vy - 1)>0))
	{
		if (whitetomove)
		{
			if (myboard->getPieceonPos(vx + 1, vy - 1) == 'k')
			{
				//attacks->setPiece('k', vx + 1, vy - 1);
				attackcount++;
			}
		}
		else
		{
			if (myboard->getPieceonPos(vx + 1, vy - 1) == 'K')
			{
				////attacks->setPiece('K', vx + 1, vy - 1);
				attackcount++;
			}
		}

	}
	//delete test;
	return attackcount;
}

bool Movement::loadFromFen(std::string pos)
{
	this->myboard->loadFromFen(const_cast<char*>(pos.c_str()));
	return false;
}

char Movement::getPieceonPos(int abc, int zahl)
{
	return myboard->getPieceonPos(abc, zahl);
}

bool Movement::getWhitehasMove()
{
	return this->myboard->getwhitetoMove();
}

bool Movement::setBoard(Board *mynewBoard)
{
	delete myboard;
	myboard = mynewBoard->copyBoard();
	return false;
}

Board *Movement::copyBoard()
{
	Board *newboard = new Board();
	for (int i = 1; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			newboard->setPiece(myboard->getPieceonPos(i, j), i, j);
		}
	}
	newboard->setBewertung(myboard->getBewertung());
	newboard->setFigurenwert(myboard->getFigurenwert());
	newboard->setcastleQs(0, myboard->getcastleQs(0));
	newboard->setcastleQs(1, myboard->getcastleQs(1));
	newboard->setcastleKs(0, myboard->getcastleKs(0));
	newboard->setcastleKs(1, myboard->getcastleKs(1));
	newboard->setwhitetoMove(myboard->getwhitetoMove());
	newboard->setEnPassant(myboard->getEnPassantField(true), true);
	newboard->setEnPassant(myboard->getEnPassantField(false), false);
	newboard->setZugNr(myboard->getZugNr());
	newboard->setHalbzug(myboard->getHalbzug());
	for (int i = 0; i < 6; i++)
	{
		newboard->setWiederHol(myboard->getWiederHol(i, 0, 0), i, 0, 0);
		newboard->setWiederHol(myboard->getWiederHol(i, 0, 1), i, 0, 1);
		newboard->setWiederHol(myboard->getWiederHol(i, 1, 0), i, 1, 0);
		newboard->setWiederHol(myboard->getWiederHol(i, 1, 1), i, 1, 1);
	}
	newboard->setWiederCount(myboard->getWiederCount());
	newboard->setWhiteKingPos(myboard->getWhiteKingPos(true), true);
	newboard->setWhiteKingPos(myboard->getWhiteKingPos(false), false);
	newboard->setBlackKingPos(myboard->getBlackKingPos(true), true);
	newboard->setBlackKingPos(myboard->getBlackKingPos(false), false);
	newboard->setRemie(myboard->getRemie(true), true);
	newboard->setRemie(myboard->getRemie(true), true);
	return newboard;
}



char Movement::setPiece(char pie, int vx, int vy)
{
	char f = myboard->getPieceonPos(vx, vy);
	myboard->setPiece(pie, vx, vy);
	return f;
}


bool Movement::makenextMove(int vx, int vy, int nx, int ny, char p)
{
	Zuege *akt;
	char pie = myboard->getPieceonPos(vx, vy);
	if ((pie == 'k') || (pie == 'K'))
	{
		if (vx == 5 && (nx == 7 || nx == 3) && ((ny == 1 && vy == 1) || (ny == 8 && vy == 8)))
		{
			return myboard->makeRochade(myboard, vx, vy, nx, ny);
		}
	}
	if (pie == 'p' || pie == 'P')
	{
		if ((ny - vy) == 2 || (vy - ny) == 2)
		{
			myboard->setEnPassant(nx, true);
			myboard->setEnPassant(ny - 1, false);
		}
	}
	if (this->myboard->getwhitetoMove())
	{
		akt = new Zuege();
		akt->setZugNr(myboard->getZugNr() + 1);
		akt->setWhitePiece(vx, vy, nx, ny);
		if (p != ' ')
			akt->setWhiteTrade(p);
		this->mynot->addZug(akt);
	}
	else
	{
		akt = this->mynot->getAktZug();
		akt->setBlackPiece(vx, vy, nx, ny);
		if (p != ' ')
			akt->setBlackTrade(p);
	}
	bool correct = myboard->makeMove(vx, vy, nx, ny);
	if (correct && p != ' ')
		correct = myboard->setPieceTrade(p, nx, ny);
	//delete akt;
	return correct;
}

int Movement::getZugNr()
{
	return this->myboard->getZugNr();
}

void Movement::printZuege()
{
	printf(this->mynot->getZuegeStr());
}

void Movement::init()
{
	hit = false;
	this->myboard->init();
	while(this->mynot->getAktZugNr()>0)
		this->mynot->deleteLastZug();
	//this->attacks = new Board();
	this->mypieces->init();
}
