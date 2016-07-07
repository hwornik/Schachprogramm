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
	*isunderAttack=!myeva->isPosunderAttack(myboard,posx,posy,whitetomove);
	Pieces *aim= new Pieces();
	aim->setName(myboard->getPieceonPos(posx,posy));
	aim->setPos(posx,posy);
	Pieces **pic=myeva->whichFigureAttacks(myboard,posx,posy,whitetomove);
	*fertig=true;
}
//---------------------------------------------------------------------------+
void UnderAttackTh::setData(Board *myboard,int posx,int posy,bool whitetomove,bool *isunderAttack, bool *fertig)
{
		  this->myboard=myboard;
		  this->posx=posx;
		  this->posy=posy;
		  this->whitetomove=whitetomove;
		  this->isunderAttack=isunderAttack;
		  this->fertig=fertig;
}
