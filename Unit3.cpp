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
		myeva= new Evaluation();
}
//---------------------------------------------------------------------------
void __fastcall UnderAttackTh::Execute()
{
	// ---- Fügen Sie den Thread-Code hier ein ----
	//*isunderAttack=!myeva->isPosunderAttack(myboard,posx,posy,whitetomove);
	Pieces *aim= new Pieces();
	int figwert=0;
	bool attack=true;
	aim->setName(myboard->getPieceonPos(posx,posy));
	aim->setPos(posx,posy);
	figwert=0;
	int vorz=0;
	while(attack)
	{

		Pieces *pic=myeva->whichFigureAttacks(myboard,posx,posy,whitetomove);
		if(pic==NULL)
		{
			attack=false;
			*isnotunderAttack=true;
			break;
		}
		else
		{
			if((vorz%2)==0)
				figwert-=aim->getWert();
			else
				figwert+=aim->getWert();
			vorz++;
			myboard->makeMove(pic->getPos(true),pic->getPos(false),posx,posy);
			*isnotunderAttack=false;
			aim->init();
			aim->setName(pic->getName());
			aim->setPos(pic->getPos(true),pic->getPos(false));
		}
	}
     std::cout << "Fin Figurwert=" << figwert << "\n";
	if(figwert<0)
	{
	   *isnotunderAttack=false;
	}
	else
	   *isnotunderAttack=true;
	*fertig=true;
}
//---------------------------------------------------------------------------+
void UnderAttackTh::setData(Board *myboard,int posx,int posy,bool whitetomove,bool *isnotunderAttack, bool *fertig)
{
		  this->myboard=myboard;
		  this->posx=posx;
		  this->posy=posy;
		  this->whitetomove=whitetomove;
		  this->isnotunderAttack=isnotunderAttack;
		  this->fertig=fertig;
}
