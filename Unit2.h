//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <cmath>

#include "Board.h"
#include "EvaluationRekurs.h"
#include "Evaluation.h"
//---------------------------------------------------------------------------
class DeepSearchTh : public TThread
{
private:
	Board *myboard;
	int *bewert;
	int tiefe;
	int *taktikwert;
	bool nullproove;
	bool *isready;
	char *zug;
	int figurenwert;
	bool masterwhitetomove;
protected:
	void __fastcall Execute();
public:
	__fastcall DeepSearchTh(bool CreateSuspended);
	int DeepSearchTh::setData(bool *isready,Board *myboard,int *bewert, int tiefe,int *taktikwert,int figurenwert,bool nullproove, char zug[6],bool masterwhitetomove);
};
//---------------------------------------------------------------------------
#endif
