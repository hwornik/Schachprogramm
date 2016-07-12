//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>

#include "Evaluation.h"

//---------------------------------------------------------------------------
class UnderAttackTh : public TThread
{
private:
	Evaluation *myeva;
	Board *myboard;
	int posx,posy,figwert;
	bool whitetomove,*isnotunderAttack, *fertig;
	Pieces *piec[20],*piece;
protected:
	void __fastcall Execute();
public:
	__fastcall UnderAttackTh(bool CreateSuspended);
    int whichFigureAttacks(Board *myboard,int posx,int posy, bool whitetomove);
	void setData(Board *myboard,int figwert,int posx,int posy,bool whitetomove,bool *isnotunderAttack,bool *fertig);
};
//---------------------------------------------------------------------------
#endif
