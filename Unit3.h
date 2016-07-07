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
	int posx,posy;
	bool whitetomove,*isunderAttack, *fertig;

protected:
	void __fastcall Execute();
public:
	__fastcall UnderAttackTh(bool CreateSuspended);
	void setData(Board *myboard,int posx,int posy,bool whitetomove,bool *isunderAttack,bool *fertig);
};
//---------------------------------------------------------------------------
#endif
