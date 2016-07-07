#pragma once
#include <string>

#include <istream>

#pragma once
#include <iostream>
#include "Board.h"
#include "Pieces.h"
#include "Movement.h"
#include "Evaluation.h"
#include "EvaluationRekurs.h"
#include "Communicate.h"
#include "Zuege.h"
#include "Notation.h"
#include "Pieces.h"

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include<string.h>
#include <strsafe.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_THREADS 4
#define BUF_SIZE 255


typedef struct MyData {
	Board *myboard;
	Communicate *mycom;
	bool *ending;
	clock_t movetime;
	Notation *mynot;
	bool searchmvs;
	int maxthread;
	bool nullproove;
} MYDATA, *PMYDATA;

typedef struct RMyData {
	Board *myboard;
	bool *ending;
	clock_t movetime;
	Notation *mynot;
	int *mybewert;
	bool *searchmvs;
	bool hasmove;
	int figurenwert;
	bool nullproove;
	bool chkhit;
} RMYDATA, *RPMYDATA;

#define MAX_THREADS 1
class Calculus
{
public:
	Calculus();
	~Calculus();
	int perft(char comand[57]);
	int util_bench(char comand[57]);
	int printeva();
	void treadproc(Notation *mynot, bool searchmvs, Board* myboard, Communicate *mycom, clock_t movetime);
	void stoptreadproc();
private:
	Board *masterboard;
	Board *movingboard;
	// *myeva = 0;
	int tiefe;
	int knoten;
	static DWORD WINAPI MainThredSearch(LPVOID lpParam);
	void ErrorHandler(LPTSTR lpszFunction);
	static int searchrekurs(int startzug, int halbzug, int tiefe, EvaluationRekurs *myeva, Board *movingboard, Board *ourboard, int *bewertung, bool *ending, clock_t movetime, HANDLE hStdout, TCHAR *msgBuf, size_t cchStringSize, DWORD dwChars);
	bool stopsearch;
	HANDLE  hThreadArray[1];
	clock_t movetime;
	Zuege *myzug;
	bool searchmvs;
	static DWORD WINAPI Calculus::MainThredRekurs(LPVOID lpParam);
	PMYDATA pDataArray[1];
	static DWORD WINAPI MainThredLinear(LPVOID lpParam);
	static int getBewertungAllerMoglZuege(Board * myboard, int *bewert, int tiefe,int figurenwert, bool nullproove);
	static int getBewertungHitsZuege(Board * myboard,int *mybewert, int tiefe, int figurenwert);
	static int getBewertungHitsZuegeBadWay(Board * myboard, int * mybewert, int tiefe, int figurenwert);
};

