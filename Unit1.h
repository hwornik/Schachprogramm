//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <iostream>
#include <istream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <strsafe.h>


#include "Evaluation.h"
#include "Board.h"
#include "Notation.h"
#include "Communicate.h";
#include "Pieces.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Zuege.h"

#define MAX_THREADS 4
#define BUF_SIZE 255

//---------------------------------------------------------------------------
class CalculusTopTh : public TThread
{
private:
	Board *masterboard;
    Board *myboard;
	int maxthread;
	bool searchmvs;
	Notation *mynot;
	Communicate *mycom;
	clock_t movetime;
	bool *ending;
	Zuege *bestzuege[64];
	bool bewisready[16];
    bool fbewisready[16];
	char zug[64][6];
	DeepSearchTh **threadarr;
	UnderAttackTh **fthreadarr;
    int bewr[64];
	void berechneZugwerte(char *zuga,Board *grboard,int bewr, int *bewertarr,int *taktikarr,bool masterwhitetomove);
	void testeFigurAttacke(Board *myboard,int posx,int posy,bool *isunderattack,bool *fertig);
	Evaluation *myevatst;
	Zuege *bestMove[4];
	Board *ubgboarda[64];
	Evaluation *myeva;
	Pieces *pic;
	int bewertarr[64];
	int tbewertarr[64];
	int taktikarr[64];
protected:
	void __fastcall Execute();
public:
	void setData(Notation *mynot, bool searchmvs, Board* myboard, Communicate *mycom, clock_t movetime);
	__fastcall CalculusTopTh(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
