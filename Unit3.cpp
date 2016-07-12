//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Unit3.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Wichtig: Methoden und Eigenschaften von Objekten in der VCL können nur
//   in Methoden verwendet werden, die mit 'Synchronize' aufgerufen wurden, z.B.:
//
//      Synchronize(&UpdateCaption);
//
//   wobei UpdateCaption so aussehen könnte:
//
//      void __fastcall UnderAttackTh::UpdateCaption()
//      {
//        Form1->Caption = "Im Thread aktualisiert";
//      }
//---------------------------------------------------------------------------

__fastcall UnderAttackTh::UnderAttackTh(bool CreateSuspended)
	: TThread(CreateSuspended)
{

}
//---------------------------------------------------------------------------
void __fastcall UnderAttackTh::Execute()
{
	// ---- Fügen Sie den Thread-Code hier ein ----
	//*isunderAttack=!myeva->isPosunderAttack(myboard,posx,posy,whitetomove);
	myeva= new Evaluation();
	piece=new Pieces();
	piece->init();
	bool attack=true;
	piece->setName(myboard->getPieceonPos(posx,posy));
	int vorz=0;
	Pieces *pic;
	int wert,min;
    min=piece->getWert();
	while(attack)
	{
		wert=this->whichFigureAttacks(myboard,posx,posy,whitetomove);
		if(wert<0)
		{
			attack=false;
			//*isnotunderAttack=true;
			break;
		}
		else
		{
			if(vorz==0)
				figwert-=min;
			else
			{
				figwert+=min;
                vorz=-1;
			}
			vorz++;
			myboard->makeMove(piece->getPos(true),piece->getPos(false),posx,posy);
			whitetomove=!whitetomove;
			min=wert;
		}
	}
	if(figwert<0)
	{
	   *isnotunderAttack=false;
	}
	else
	   *isnotunderAttack=true;
	*fertig=true;
}
//---------------------------------------------------------------------------+
void UnderAttackTh::setData(Board *myboard,int figwert, int posx,int posy,bool whitetomove,bool *isnotunderAttack, bool *fertig)
{
		  this->myboard=myboard;
		  this->posx=posx;
		  this->posy=posy;
		  this->whitetomove=whitetomove;
		  this->isnotunderAttack=isnotunderAttack;
		  this->fertig=fertig;
          this->figwert=figwert;
}

int UnderAttackTh::whichFigureAttacks(Board *myboard,int posx,int posy, bool whitetomove)
{
	int anzahl=0;
	// Test auf Night
	// Night;
		if (((posx + 2) < 9) && ((posy + 1) < 9))
		{
			if (whitetomove && myboard->getPieceonPos( posx + 2, posy + 1)=='n')
			{
					piec[anzahl]= new Pieces();
					piec[anzahl]->init();
					piec[anzahl]->setName(myboard->getPieceonPos( posx + 2, posy + 1));
					piec[anzahl]->setPos( posx + 2, posy + 1);
					anzahl++;
			}
			else if(!whitetomove && myboard->getPieceonPos( posx + 2, posy + 1)=='N')
			{
					piec[anzahl]= new Pieces();
					piec[anzahl]->init();
					piec[anzahl]->setName(myboard->getPieceonPos( posx + 2, posy + 1));
					piec[anzahl]->setPos( posx + 2, posy + 1);
					anzahl++;
			}

		}
		if (((posx + 2)<9) && ((posy - 1)>0))
		{
			if (whitetomove && myboard->getPieceonPos( posx + 2, posy - 1)=='n')
			{
					piec[anzahl]= new Pieces();
					piec[anzahl]->init();
					piec[anzahl]->setName(myboard->getPieceonPos( posx + 2, posy - 1));
					piec[anzahl]->setPos( posx + 2, posy - 1);
					anzahl++;
			}
			else if(!whitetomove && myboard->getPieceonPos( posx + 2, posy - 1)=='N')
			{
					piec[anzahl]= new Pieces();
					piec[anzahl]->init();
					piec[anzahl]->setName(myboard->getPieceonPos( posx + 2, posy - 1));
					piec[anzahl]->setPos( posx + 2, posy - 1);
					anzahl++;
			}
		}
		if (((posx - 2)>0) && ((posx + 1)<9))
		{
			if (whitetomove && myboard->getPieceonPos( posx - 2, posy + 1)=='n')
			{
					piec[anzahl]= new Pieces();
					piec[anzahl]->init();
					piec[anzahl]->setName(myboard->getPieceonPos( posx - 2, posy + 1));
					piec[anzahl]->setPos( posx - 2, posy + 1);
					anzahl++;
			}
			else if(!whitetomove && myboard->getPieceonPos( posx - 2, posy + 1)=='N')
			{
					piec[anzahl]= new Pieces();
					piec[anzahl]->init();
					piec[anzahl]->setName(myboard->getPieceonPos( posx - 2, posy + 1));
					piec[anzahl]->setPos( posx - 2, posy + 1);
					anzahl++;
			}
		}
		if (((posx - 2)>0) && ((posy - 1)>0))
		{
			if (whitetomove && myboard->getPieceonPos( posx - 2, posy - 1)=='n')
			{
					piec[anzahl]= new Pieces();
					piec[anzahl]->init();
					piec[anzahl]->setName(myboard->getPieceonPos( posx - 2, posy - 1));
					piec[anzahl]->setPos( posx - 2, posy - 1);
					anzahl++;
			}
			else if(!whitetomove && myboard->getPieceonPos( posx - 2, posy - 1)=='N')
			{
					piec[anzahl]= new Pieces();
					piec[anzahl]->init();
					piec[anzahl]->setName(myboard->getPieceonPos( posx - 2, posy - 1));
					piec[anzahl]->setPos( posx - 2, posy - 1);
					anzahl++;
			}
		}
		if (((posx + 1)<9) && ((posy + 2)<9))
		{
			if (whitetomove && myboard->getPieceonPos( posx + 1, posy + 2)=='n')
			{
					piec[anzahl]= new Pieces();
					piec[anzahl]->init();
					piec[anzahl]->setName(myboard->getPieceonPos( posx + 1, posy + 2));
					piec[anzahl]->setPos( posx + 1, posy + 2);
					anzahl++;
			}
			else if(!whitetomove && myboard->getPieceonPos( posx + 1, posy + 2)=='N')
			{
					piec[anzahl]= new Pieces();
					piec[anzahl]->init();
					piec[anzahl]->setName(myboard->getPieceonPos( posx + 1, posy + 2));
					piec[anzahl]->setPos( posx + 1, posy + 2);
					anzahl++;
			}
		}
		if (((posx - 1)>0) && ((posy + 2)<9))
		{
			if (whitetomove && myboard->getPieceonPos( posx - 1, posy + 2)=='n')
			{
					piec[anzahl]= new Pieces();
					piec[anzahl]->init();
					piec[anzahl]->setName(myboard->getPieceonPos( posx - 1, posy + 2));
					piec[anzahl]->setPos( posx - 1, posy + 2);
					anzahl++;
			}
			else if(!whitetomove && myboard->getPieceonPos( posx - 1, posy + 2)=='N')
			{
					piec[anzahl]= new Pieces();
					piec[anzahl]->init();
					piec[anzahl]->setName(myboard->getPieceonPos( posx - 1, posy + 2));
					piec[anzahl]->setPos( posx - 1, posy + 2);
					anzahl++;
			}
		}
		if (((posx - 1)>0) && ((posy - 2)>0))
		{
			if (whitetomove && myboard->getPieceonPos( posx - 1, posy - 2)=='n')
			{
					piec[anzahl]= new Pieces();
					piec[anzahl]->init();
					piec[anzahl]->setName(myboard->getPieceonPos( posx - 1, posy - 2));
					piec[anzahl]->setPos( posx - 1, posy - 2);
					anzahl++;
			}
			else if(!whitetomove && myboard->getPieceonPos( posx - 1, posy - 2)=='N')
			{
					piec[anzahl]= new Pieces();
					piec[anzahl]->init();
					piec[anzahl]->setName(myboard->getPieceonPos( posx - 1, posy - 2));
					piec[anzahl]->setPos( posx - 1, posy - 2);
					anzahl++;
			}
		}
		if (((posx + 1)<9) && ((posx - 2)>0))
		{
			if (whitetomove && myboard->getPieceonPos( posx + 1, posy - 2)=='n')
			{
					piec[anzahl]= new Pieces();
					piec[anzahl]->init();
					piec[anzahl]->setName(myboard->getPieceonPos( posx + 1, posy - 2));
					piec[anzahl]->setPos(posx + 1, posy - 2);
					anzahl++;
			}
			else if(!whitetomove && myboard->getPieceonPos( posx + 1, posy - 2)=='N')
			{
					piec[anzahl]= new Pieces();
					piec[anzahl]->init();
					piec[anzahl]->setName(myboard->getPieceonPos( posx + 1, posy - 2));
					piec[anzahl]->setPos(posx + 1, posy - 2);
					anzahl++;
			}
		}
		// Test auf Turm oder Dame
		// Move Forward
		for (int i = 1; i < 9 - posy; i++)
		{
			if(myboard->getPieceonPos(posx,posy+i)!='e')
			{
				if (whitetomove && ((myboard->getPieceonPos( posx, posy+i)=='r') || (myboard->getPieceonPos( posx, posy+i)=='q') ))
				{
						piec[anzahl]= new Pieces();
						piec[anzahl]->init();
						piec[anzahl]->setName(myboard->getPieceonPos( posx, posy+i));
						piec[anzahl]->setPos( posx, posy+i);
						anzahl++;
				}
				else if (!whitetomove && ((myboard->getPieceonPos( posx, posy+i)=='R') || (myboard->getPieceonPos( posx, posy+i)=='Q') ) )
				{
						piec[anzahl]= new Pieces();
						piec[anzahl]->init();
						piec[anzahl]->setName(myboard->getPieceonPos( posx, posy+i));
						piec[anzahl]->setPos( posx, posy+i);
						anzahl++;
				}
				break;
			}
		}
		// Move right
		for (int i = 1; i < 9 - posx; i++)
		{
			if(myboard->getPieceonPos(posx+i,posy)!='e')
			{
				if (whitetomove && ((myboard->getPieceonPos( posx+i, posy)=='r') || (myboard->getPieceonPos( posx+i, posy)=='q') ))
				{
						piec[anzahl]= new Pieces();
						piec[anzahl]->init();
						piec[anzahl]->setName(myboard->getPieceonPos(posx+i,posy));
						piec[anzahl]->setPos( posx+i, posy);
						anzahl++;
				}
				else if (!whitetomove && ((myboard->getPieceonPos( posx+i, posy)=='R') || (myboard->getPieceonPos( posx+i, posy)=='Q') )  )
				{
						piec[anzahl]= new Pieces();
						piec[anzahl]->init();
						piec[anzahl]->setName(myboard->getPieceonPos(posx+i,posy));
						piec[anzahl]->setPos( posx+i, posy);
						anzahl++;
				}
				break;
			}
		}
		// Move down
		for (int i = 1; i < posy; i++)
		{
			if(myboard->getPieceonPos(posx,posy-i)!='e')
			{
				if (whitetomove && ((myboard->getPieceonPos( posx, posy-i)=='r') || (myboard->getPieceonPos( posx, posy-i)=='q') ))
				{
						piec[anzahl]= new Pieces();
						piec[anzahl]->init();
						piec[anzahl]->setName(myboard->getPieceonPos(posx,posy-i));
						piec[anzahl]->setPos( posx, posy-i);
						anzahl++;
				}
				else if (!whitetomove && ((myboard->getPieceonPos( posx, posy-i)=='R') || (myboard->getPieceonPos( posx, posy-i)=='Q') ))
				{
						piec[anzahl]= new Pieces();
						piec[anzahl]->init();
						piec[anzahl]->setName(myboard->getPieceonPos(posx,posy-i));
						piec[anzahl]->setPos( posx, posy-i);
						anzahl++;
				}
				break;
			}

		}
		// Move left
		for (int i = 1; i < posx; i++)
		{
			if(myboard->getPieceonPos(posx-i,posy)!='e')
			{
				if (whitetomove && ((myboard->getPieceonPos( posx-i, posy)=='r') || (myboard->getPieceonPos( posx-i, posy)=='q') ))
				{
						piec[anzahl]= new Pieces();
						piec[anzahl]->init();
						piec[anzahl]->setName(myboard->getPieceonPos(posx-i,posy));
						piec[anzahl]->setPos(posx-i,posy);
						anzahl++;
				}
				else if (!whitetomove && ((myboard->getPieceonPos( posx-i, posy)=='R') || (myboard->getPieceonPos( posx-i, posy)=='Q') )  )
				{
						piec[anzahl]= new Pieces();
						piec[anzahl]->init();
						piec[anzahl]->setName(myboard->getPieceonPos(posx-i,posy));
						piec[anzahl]->setPos(posx-i,posy);
						anzahl++;
				}
				break;
			}

		}
		// Test auf Läufer oder Dame
		// nach rechts oben
		for (int i = 1; i < 9; i++)
		{

			if (((posx + i)<9) && ((posy + i)<9) && (myboard->getPieceonPos(posx+i,posy+i)!='e' ))
			{
				if (whitetomove && ((myboard->getPieceonPos( posx+i, posy+i)=='b') || (myboard->getPieceonPos( posx+i, posy+i)=='q') ) )
				{
						piec[anzahl]= new Pieces();
						piec[anzahl]->init();
						piec[anzahl]->setName(myboard->getPieceonPos(posx+i,posy+i));
						piec[anzahl]->setPos(posx+i,posy+i);
						anzahl++;
				}
				else if (!whitetomove && ((myboard->getPieceonPos( posx+i, posy+i)=='B') || (myboard->getPieceonPos( posx+i, posy+i)=='Q') ) )
				{
						piec[anzahl]= new Pieces();
						piec[anzahl]->init();
						piec[anzahl]->setName(myboard->getPieceonPos(posx+i,posy+i));
						piec[anzahl]->setPos(posx+i,posy+i);
						anzahl++;
				}
				break;
			}

		}
		// nach rechts unten
		for (int i = 1; i < 9; i++)
		{

			if (((posx + i)<9) && ((posy - i)>0) && (myboard->getPieceonPos(posx+i,posy-i)!='e' ))
			{
				if (whitetomove && ((myboard->getPieceonPos( posx+i, posy-i)=='b') || (myboard->getPieceonPos( posx+i, posy-i)=='q') ))
				{
						piec[anzahl]= new Pieces();
						piec[anzahl]->init();
						piec[anzahl]->setName(myboard->getPieceonPos(posx+i,posy-i));
						piec[anzahl]->setPos( posx+i, posy-i);
						anzahl++;
				}
				else if (!whitetomove && ((myboard->getPieceonPos( posx+i, posy-i)=='B') || (myboard->getPieceonPos( posx+i, posy-i)=='Q') )  )
				{
						piec[anzahl]= new Pieces();
						piec[anzahl]->init();
						piec[anzahl]->setName(myboard->getPieceonPos(posx+i,posy-i));
						piec[anzahl]->setPos( posx+i, posy-i);
						anzahl++;
				}
				break;
			}

		}
		// nach links unten
		for (int i = 1; i < 9; i++)
		{
			if (((posx - i)> 0) && ((posy - i)>0) && (myboard->getPieceonPos(posx-i,posy-i)!='e' ))
			{
				if (whitetomove && ((myboard->getPieceonPos( posx-i, posy-i)=='b') || (myboard->getPieceonPos( posx-i, posy-i)=='q') ))
				{
						piec[anzahl]= new Pieces();
						piec[anzahl]->init();
						piec[anzahl]->setName(myboard->getPieceonPos(posx-i,posy-i));
						piec[anzahl]->setPos(posx-i,posy-i);
						anzahl++;
				}
				else if (!whitetomove && ((myboard->getPieceonPos( posx-i, posy-i)=='B') || (myboard->getPieceonPos( posx-i, posy-i)=='Q') ) )
				{
						piec[anzahl]= new Pieces();
						piec[anzahl]->init();
						piec[anzahl]->setName(myboard->getPieceonPos(posx-i,posy-i));
						piec[anzahl]->setPos(posx-i,posy-i);
						anzahl++;
				}
				break;
			}
		}
		// nach links oben
		for (int i = 1; i < 9; i++)
		{
			if (((posx - i)>0) && ((posy + i)<9) && (myboard->getPieceonPos(posx-i,posy+i)!='e' ))
			{
				if (whitetomove && ((myboard->getPieceonPos( posx-i, posy+i)=='b') || (myboard->getPieceonPos( posx-i, posy+i)=='q') ))
				{
						piec[anzahl]= new Pieces();
						piec[anzahl]->init();
						piec[anzahl]->setName(myboard->getPieceonPos(posx-i,posy+i));
						piec[anzahl]->setPos(posx-i,posy+i);
						anzahl++;
				}
				else if (!whitetomove && ((myboard->getPieceonPos( posx-i, posy+i)=='B') || (myboard->getPieceonPos( posx-i, posy+i)=='Q') ) )
				{
						piec[anzahl]= new Pieces();
						piec[anzahl]->init();
						piec[anzahl]->setName(myboard->getPieceonPos(posx-i,posy+i));
						piec[anzahl]->setPos(posx-i,posy+i);
						anzahl++;
				}
				break;
			}
		}
		// Test auf Bauer
		if ((posx+1<9 && posy+1<9) && ((whitetomove && ((myboard->getPieceonPos( posx+1, posy+1)=='p') ))))
		{
				piec[anzahl]= new Pieces();
				piec[anzahl]->init();
				piec[anzahl]->setName(myboard->getPieceonPos(posx+1,posy+1));
				piec[anzahl]->setPos(posx+1,posy+1);
				anzahl++;
		}
		else if (whitetomove && (posx-1>0 && posy+1<9) && ((myboard->getPieceonPos( posx-1, posy+1)=='p') ) )
		{
				piec[anzahl]= new Pieces();
				piec[anzahl]->init();
				piec[anzahl]->setName(myboard->getPieceonPos(posx-1,posy+1));
				piec[anzahl]->setPos(posx-1,posy+1);
				anzahl++;
		}
		else if (!whitetomove && (posx-1>0 && posy-1>0) &&((myboard->getPieceonPos( posx-1, posy-1)=='P') ) )
		{
				piec[anzahl]= new Pieces();
				piec[anzahl]->init();
				piec[anzahl]->setName(myboard->getPieceonPos(posx-1,posy-1));
				piec[anzahl]->setPos(posx-1,posy-1);
				anzahl++;
		}
		else if (!whitetomove && (posx+1<9 && posy-1>0) && ((myboard->getPieceonPos( posx+1, posy-1)=='P') )  )
		{
				piec[anzahl]= new Pieces();
				piec[anzahl]->init();
				piec[anzahl]->setName(myboard->getPieceonPos(posx+1,posy-1));
				piec[anzahl]->setPos(posx+1,posy-1);
				anzahl++;
		}
		// Test auf König
		if((posy+1<9) && ((whitetomove && (myboard->getPieceonPos( posx, posy+1)=='K')) || (!whitetomove && (myboard->getPieceonPos( posx, posy+1)=='k') )))
		{
				piec[anzahl]= new Pieces();
				piec[anzahl]->init();
				piec[anzahl]->setName(myboard->getPieceonPos(posx,posy+1));
				piec[anzahl]->setPos(posx,posy+1);
				anzahl++;
		}
		else if ((posx+1<9 && posy+1<9) && ((whitetomove && (myboard->getPieceonPos( posx+1, posy+1)=='K')) || (!whitetomove && (myboard->getPieceonPos( posx+1, posy+1)=='k') )))
		{
				piec[anzahl]= new Pieces();
				piec[anzahl]->init();
				piec[anzahl]->setName(myboard->getPieceonPos(posx+1,posy+1));
				piec[anzahl]->setPos(posx+1,posy+1);
				anzahl++;
		}
		else if ((posx+1<9) && ((whitetomove && (myboard->getPieceonPos( posx+1, posy)=='K')) || (!whitetomove && (myboard->getPieceonPos( posx+1, posy)=='k') )))
		{
				piec[anzahl]= new Pieces();
				piec[anzahl]->init();
				piec[anzahl]->setName(myboard->getPieceonPos(posx+1,posy));
				piec[anzahl]->setPos(posx+1,posy);
				anzahl++;
		}
		else if ((posx+1<9 && posy-1>0) && ((whitetomove && (myboard->getPieceonPos( posx+1, posy-1)=='K')) || (!whitetomove && (myboard->getPieceonPos( posx+1, posy-1)=='k') )))
		{
				piec[anzahl]= new Pieces();
				piec[anzahl]->init();
				piec[anzahl]->setName(myboard->getPieceonPos(posx+1,posy-1));
				piec[anzahl]->setPos(posx+1,posy-1);
				anzahl++;
		}
		else if ((posy-1>0) && ((whitetomove && (myboard->getPieceonPos( posx, posy-1)=='K')) || (!whitetomove && (myboard->getPieceonPos( posx, posy-1)=='k') )))
		{
				piec[anzahl]= new Pieces();
				piec[anzahl]->init();
				piec[anzahl]->setName(myboard->getPieceonPos(posx,posy-1));
				piec[anzahl]->setPos(posx,posy-1);
				anzahl++;
		}
		else if ((posx-1>0 && posy-1>0) && ((whitetomove && (myboard->getPieceonPos( posx-1, posy-1)=='K')) || (!whitetomove && (myboard->getPieceonPos( posx-1, posy-1)=='k') )))
		{
				piec[anzahl]= new Pieces();
				piec[anzahl]->init();
				piec[anzahl]->setName(myboard->getPieceonPos(posx-1,posy-1));
				piec[anzahl]->setPos(posx-1,posy-1);
				anzahl++;
		}
		else if ((posx-1>0) && ((whitetomove && (myboard->getPieceonPos( posx-1, posy)=='K')) || (!whitetomove && (myboard->getPieceonPos( posx-1, posy)=='k') )))
		{
				piec[anzahl]= new Pieces();
				piec[anzahl]->init();
				piec[anzahl]->setName(myboard->getPieceonPos(posx-1,posy));
				piec[anzahl]->setPos(posx-1,posy);
				anzahl++;
		}
		else if ((posx-1>0 && posy+1<9) && ((whitetomove && (myboard->getPieceonPos( posx-1, posy+1)=='K')) || (!whitetomove && (myboard->getPieceonPos( posx-1, posy+1)=='k') )))
		{
				piec[anzahl]= new Pieces();
				piec[anzahl]->init();
				piec[anzahl]->setName(myboard->getPieceonPos(posx-1,posy+1));
				piec[anzahl]->setPos(posx-1,posy+1);
				anzahl++;
		}
		piece->init();
		if(anzahl>0)
		{
			int min=100000;
			for(int i=0;i<anzahl;i++)
			{
				if(min > piec[i]->getWert())
				{
					min=piec[i]->getWert();
					piece->setName(piec[i]->getName());
					piece->setPos(piec[i]->getPos(true),piec[i]->getPos(false));
				}
			}
            return min;
		}
		else
            return -1;
}
