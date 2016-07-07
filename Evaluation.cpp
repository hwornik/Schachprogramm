#include "stdafx.h"
#include "Evaluation.h"


Evaluation::Evaluation()
{
	movesFields = 0;
	movesFigure = 0;
	hits = 0;
	notat[0] = 'a';
	notat[1] = 'b';
	notat[2] = 'c';
	notat[3] = 'd';
	notat[4] = 'e';
	notat[5] = 'f';
	notat[6] = 'g';
	notat[7] = 'h';
	trade = false;
	tradefig = ' ';
	moving = new Movement();
	hitboard = new Board();
	hitmvboard = new Board();
	moveboard = new Board();
	pie = new Pieces();
}


Evaluation::~Evaluation()
{
	delete moving;
	delete hitboard;
	delete moveboard;
	delete pie;
}


Board * Evaluation::possibleMoves(Board *myboard)
{
	//Movement *moving;
	//moving = new Movement();
	moving->init();
	moving->setBoard(myboard);
	// *moveboard = new Board();
	moveboard->init();
	char c;
	movesFigure = 0;
	movesFields = 0;
	hits = 0;
	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			c = moving->getPieceonPos(i, j);
			if (c != 'e')
			{
				this->compMovesandHits(false, c, moving, i, j, moveboard);
			}
		}
	}
	//delete moving;
	//moving = 0;
	return moveboard;
}

int Evaluation::possibleMovesFigure()
{
	return movesFigure;
}

int Evaluation::possibleFields()
{
	return movesFields;
}

int Evaluation::possibleHits()
{
	return hits;
}

bool Evaluation::printStats()
{
	printf("Bewertung Board %d\n", bewertung);
	printf("Kontrolierte Felder%d\n", kontrolleF);
	printf("Mögliche Moves %d\n", movesFields);
	printf("Mögliche Hits %d\n", hits);
	printf("Bewegliche Figuren %d\n", movesFigure);
	return false;
}

int Evaluation::getMovesFigures()
{
	return this->movesFigure;
}

bool Evaluation::makeThisMovesfigure(Board *myboard, int vx, int vy, int nx, int ny)
{
	//Movement *moving;
	//moving = new Movement();
	moving->init();
	moving->setBoard(myboard);
	movesFigure = 0;
	movesFields = 0;
	hits = 0;
	//Board *moveboard = new Board();
	//Board *hitboard = new Board();
	//hitboard->init();
	char f, e, c;
	trade = false;
	tradefig = ' ';
	//printf("info currmove %c%d%c%d\n", notat[vx - 1], vy, notat[nx - 1], ny);
	f = moving->setPiece('e', vx, vy);
	if (f == 'P'&& ny == 8)
	{
		f = 'Q';
		tradefig = 'Q';
		trade = true;
	}
	if (f == 'p'&& ny == 1)
	{
		f = 'q';
		tradefig = 'q';
		trade = true;
	}
	e = moving->setPiece(f, nx, ny);
	/*for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			c = moving->getPieceonPos(i, j);
			if (c != 'e')
			{

				this->compMovesandHits(false, c, moving, i, j, hitboard);
			}
		}
	}  */
    hitboard->init();
    for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			c = moving->getPieceonPos(i, j);
			if (c != 'e')
			{
				this->compMovesandHits(true, c, moving, i, j, hitboard);
			}
		}
	}
	kontrolleF = countXFields(hitboard, moving->getWhitehasMove());
	bewertung = figurenBewertung(moving);
	if (trade && ny == 8)
	{
		f = 'Q';
	}
	if (trade && ny == 1)
	{
		f = 'q';
	}
	moving->setPiece(f, vx, vy);
	moving->setPiece(e, nx, ny);
	//delete moveboard;
	//delete hitboard;
	//delete moving;
	return true;
}
bool Evaluation::makeNextMovesfigure()
{
	//Movement *moving;
	//moving = new Movement();
	movesFigure = 0;
	movesFields = 0;
	hits = 0;
	//Board *moveboard = new Board();
	//Board *hitboard = new Board();
	hitboard->init();
	char f, e, c;
	movenr++;
	hitboard->init();
	hitmvboard->init();
	trade = false;
	tradefig = ' ';
	if (movenr <= zahlermoves)
	{
		//printf("info currmove %c%d%c%d\n", notat[moveperFigure[0][0] - 1], moveperFigure[0][1], notat[moveperFigure[movenr][0] - 1], moveperFigure[movenr][1]);
		f = moving->setPiece('e', moveperFigure[0][0], moveperFigure[0][1]);
		if (f == 'P'&& moveperFigure[movenr][1] == 8)
		{
			f = 'Q';
			tradefig = 'Q';
			trade = true;
		}
		if (f == 'p'&& moveperFigure[movenr][1] == 1)
		{
			f = 'q';
			tradefig = 'q';
			trade = true;
		}
		e = moving->setPiece(f, moveperFigure[movenr][0], moveperFigure[movenr][1]);
		for (int i = 1; i < 9; i++)
		{
			for (int j = 1; j < 9; j++)
			{
				c = moving->getPieceonPos(i, j);
				if (c != 'e')
				{

					this->compMovesandHits(false, c, moving, i, j, moveboard);
					this->compMovesandHits(true, c, moving, i, j, hitboard);
				}
			}
		}
		kontrolleF = countXFields(hitboard, moving->getWhitehasMove());
		bewertung = figurenBewertung(moving);
		if (trade && moveperFigure[movenr][1] == 8)
		{
			f = 'Q';
		}
		if (trade && moveperFigure[movenr][1] == 1)
		{
			f = 'q';
		}
		moving->setPiece(f, moveperFigure[0][0], moveperFigure[0][1]);
		moving->setPiece(e, moveperFigure[movenr][0], moveperFigure[movenr][1]);
		//delete moveboard;
		//delete hitboard;
		return true;
	}
	//delete moveboard;
	//delete hitboard;
	//delete moving;
	return false;

}

int Evaluation::computeMovesfigure(int vx, int vy, Board * myboard)
{
	movenr = 0;
	//Movement *moving;
	//moving = new Movement();
	moving->init();
	moving->setBoard(myboard);
	this->noticeMovesandHits(moving->getPieceonPos(vx, vy), moving, vx, vy);
	//delete moving;
	return 0;
}

int Evaluation::getZuege()
{
	return movesFields;
}

int Evaluation::getHits()
{
	return hits;
}

char *Evaluation::getZugStr()
{
	char *str = new char[6];
	if (trade)
	{
		sprintf(str, "%c%d%c%d%c", notat[moveperFigure[0][0] - 1], moveperFigure[0][1], notat[moveperFigure[movenr][0] - 1], moveperFigure[movenr][1], tradefig);
		return str;
	}
	else
	{
		sprintf(str, "%c%d%c%d", notat[moveperFigure[0][0] - 1], moveperFigure[0][1], notat[moveperFigure[movenr][0] - 1], moveperFigure[movenr][1]);
		return str;
	}

}

int Evaluation::figurenBewertung(Movement * moving)
{
	int white = 0, black = 0;
	char f;
	//Pieces *pie = new Pieces();
	pie->init();
	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			f = moving->getPieceonPos(i, j);
			if (f != 'e' && f != 'x' && f != 'm' && f != 'h')
			{
				pie->setName(f);
				if (isupper(f))
				{
					white += pie->getWert();
				}
				else
				{
					black += pie->getWert();
				}
			}
		}
	}
	white *= 100;
	black *= 100;
	//delete pie;
	return white - black;
}

int Evaluation::getKontrolFields()
{
	return kontrolleF;
}

int Evaluation::getFigurenwert()
{
	return bewertung;
}

int Evaluation::getZug(bool xwert)
{
	int i = 1;
	if (xwert)
		i = 0;
	return moveperFigure[movenr][i];
}

int Evaluation::getZug(bool von,bool xwert)
{
	int i = 1;
	if (xwert)
		i = 0;
	if(von)
		return moveperFigure[0][i];
	else
		return moveperFigure[movenr][i];
}

int Evaluation::countXFields(Board * hitboard, bool whitetomove)
{
	int x = 0;
	//printf("\n");
	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			//printf("%c",hitboard->getPieceonPos(i, j) );
			if (hitboard->getPieceonPos(i, j) == 'x' || hitboard->getPieceonPos(i, j) == 'h')
			{
				if (whitetomove && j == 5 && i>2 && i<7)
					x++;
				else if (!whitetomove && j == 4 && i>2 && i<7)
					x++;
				x++;
			}
		}
		//printf("\n");
	}
	return x;
}


bool Evaluation::noticeMovesandHits(char pie, Movement *moving, int vx, int vy)
{
	moveperFigure[0][0] = vx;
	moveperFigure[0][1] = vy;
	zahlermoves = 0;
	char promo = ' ';
	bool notfoundfigure = true;
	if ((pie == 'n') || (pie == 'N'))
	{
		// Night;
		if (((vx + 2) < 9) && ((vy + 1) < 9))
		{
			if (moving->proofNextMove(false, vx, vy, vx + 2, vy + 1, promo))
			{
				zahlermoves++;
				moveperFigure[zahlermoves][0] = vx + 2;
				moveperFigure[zahlermoves][1] = vy + 1;
			}
		}
		if (((vx + 2)<9) && ((vy - 1)>0))
		{
			if (moving->proofNextMove(false, vx, vy, vx + 2, vy - 1, promo))
			{
				zahlermoves++;
				moveperFigure[zahlermoves][0] = vx + 2;
				moveperFigure[zahlermoves][1] = vy - 1;
			}
		}
		if (((vx - 2)>0) && ((vy + 1)<9))
		{
			if (moving->proofNextMove(false, vx, vy, vx - 2, vy + 1, promo))
			{
				zahlermoves++;
				moveperFigure[zahlermoves][0] = vx - 2;
				moveperFigure[zahlermoves][1] = vy + 1;
			}
		}
		if (((vx - 2)>0) && ((vy - 1)>0))
		{
			if (moving->proofNextMove(false, vx, vy, vx - 2, vy - 1, promo))
			{
				zahlermoves++;
				moveperFigure[zahlermoves][0] = vx - 2;
				moveperFigure[zahlermoves][1] = vy - 1;
			}
		}
		if (((vx + 1)<9) && ((vy + 2)<9))
		{
			if (moving->proofNextMove(false, vx, vy, vx + 1, vy + 2, promo))
			{
				zahlermoves++;
				moveperFigure[zahlermoves][0] = vx + 1;
				moveperFigure[zahlermoves][1] = vy + 2;
			}
		}
		if (((vx - 1)>0) && ((vy + 2)<9))
		{
			if (moving->proofNextMove(false, vx, vy, vx - 1, vy + 2, promo))
			{
				zahlermoves++;
				moveperFigure[zahlermoves][0] = vx - 1;
				moveperFigure[zahlermoves][1] = vy + 2;
			}
		}
		if (((vx - 1)>0) && ((vy - 2)>0))
		{
			if (moving->proofNextMove(false, vx, vy, vx - 1, vy - 2, promo))
			{
				zahlermoves++;
				moveperFigure[zahlermoves][0] = vx - 1;
				moveperFigure[zahlermoves][1] = vy - 2;
			}
		}
		if (((vx + 1)<9) && ((vy - 2)>0))
		{
			if (moving->proofNextMove(false, vx, vy, vx + 1, vy - 2, promo))
			{
				zahlermoves++;
				moveperFigure[zahlermoves][0] = vx + 1;
				moveperFigure[zahlermoves][1] = vy - 2;
			}
		}
	}
	else
	{
		if ((pie != 'B') && (pie != 'b') )
		{
			// Move Forward
			for (int i = 1; i < 9 - vy; i++)
			{
				if (moving->proofNextMove(false, vx, vy, vx, vy + i, promo))
				{
					zahlermoves++;
					moveperFigure[zahlermoves][0] = vx;
					moveperFigure[zahlermoves][1] = vy + i;
				}
				else
				{
					break;
				}
			}
			// Move right
			for (int i = 1; i < 9 - vx; i++)
			{
				if (moving->proofNextMove(false, vx, vy, vx + i, vy, promo))
				{
					zahlermoves++;
					moveperFigure[zahlermoves][0] = vx + i;
					moveperFigure[zahlermoves][1] = vy;
				}
				else
				{
					break;
				}
			}
			// Move down
			for (int i = 1; i < vy; i++)
			{

				if (moving->proofNextMove(false, vx, vy, vx, vy - i, promo))
				{
					zahlermoves++;
					moveperFigure[zahlermoves][0] = vx;
					moveperFigure[zahlermoves][1] = vy - i;
				}
				else
				{
					break;
				}

			}
			// Move left
			for (int i = 1; i < vx; i++)
			{

				if (moving->proofNextMove(false, vx, vy, vx - i, vy, promo))
				{
					zahlermoves++;
					moveperFigure[zahlermoves][0] = vx - i;
					moveperFigure[zahlermoves][1] = vy;
				}
				else
				{
					break;
				}

			}
		}
		if ((pie != 'R') && (pie != 'r') )
		{
			// nach rechts oben
			for (int i = 1; i < 9; i++)
			{

				if (((vx + i)<9) && ((vy + i)<9) && (moving->proofNextMove(false, vx, vy, vx + i, vy + i, promo)))
				{
					zahlermoves++;
					moveperFigure[zahlermoves][0] = vx + i;
					moveperFigure[zahlermoves][1] = vy + i;
				}
				else
				{
					break;
				}

			}
			// nach rechts unten
			for (int i = 1; i < 9; i++)
			{

				if (((vx + i)<9) && ((vy - i)>0) && (moving->proofNextMove(false, vx, vy, vx + i, vy - i, promo)))
				{
					zahlermoves++;
					moveperFigure[zahlermoves][0] = vx + i;
					moveperFigure[zahlermoves][1] = vy - i;
				}
				else
				{
					break;
				}

			}
			// nach links unten
			for (int i = 1; i < 9; i++)
			{

				if (((vx - i)>0) && ((vy - i)>0) && (moving->proofNextMove(false, vx, vy, vx - i, vy - i, promo)))
				{
					zahlermoves++;
					moveperFigure[zahlermoves][0] = vx - i;
					moveperFigure[zahlermoves][1] = vy - i;
				}
				else
				{
					break;
				}

			}
			// nach links oben
			for (int i = 1; i < 9; i++)
			{

				if (((vx - i)>0) && ((vy + i)<9) && (moving->proofNextMove(false, vx, vy, vx - i, vy + i, promo)))
				{
					zahlermoves++;
					moveperFigure[zahlermoves][0] = vx - i;
					moveperFigure[zahlermoves][1] = vy + i;
				}
				else
				{
					break;
				}

			}
		}
	}
	return false;
}

bool Evaluation::compMovesandHits(bool searchhits, char pie, Movement *moving, int vx, int vy, Board * moveboard)
{
	char promo = ' ';
	bool notfoundfigure = true;
	if ((pie == 'n') || (pie == 'N'))
	{
		// Night;
		if (((vx + 2) < 9) && ((vy + 1) < 9))
		{
			if (moving->proofNextMove(searchhits, vx, vy, vx + 2, vy + 1, promo))
			{
				notfoundfigure = this->nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx + 2, vy + 1, moveboard);
			}
		}
		if (((vx + 2)<9) && ((vy - 1)>0))
		{
			if (moving->proofNextMove(searchhits, vx, vy, vx + 2, vy - 1, promo))
			{
				notfoundfigure = this->nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx + 2, vy - 1, moveboard);
			}
		}
		if (((vx - 2)>0) && ((vy + 1)<9))
		{
			if (moving->proofNextMove(searchhits, vx, vy, vx - 2, vy + 1, promo))
			{
				notfoundfigure = this->nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx - 2, vy + 1, moveboard);
			}
		}
		if (((vx - 2)>0) && ((vy - 1)>0))
		{
			if (moving->proofNextMove(searchhits, vx, vy, vx - 2, vy - 1, promo))
			{
				notfoundfigure = this->nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx - 2, vy - 1, moveboard);
			}
		}
		if (((vx + 1)<9) && ((vy + 2)<9))
		{
			if (moving->proofNextMove(searchhits, vx, vy, vx + 1, vy + 2, promo))
			{
				notfoundfigure = this->nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx + 1, vy + 2, moveboard);
			}
		}
		if (((vx - 1)>0) && ((vy + 2)<9))
		{
			if (moving->proofNextMove(searchhits, vx, vy, vx - 1, vy + 2, promo))
			{
				notfoundfigure = this->nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx - 1, vy + 2, moveboard);
			}
		}
		if (((vx - 1)>0) && ((vy - 2)>0))
		{
			if (moving->proofNextMove(searchhits, vx, vy, vx - 1, vy - 2, promo))
			{
				notfoundfigure = this->nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx - 1, vy - 2, moveboard);
			}
		}
		if (((vx + 1)<9) && ((vy - 2)>0))
		{
			if (moving->proofNextMove(searchhits, vx, vy, vx + 1, vy - 2, promo))
			{
				notfoundfigure = this->nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx + 1, vy - 2, moveboard);
			}
		}
	}
	else
	{
		if (pie != 'B' && pie != 'b')
		{
			// Move Forward
			for (int i = 1; i < 9 - vy; i++)
			{
				if (moving->proofNextMove(searchhits, vx, vy, vx, vy + i, promo))
				{
					notfoundfigure = nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx, vy + i, moveboard);
				}
				else
				{
					break;
				}
			}
			// Move right
			for (int i = 1; i < 9 - vx; i++)
			{
				if (moving->proofNextMove(searchhits, vx, vy, vx + 1, vy, promo))
				{
					notfoundfigure = nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx + 1, vy, moveboard);
				}
				else
				{
					break;
				}
			}
			// Move down
			for (int i = 1; i < vy; i++)
			{

				if (moving->proofNextMove(searchhits, vx, vy, vx, vy - i, promo))
				{
					notfoundfigure = nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx, vy - i, moveboard);
				}
				else
				{
					break;
				}

			}
			// Move left
			for (int i = 1; i < vx; i++)
			{

				if (moving->proofNextMove(searchhits, vx, vy, vx - i, vy, promo))
				{
					notfoundfigure = nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx - i, vy, moveboard);
				}
				else
				{
					break;
				}

			}
		}
		if (pie != 'R' && pie != 'r')
		{
			// nach rechts oben
			for (int i = 1; i < 9; i++)
			{

				if (((vx + i)<9) && ((vy + i)<9) && (moving->proofNextMove(searchhits, vx, vy, vx + i, vy + i, promo)))
				{
					notfoundfigure = nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx + i, vy + i, moveboard);
				}
				else
				{
					break;
				}

			}
			// nach rechts unten
			for (int i = 1; i < 9; i++)
			{

				if (((vx + i)<9) && ((vy - i)>0) && (moving->proofNextMove(searchhits, vx, vy, vx + i, vy - i, promo)))
				{
					notfoundfigure = nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx + i, vy - i, moveboard);
				}
				else
				{
					break;
				}

			}
			// nach links unten
			for (int i = 1; i < 9; i++)
			{

				if (((vx - i)>0) && ((vy - i)>0) && (moving->proofNextMove(searchhits, vx, vy, vx - i, vy - i, promo)))
				{
					notfoundfigure = nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx - i, vy - i, moveboard);
				}
				else
				{
					break;
				}

			}
			// nach links oben
			for (int i = 1; i < 9; i++)
			{

				if (((vx - i)>0) && ((vy + i)<9) && (searchhits, moving->proofNextMove(searchhits, vx, vy, vx - i, vy + i, promo)))
				{
					notfoundfigure = nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx - i, vy + i, moveboard);
				}
				else
				{
					break;
				}

			}
		}
	}
	return false;
}

bool Evaluation::nightTest(bool searchhits, char pie, bool notfoundfigure, bool ishit, int vx, int vy, int nx, int ny, Board *moveboard)
{
	if (notfoundfigure)
	{
		moveboard->setPiece(pie, vx, vy);
		movesFigure++;
		notfoundfigure = false;
	}
	if (searchhits)
	{
		moveboard->setPiece('x', nx, ny);
 	}
	else
	{
		if (ishit)
		{
			moveboard->setPiece('x', nx, ny);
			hits++;
		}
		else
		{
			moveboard->setPiece('m', nx, ny);
			movesFields++;
		}
	}
	return notfoundfigure;
}

int Evaluation::getZugNr()
{
	return compzugnr;
}

bool Evaluation::isPosunderAttack(Board *myboard,int posx,int posy, bool whitetomove)
{
	char c;
	moving->init();
	moving->setBoard(myboard);
	moveboard->init();
	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			c = moving->getPieceonPos(i, j);
			if (c != 'e')
			{
				//this->compMovesandHits(false, c, moving, i, j, moveboard);
				this->compMovesandHits(true, c, moving, i, j, moveboard);
			}
		}
	}
	/*std::cout << "hitboard\n";
	for(int i=1;i<9;i++)
	{
		for(int j=1;j<9;j++)
		{
			 std::cout << hitboard->getPieceonPos(i,j);
		}
		std::cout << "\n";
	} */
	if(moveboard->getPieceonPos(posx,posy)=='x')
		return true;
	else
		return false;
}

Pieces *Evaluation::whichFigureAttacks(Board *myboard,int posx,int posy, bool whitetomove)
{
	int anzahl=0;
	// Test auf Turm oder Dame
	// Test auf Läufer oder Dame
	// Test auf Bauer
	// Test auf König
	char promo = ' ';
	bool notfoundfigure = true;
	Pieces *piec[20];
	// Test auf Night
	if ((pie == 'n') || (pie == 'N'))
	{
		// Night;
		if (((posx + 2) < 9) && ((posy + 1) < 9))
		{
			if (whitetomove && myboard->getPieceonPos( posx + 2, posy + 1)=='n')
			{
					piec[anzahl]= new Pieces();
					piec[anzahl]->setName(myboard->getPieceonPos(posx,posy));
					piec[anzahl]->setPos(posx,posy);
					anzahl++;
			}
			else if(!whitetomove && myboard->getPieceonPos( posx + 2, posy + 1)=='N')
			{
					piec[anzahl]= new Pieces();
					piec[anzahl]->setName(myboard->getPieceonPos(posx,posy));
					piec[anzahl]->setPos(posx,posy);
                    anzahl++;
            }

		}
		if (((vx + 2)<9) && ((vy - 1)>0))
		{
			if (moving->proofNextMove(searchhits, vx, vy, vx + 2, vy - 1, promo))
			{
				notfoundfigure = this->nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx + 2, vy - 1, moveboard);
			}
		}
		if (((vx - 2)>0) && ((vy + 1)<9))
		{
			if (moving->proofNextMove(searchhits, vx, vy, vx - 2, vy + 1, promo))
			{
				notfoundfigure = this->nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx - 2, vy + 1, moveboard);
			}
		}
		if (((vx - 2)>0) && ((vy - 1)>0))
		{
			if (moving->proofNextMove(searchhits, vx, vy, vx - 2, vy - 1, promo))
			{
				notfoundfigure = this->nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx - 2, vy - 1, moveboard);
			}
		}
		if (((vx + 1)<9) && ((vy + 2)<9))
		{
			if (moving->proofNextMove(searchhits, vx, vy, vx + 1, vy + 2, promo))
			{
				notfoundfigure = this->nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx + 1, vy + 2, moveboard);
			}
		}
		if (((vx - 1)>0) && ((vy + 2)<9))
		{
			if (moving->proofNextMove(searchhits, vx, vy, vx - 1, vy + 2, promo))
			{
				notfoundfigure = this->nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx - 1, vy + 2, moveboard);
			}
		}
		if (((vx - 1)>0) && ((vy - 2)>0))
		{
			if (moving->proofNextMove(searchhits, vx, vy, vx - 1, vy - 2, promo))
			{
				notfoundfigure = this->nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx - 1, vy - 2, moveboard);
			}
		}
		if (((vx + 1)<9) && ((vy - 2)>0))
		{
			if (moving->proofNextMove(searchhits, vx, vy, vx + 1, vy - 2, promo))
			{
				notfoundfigure = this->nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx + 1, vy - 2, moveboard);
			}
		}
	}
	else
	{
		if (pie != 'B' && pie != 'b')
		{
			// Move Forward
			for (int i = 1; i < 9 - vy; i++)
			{
				if (moving->proofNextMove(searchhits, vx, vy, vx, vy + i, promo))
				{
					notfoundfigure = nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx, vy + i, moveboard);
				}
				else
				{
					break;
				}
			}
			// Move right
			for (int i = 1; i < 9 - vx; i++)
			{
				if (moving->proofNextMove(searchhits, vx, vy, vx + 1, vy, promo))
				{
					notfoundfigure = nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx + 1, vy, moveboard);
				}
				else
				{
					break;
				}
			}
			// Move down
			for (int i = 1; i < vy; i++)
			{

				if (moving->proofNextMove(searchhits, vx, vy, vx, vy - i, promo))
				{
					notfoundfigure = nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx, vy - i, moveboard);
				}
				else
				{
					break;
				}

			}
			// Move left
			for (int i = 1; i < vx; i++)
			{

				if (moving->proofNextMove(searchhits, vx, vy, vx - i, vy, promo))
				{
					notfoundfigure = nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx - i, vy, moveboard);
				}
				else
				{
					break;
				}

			}
		}
		if (pie != 'R' && pie != 'r')
		{
			// nach rechts oben
			for (int i = 1; i < 9; i++)
			{

				if (((vx + i)<9) && ((vy + i)<9) && (moving->proofNextMove(searchhits, vx, vy, vx + i, vy + i, promo)))
				{
					notfoundfigure = nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx + i, vy + i, moveboard);
				}
				else
				{
					break;
				}

			}
			// nach rechts unten
			for (int i = 1; i < 9; i++)
			{

				if (((vx + i)<9) && ((vy - i)>0) && (moving->proofNextMove(searchhits, vx, vy, vx + i, vy - i, promo)))
				{
					notfoundfigure = nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx + i, vy - i, moveboard);
				}
				else
				{
					break;
				}

			}
			// nach links unten
			for (int i = 1; i < 9; i++)
			{

				if (((vx - i)>0) && ((vy - i)>0) && (moving->proofNextMove(searchhits, vx, vy, vx - i, vy - i, promo)))
				{
					notfoundfigure = nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx - i, vy - i, moveboard);
				}
				else
				{
					break;
				}

			}
			// nach links oben
			for (int i = 1; i < 9; i++)
			{

				if (((vx - i)>0) && ((vy + i)<9) && (searchhits, moving->proofNextMove(searchhits, vx, vy, vx - i, vy + i, promo)))
				{
					notfoundfigure = nightTest(searchhits, pie, notfoundfigure, moving->moveisHit(), vx, vy, vx - i, vy + i, moveboard);
				}
				else
				{
					break;
				}

			}
		}
	}
	return NULL;
}
