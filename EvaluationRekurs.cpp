#include "stdafx.h"
#include "EvaluationRekurs.h"


EvaluationRekurs::EvaluationRekurs()
{
	moving = new Movement();
	pie = new Pieces();
	moveboard = new Board();
}

EvaluationRekurs::~EvaluationRekurs()
{
	delete moveboard;
	delete moving;
	delete pie;
}

int EvaluationRekurs::computeMovesfigure(int vx, int vy, Board * myboard)
{
	movenr = 0;
	//Movement *moving;
	//moving = new Movement();
	moving->init();
	moving->setBoard(myboard);
	this->noticeMovesandHits(moving->getPieceonPos(vx, vy), moving, vx, vy);
	//delete myboard;
	return 0;
}

bool EvaluationRekurs::makeNextMovesfigure()
{
	//moving = new Movement();
	movesFigure = 0;
	movesFields = 0;
	hits = 0;
	char f, e, c;
	movenr++;
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
		if (e != 'e')
		{
			//bewertung = this->figurenBewertung(moving);
			
				if (isupper(e))
				{
					pie->init();
					pie->setName(e);
					bewertung = -pie->getWert() * 100;;
				}
				else
				{
					pie->init();
					pie->setName(e);
					bewertung = pie->getWert() * 100;;
				}
		}
		else
		{
			bewertung = 0;
		}
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
		return true;
	}
	//delete moving;
	return false;
}

int EvaluationRekurs::getZug(bool xwert)
{
	int i = 1;
	if (xwert)
		i = 0;
	return moveperFigure[movenr][i];
}

Board * EvaluationRekurs::possibleMoves(Board * myboard)
{
	moving->setBoard(myboard);
	//Board *moveboard = new Board();
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

int EvaluationRekurs::getFigurenwert()
{
	return bewertung;
}


bool EvaluationRekurs::noticeMovesandHits(char pie, Movement * moving, int vx, int vy)
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
		if (pie != 'B' && pie != 'b')
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
		if (pie != 'R' && pie != 'r')
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

bool EvaluationRekurs::compMovesandHits(bool searchhits, char pie, Movement * moving, int vx, int vy, Board * moveboard)
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

bool EvaluationRekurs::nightTest(bool searchhits, char pie, bool notfoundfigure, bool ishit, int vx, int vy, int nx, int ny, Board * moveboard)
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

int EvaluationRekurs::figurenBewertung(Movement * moving)
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