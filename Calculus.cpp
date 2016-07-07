#include "stdafx.h"
#include "Calculus.h"


Calculus::Calculus()
{
	masterboard = 0;
	movingboard = 0;
	hThreadArray[0]=0;
	pDataArray[0] = NULL;
	tiefe = 8;
    knoten = 10;
}


Calculus::~Calculus()
{
}


int Calculus::perft(char comand[57])
{
	return 0;
}

int Calculus::util_bench(char comand[57])
{
	return 0;
}

int Calculus::printeva()
{
	return 0;
}

void Calculus::stoptreadproc()
{
	this->stopsearch = true;
	WaitForSingleObject(hThreadArray[0], INFINITE);
	CloseHandle(hThreadArray[0]);
	if (pDataArray[0] != NULL)
	{
		HeapFree(GetProcessHeap(), 0, pDataArray[0]);
		pDataArray[0] = NULL;    // Ensure address is not reused.
	}
}

void Calculus::treadproc(Notation *mynot, bool searchmvs, Board* myboard, Communicate *mycom, clock_t movetime)
{
	this->myzug = 0;
	this->searchmvs = searchmvs;
	this->stopsearch = false;
	DWORD   dwThreadIdArray[1];

	// Create MAX_THREADS worker threads.

	// Allocate memory for thread data.
	
	pDataArray[0] = (PMYDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
		sizeof(MYDATA));

	if (pDataArray[0] == NULL)
	{
		// If the array allocation fails, the system is out of memory
		// so there is no point in trying to print an error message.
		// Just terminate execution.
		ExitProcess(2);
	}

	// Generate unique data for each thread to work with.
	pDataArray[0]->myboard = myboard;
	pDataArray[0]->mycom = mycom;
	pDataArray[0]->ending = &this->stopsearch;
	pDataArray[0]->movetime = this->movetime;
	pDataArray[0]->mynot = mynot;
	pDataArray[0]->searchmvs = this->searchmvs;
	pDataArray[0]->maxthread = 1;
	// Create the thread to begin execution on its own.

	hThreadArray[0] = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size
		MainThredSearch,       // thread function name
		pDataArray[0],          // argument to thread function
		0,                      // use default creation flags
		&dwThreadIdArray[0]);   // returns the thread identifier


							 // Check the return value for success.
							 // If CreateThread fails, terminate execution.
							 // This will automatically clean up threads and memory.

	if (hThreadArray[0] == NULL)
	{
		//pDataArray[0]->mycom->sendmoves("0000", "0000");
		ErrorHandler(TEXT("CreateThread"));
		ExitProcess(3);

	}

	//WaitForSingleObject(hThreadArray,INFINITE);
	// Wait until all threads have terminated.

	 WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);

	// Close all thread handles and free memory allocations.

	for(int i=0; i<MAX_THREADS; i++)
	{
	CloseHandle(hThreadArray[i]);
	if(pDataArray[i] != NULL)
	{
	HeapFree(GetProcessHeap(), 0, pDataArray[i]);
	pDataArray[i] = NULL;    // Ensure address is not reused.
	}
	}


}

DWORD WINAPI Calculus::MainThredSearch(LPVOID lpParam)
{

	HANDLE hStdout;
	PMYDATA pDataArray;

	TCHAR msgBuf[BUF_SIZE];
	size_t cchStringSize;
	DWORD dwChars;

	// Make sure there is a console to receive output results.

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdout == INVALID_HANDLE_VALUE)
		return 1;

	// Cast the parameter to the correct data type.
	// The pointer is known to be valid because
	// it was checked for NULL before the thread was created.

	pDataArray = (PMYDATA)lpParam;

	Evaluation *myeva = new Evaluation();
	Board *masterboard = pDataArray->myboard;
	Board *movingboard = myeva->possibleMoves(masterboard);
	Pieces *pic = new Pieces();
	//myeva->printStats();
	int grenze = myeva->getMovesFigures();
	char f;
	int moves = -1, hits = -1, bewegfig = -1, kontrol = -1, wert = 0;
	int maxthread=pDataArray->maxthread;
	char *zug;
	zug = new char[6];
	char *zug2;
	zug2 = new char[6];
	int zi = 0, zugnr;
	zug = "0000";
	zug2 = "0000";
	char str[100];
	int *tbewertung, *ttaktik;
	int taktik = 0, bewertt=0;
	tbewertung = &bewertt;
	ttaktik = &taktik;
	int tiefe = 0, startzug = 0, halbzug = 0;
	bool movewhite = pDataArray->myboard->getwhitetoMove();
	zugnr = masterboard->getZugNr();
	//Thread
	RPMYDATA rpDataArray[MAX_THREADS];
	DWORD   dwThreadIdArray[MAX_THREADS];
	HANDLE  hThreadArray[MAX_THREADS];
	int aktindex = 0;
	int aktberech[16];
	int bewertarr[16];
	int tbewertarr[16];
	int taktikarr[16];
	bool bewisready[16];
	Board *zwboard = masterboard->copyBoard();
	char ok;
	if (movewhite)
	{
		zugnr++;
		wert = 0 - 8 * 1 - 4 * 3 - 2 * 5 - 9 - 9999 - 1;
		wert *= 100;
	}
	else
	{
		wert = 8 * 1 + 4 * 3 + 2 * 5 + 9 + 9999 + 1;
		wert *= 100;
	}
	if (pDataArray->searchmvs)
	{
		for (int i = 1; i <= pDataArray->mynot->getAktZugNr(); i++)
		{
			Zuege *zg = pDataArray->mynot->getZugNr(i);
			if (zg == 0)
			{
				pDataArray->mycom->sendmoves(zug, zug2);
				return 0;
			}
			Board *ubgboard = pDataArray->myboard->copyBoard();
			myeva->makeThisMovesfigure(ubgboard, zg->getWhitePiece(true, true), zg->getWhitePiece(true, false), zg->getWhitePiece(false, true), zg->getWhitePiece(false, false));
			delete ubgboard;
			// Print the parameter values using thread-safe functions.
			TCHAR* b = zg->getWhiteMove();
			StringCchPrintf(msgBuf, BUF_SIZE, TEXT("info currentmovenr %d currentmove %s score cp%d time %d\n"),
				zugnr, b, myeva->getFigurenwert(), clock() - pDataArray->movetime);
			StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
			WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);
			//Print Thread safe ende
			//sprintf(str, "info currentmovenr %d currentmove %s score cp%d time %d", zugnr, zg->getWhiteMove(), myeva->getFigurenwert(), clock() - pDataArray->movetime);
			//pDataArray->mycom->send(str);
			bewertarr[aktindex] = (myeva->getFigurenwert() + bewertarr[aktindex]) / 2;
			if ((movewhite && wert < bewertarr[aktindex]) || (!movewhite && wert > bewertarr[aktindex]))
			{
				wert = bewertarr[aktindex];
				kontrol = myeva->getKontrolFields();
				bewegfig = myeva->getMovesFigures();
				hits = myeva->getHits();
				moves = myeva->getZuege();
				zug2 = zug;
				zug = zg->getWhiteMove();
			}
			else if (wert == bewertarr[aktindex] && ((kontrol + hits + bewegfig + moves) < (myeva->getKontrolFields()
				+ myeva->getHits() + myeva->getMovesFigures() + myeva->getZuege())))
			{
				wert = bewertarr[aktindex];
				kontrol = myeva->getKontrolFields();
				bewegfig = myeva->getMovesFigures();
				hits = myeva->getHits();
				moves = myeva->getZuege();
				zug2 = zug;
				zug = zg->getWhiteMove();
			}
			if (*pDataArray->ending)
			{
				pDataArray->mycom->sendmoves(zug, zug2);
				return 0;
			}
		}
	}
	else
	{
		for (int i = 1; i < 9; i++)// my next move
		{
			for (int j = 1; j < 9; j++)
			{
				f = movingboard->getPieceonPos(i, j);
				if (f != 'e' && f != 'x' && f != 'm' && f != 'h')
				{
					Board *ubgboard = pDataArray->myboard->copyBoard();
					myeva->computeMovesfigure(i, j, ubgboard);
					//delete ubgboard;
					while (myeva->makeNextMovesfigure())
					{
						//sprintf(str, "info currentmovenr %d currentmove %s score cp%d time %d", zugnr, myeva->getZugStr(), myeva->getFigurenwert(), clock() - pDataArray->movetime);
						//pDataArray->mycom->send(str);
						//myeva->printStats();
						//bewertarr[aktindex] = myeva->getFigurenwert();
						taktikarr[aktindex] = myeva->getKontrolFields()
							+ myeva->getHits() + myeva->getMovesFigures() + myeva->getZuege();
						//// Threads start
						ok= zwboard->maketestmove(i, j, myeva->getZug(true), myeva->getZug(false));// My Move on Board!!!!!!
						zwboard->setwhitetoMove(!zwboard->getwhitetoMove());
						
						int pw = 0;
						if (ok != 'e')
						{
							pic->init();
							pic->setName(ok);
							pw = pic->getWert()*100;
						}
						//Board *zwboard = masterboard->copyBoard();
						//zwboard->makeMove(i, j, myeva->getZug(true), myeva->getZug(false));
						// erzeuge Daten
						    for( int ix=0; ix<MAX_THREADS; ix++ )
							{
								// Allocate memory for thread data.

								rpDataArray[ix] = (RPMYDATA) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
										sizeof(RMYDATA));

								if( rpDataArray[ix] == NULL )
								{
								   // If the array allocation fails, the system is out of memory
								   // so there is no point in trying to print an error message.
								   // Just terminate execution.
									ExitProcess(2);
								}
								// Generate unique data for each thread to work with.
								bewertarr[ix] = 0;
								bewisready[ix] = false;
								
								rpDataArray[ix]->ending = pDataArray->ending;
								rpDataArray[ix]->movetime=pDataArray->movetime;
								rpDataArray[ix]->myboard = zwboard;
								rpDataArray[ix]->mybewert = &tbewertarr[ix];
								rpDataArray[ix]->mynot = new  Notation();
								rpDataArray[ix]->searchmvs = &bewisready[ix];
								rpDataArray[ix]->hasmove = masterboard->getwhitetoMove();
								rpDataArray[ix]->figurenwert = myeva->getFigurenwert()+pw;
								rpDataArray[ix]->nullproove = true;
								if (myeva->getHits() > 0)
									rpDataArray[ix]->chkhit = true;
								else
									rpDataArray[ix]->chkhit = false;
								// Create the thread to begin execution on its own.
								// start calculating with my next possible move
								hThreadArray[ix] = CreateThread(
									NULL,                   // default security attributes
									0,                      // use default stack size  
									MainThredRekurs,       // thread function name
									rpDataArray[ix],          // argument to thread function 
									0,                      // use default creation flags 
									&dwThreadIdArray[ix]);   // returns the thread identifier 


															// Check the return value for success.
															// If CreateThread fails, terminate execution. 
															// This will automatically clean up threads and memory. 

								if (hThreadArray[ix] == NULL)
								{
									
									ExitProcess(3);
								}
							} // End of main thread creation loop.
							WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);
							zwboard->takebacktestmove(i, j, myeva->getZug(true), myeva->getZug(false),ok);
							zwboard->setwhitetoMove(!zwboard->getwhitetoMove());
							// Close all thread handles and free memory allocations.

							for (int ix = 0; ix<MAX_THREADS; ix++)
							{
								CloseHandle(hThreadArray[ix]);
								if (rpDataArray[ix] != NULL)
								{
									HeapFree(GetProcessHeap(), 0, rpDataArray[ix]);
									rpDataArray[ix] = NULL;    // Ensure address is not reused.
								}
							}
							// Rekursive Suche start
							/*startzug = zugnr;
							if (masterboard->getwhitetoMove())
								halbzug = 0;
							else
								halbzug = 1;
							Board *zwboard = masterboard->copyBoard();
							zwboard->makeMove(i, j, myeva->getZug(true), myeva->getZug(false));
							EvaluationRekurs *nxeva;
							nxeva = new EvaluationRekurs();
							Board *nzeboard = nxeva->possibleMoves(zwboard);
							searchrekurs(startzug, halbzug, tiefe, nxeva, nzeboard, zwboard, tbewertung, pDataArray->ending, pDataArray->movetime, hStdout, msgBuf, cchStringSize, dwChars);
							delete nxeva;
							delete nzeboard;
							delete zwboard;
							*/
						//rekursive Suche ende
						//threds Ende
						//printf("bewer akt %d thr %d\n",myeva->getFigurenwert(), tbewertarr[aktindex]);
						//bewertarr[aktindex] += (myeva->getFigurenwert() + tbewertarr[aktindex]) / 2;
						// Print the parameter values using thread-safe functions.
							//printf("w %d taktik: %d : %d\n",wert,taktik, taktikarr[aktindex]);
							bewertarr[aktindex] = tbewertarr[aktindex];
							printf("Taktik %d Kf %d H %dMov  %d Zuege %d\n", taktikarr[aktindex], myeva->getKontrolFields(),myeva->getHits(),
								myeva->getMovesFigures(),myeva->getZuege());
						TCHAR* b = myeva->getZugStr();
						StringCchPrintf(msgBuf, BUF_SIZE, TEXT("\ninfo currentmovenr %d currentmove %s score cp%d time %d\n\n"),
							zugnr, b, bewertarr[aktindex], clock() - pDataArray->movetime);
						StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
						WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);
						
						//Print Thread safe ende
						if ((movewhite && wert < bewertarr[aktindex]) || (!movewhite && wert > bewertarr[aktindex]))
						{
							wert = bewertarr[aktindex];
							taktik = taktikarr[aktindex];
							zug2 = zug;
							zug = myeva->getZugStr();
						}
						else if ((wert == bewertarr[aktindex]) && (taktik < taktikarr[aktindex]))
						{
							//printf("taktik2: %d\n", taktikarr[aktindex]);
							wert = bewertarr[aktindex];
							taktik = taktikarr[aktindex];
							zug2 = zug;
							zug = myeva->getZugStr();
						}
					}
					if (*pDataArray->ending)
					{
						pDataArray->mycom->sendmoves(zug, zug2);
						return 0;
					}
				}
			}
		}
	}
	// Print the parameter values using thread-safe functions.
	StringCchPrintf(msgBuf, BUF_SIZE, TEXT("info score cp%d time %d\n"),
	wert, clock() - pDataArray->movetime);
	StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
	WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);
	//Print Thread safe ende
	pDataArray->mycom->sendmoves(zug, zug2);
	delete myeva;
	delete masterboard;
	delete zwboard;
	//delete movingboard;
	//	HeapFree(GetProcessHeap(), 0, pDataArray);
	//	pDataArray = NULL;    // Ensure address is not reused.

	return true;
}


void Calculus::ErrorHandler(LPTSTR lpszFunction)
{
	// Retrieve the system error message for the last-error code.

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message.

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	/*   StringCchPrintf((LPTSTR)lpDisplayBuf,
	LocalSize(lpDisplayBuf) / sizeof(TCHAR),
	TEXT("%s failed with error %d: %s"),
	/       lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR) lpDisplayBuf, TEXT("Error"), MB_OK);
	*/
	// Free error-handling buffer allocations.

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}

int Calculus::searchrekurs(int startzug,int halbzug, int tiefe, EvaluationRekurs *myeva,Board *movingboard, Board *ourboard,int *bewertung, bool *ending, clock_t movetime, HANDLE hStdout, TCHAR *msgBuf, size_t cchStringSize, DWORD dwChars)
{
	//printf("startrekurs\n");
	//USES_CONVERSION;
	halbzug++;
	if (halbzug == 2)
	{
		startzug++;
		halbzug = 0;
	}
	tiefe++;
	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			char f = movingboard->getPieceonPos(i, j);
			if (f != 'e' && f != 'x' && f != 'm' && f != 'h')
			{
				//Board *ubgboard = ourboard->copyBoard();
				myeva->computeMovesfigure(i, j, ourboard);
				//delete ubgboard;
				while (myeva->makeNextMovesfigure())
				{
					// Print the parameter values using thread-safe functions.
					/*TCHAR* b = A2T(myeva->getZugStr());
					StringCchPrintf(msgBuf, BUF_SIZE, TEXT("info currentmovenr %d currentmove %s score cp%d time %d\n"),
						startzug, b, myeva->getFigurenwert(), clock() - movetime);
					StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
					WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);
					//Print Thread safe ende
					//sprintf(str, "info currentmovenr %d currentmove %s score cp%d time %d", zugnr, myeva->getZugStr(), myeva->getFigurenwert(), clock() - pDataArray->movetime);
					//pDataArray->mycom->send(str);
					//myeva->printStats();*/
					*bewertung = (myeva->getFigurenwert() + *bewertung) / 2;
						//printf("neues Board\n");
						//Board *zwboard = ourboard->copyBoard();
						//printf("make move to %d %d\n", myeva->getZug(true), myeva->getZug(false));
						Board *newboard = ourboard->copyBoard();
						newboard->makeMove(i, j, myeva->getZug(true), myeva->getZug(false));
						EvaluationRekurs *nxeva;
						nxeva = new EvaluationRekurs();
						Board *ubgboard;
						ubgboard = nxeva->possibleMoves(newboard);
						if (tiefe < 3 || *ending)
						{
							searchrekurs(startzug, halbzug, tiefe,nxeva, ubgboard, newboard, bewertung, ending, movetime, hStdout, msgBuf, cchStringSize, dwChars);
						}
						delete nxeva;
						delete ubgboard;
						delete newboard;
					}
				}
			}
		}
	return 0;
}

DWORD WINAPI Calculus::MainThredRekurs(LPVOID lpParam)
{
	HANDLE hStdout;
	RPMYDATA pDataArray;

	TCHAR msgBuf[BUF_SIZE];
	size_t cchStringSize;
	DWORD dwChars;

	// Make sure there is a console to receive output results.

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdout == INVALID_HANDLE_VALUE)
		return 1;

	// Cast the parameter to the correct data type.
	// The pointer is known to be valid because
	// it was checked for NULL before the thread was created.

	pDataArray = (RPMYDATA)lpParam;
	int startzug=0, halbzug=0;

	int tiefe = 2;
	int knt;
	startzug = 0;
	if (pDataArray->chkhit)//pDataArray->chkhit)
		knt = getBewertungHitsZuegeBadWay(pDataArray->myboard, pDataArray->mybewert, tiefe, pDataArray->figurenwert);
	else
		knt=getBewertungAllerMoglZuege(pDataArray->myboard, pDataArray->mybewert, tiefe, pDataArray->figurenwert, pDataArray->nullproove);
	//printf(" Zugbew %d ", *pDataArray->mybewert);
	//searchrekurs(startzug, halbzug, tiefe, nxeva, nzeboard, pDataArray->myboard, pDataArray->mybewert, pDataArray->ending, pDataArray->movetime, hStdout, msgBuf, cchStringSize, dwChars);
	//delete nxeva;
	//delete nzeboard;
	*pDataArray->searchmvs = true;
	printf("%d Knoten\n",knt);
	return 0;
}

DWORD WINAPI Calculus::MainThredLinear(LPVOID lpParam)
{

	HANDLE hStdout;
	RPMYDATA pDataArray;

	TCHAR msgBuf[BUF_SIZE];
	size_t cchStringSize;
	DWORD dwChars;

	// Make sure there is a console to receive output results.

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdout == INVALID_HANDLE_VALUE)
		return 1;

	// Cast the parameter to the correct data type.
	// The pointer is known to be valid because
	// it was checked for NULL before the thread was created.

	pDataArray = (RPMYDATA)lpParam;
	int startzug = 0, halbzug = 0;

	int tiefe = 0;

	startzug = 0;
	int runden = 3;
	char f;
	//EvaluationRekurs *myeva;
	//myeva = new EvaluationRekurs();
	//Board *movingboard = pDataArray->myboard;
	//Board *movingboard = myeva->possibleMoves(pDataArray->myboard);
	getBewertungAllerMoglZuege(pDataArray->myboard->copyBoard(), pDataArray->mybewert, tiefe,pDataArray->figurenwert, pDataArray->nullproove);
	//printf(" Zugbew %d ", *pDataArray->mybewert);

	//delete myeva;
	//delete movingboard;
	//*pDataArray->searchmvs = true;
	//return 0;
}

int Calculus::getBewertungAllerMoglZuege(Board *myboard,int *bewert, int tiefe,int figurenwert,bool nullproove)
{
	int ni, nj, ni2, nj2, ni3, nj3, ni4, nj4, knt = 0;
	int wert1=0, wert2=0, wert3=0,wert4=0;
	EvaluationRekurs *myeva= new EvaluationRekurs();
	int figwert1 = 0, figwert2 = 0, figwert3 = 0, figwert4 = 0;
	EvaluationRekurs *myeva2, *myeva3,*myeva4;
	myeva3 = new EvaluationRekurs();
	myeva2 = new EvaluationRekurs();
	myeva4 = new EvaluationRekurs();
	Board *movingboard, *movingboard2, *movingboard3,*movingboard4;
	//Board *myboard2, *myboard3;
	bool whitetomove = !myboard->getwhitetoMove();
	bool round1 = false, round2 = false, round3 = false, round4 = false;
	char f, o, z,f2,o2,f3,o3,f4,o4;
	int min = 0;
	int max = 0;
	int tst=0;
	int grup =1, grdown = -1;
	int summe1= 0, summe2 = 0, summe3 = 0;;
	if (nullproove)
	{
		grup = 0;
		grdown = 0;
	}
	figwert1 = figurenwert;
	movingboard = myeva->possibleMoves(myboard);
	for (int i = 1; i < 9; i++)// Loop for Oponent;
	{
		for (int j = 1; j < 9; j++)
		{
			f = movingboard->getPieceonPos(i, j);
			if (f != 'e' && f != 'x' && f != 'm' && f != 'h')
			{
				myeva->computeMovesfigure(i, j, myboard);
				while (myeva->makeNextMovesfigure())
				{
					tst = myeva->getFigurenwert();
					if (!whitetomove)
					{
						if (tst < grup)
							break;
					}
					else
					{
						if (tst > grdown)
							break;
					}
					round1 = true;
					wert1 = tst+figwert1;
					knt++;
					summe1 = (summe1 + wert1) / 2;
					//printf(" Zug %d bew %d ",i*10+j, *bewert);
					ni = myeva->getZug(true);
					nj = myeva->getZug(false);
					o = myboard->maketestmove(i, j, ni, nj);
					myboard->setwhitetoMove(!myboard->getwhitetoMove());
					figwert2 = tst+figwert1;
					movingboard2 = myeva2->possibleMoves(myboard);
					for (int i2 = 1; i2 < 9; i2++)// Loop for Me;
					{
						for (int j2 = 1; j2 < 9; j2++)
						{
							f2 = movingboard2->getPieceonPos(i2, j2);
							if (f2 != 'e' && f2 != 'x' && f2 != 'm' && f2 != 'h')
							{
								myeva2->computeMovesfigure(i2, j2, myboard);
								while (myeva2->makeNextMovesfigure())
								{
									tst = myeva->getFigurenwert();
									if (whitetomove)
									{
										if (tst < grup)
											break;
									}
									else
									{
										if (tst > grdown)
											break;
									}
									round2 = true;
									wert2 = tst+figwert2;
									knt++;
									summe2 = (wert1 + wert2 + summe2) / 2;
									ni2 = myeva2->getZug(true);
									nj2 = myeva2->getZug(false);
									o2 = myboard->maketestmove(i2, j2, ni2, nj2);
									myboard->setwhitetoMove(!myboard->getwhitetoMove());
									movingboard3 = myeva3->possibleMoves(myboard);
									figwert3 = tst + figwert2;
									for (int i3 = 1; i3 < 9; i3++)// Loop for Oponent;
									{
										for (int j3 = 1; j3 < 9; j3++)
										{
											f3 = movingboard3->getPieceonPos(i3, j3);
											if (f3 != 'e' && f3 != 'x' && f3 != 'm' && f3 != 'h')
											{
												myeva3->computeMovesfigure(i3, j3, myboard);
												while (myeva3->makeNextMovesfigure())
												{
													tst = myeva->getFigurenwert();
													if (!whitetomove)
													{
														if (tst < grup)
															break;
													}
													else
													{
														if (tst > grdown)
															break;
													}
													round3 = true;
													wert3 =tst+figwert3;
													summe3 = (wert1 + wert2 + wert3 + summe3) / 2;
													knt++;
													if (summe3 > max)
														max = summe3;
													else if (min < summe3)
														min = summe3;
													
													/*ni3 = myeva3->getZug(true);
													nj3 = myeva3->getZug(false);
													o3 = myboard->maketestmove(i3, j3, ni3, nj3);
													myboard->setwhitetoMove(!myboard->getwhitetoMove());
													movingboard4 = myeva4->possibleMoves(myboard);
													figwert4 = tst + figwert3;
													for (int i4 = 1; i4 < 9; i4++)// Loop for Me;
													{
														for (int j4 = 1; j4 < 9; j4++)
														{
															f4 = movingboard4->getPieceonPos(i4, j4);
															if (f4 != 'e' && f4 != 'x' && f4 != 'm' && f4 != 'h')
															{
																myeva4->computeMovesfigure(i4, j4, myboard);
																while (myeva4->makeNextMovesfigure())
																{
																	tst = myeva4->getFigurenwert();
																	if (whitetomove)
																	{
																		if (tst < 0)
																			break;
																			
																	}
																	else
																	{
																		if (tst > 0)
																			break;
																	}
																	wert4 =( tst+figwert4+wert4)/2;
																
																	if ((tst + figwert4) > 0)
																		max = (max+ tst+figwert4)/2;
																	else if (0 > (tst + figwert4))
																		min = (min+tst+figwert4)/2;
																}
																
															}
														}
													}
													myboard->takebacktestmove(i3, j3, ni3, nj3, o3);
													myboard->setwhitetoMove(!myboard->getwhitetoMove());*/
												}
												
											}
										}
									}
									myboard->takebacktestmove(i2, j2, ni2, nj2, o2);
									myboard->setwhitetoMove(!myboard->getwhitetoMove());
								}
								

							}
						}
					}
					myboard->takebacktestmove(i, j, ni, nj, o);
					myboard->setwhitetoMove(!myboard->getwhitetoMove());
				}
			}
		}
	}
	/*if (whitetomove)
	{
		*bewert = max;// wert1 - wert2 / 2 + wert3 / 3 - wert4 / 4;
	}
	else
	{
		*bewert = min;// -wert1 + wert2 / 2 - wert3 / 3 + wert4 / 4;
	}*/
	if (round3)
		*bewert = summe3;
	else if (round2)
		*bewert = summe2;
	else 
		*bewert = summe1;

	printf("bew %d %d %d %d ges %d mmin %d max %d mw %d\n",summe1,summe2,summe3,wert4, *bewert,min, max,(min+max)/2);
	//delete movingboard3;
	delete myeva4;
	delete myeva3;
	//delete movingboard2;
	delete myeva2;
	//delete movingboard;
	delete myeva;
	//delete myboard;
	//delete myboard2;
	//delete myboard3;
	return knt;
}

int Calculus::getBewertungHitsZuege(Board *myboard,int *mybewert,int tiefe, int figurenwert)
{
	Evaluation *myeva = new Evaluation();
	Evaluation *myeva2 = new Evaluation();
	Evaluation *myeva3 = new Evaluation();
	Board *movingboard = myeva->possibleMoves(myboard);
	Board *movingboard2,*movingboard3;
	bool whitetomove = !myboard->getwhitetoMove();
	int wert, wert2,wert3, knt = 0, diff1 = 0, diff2 = 0, diff3=0;
	int ni, nj,ni2,nj2;
	char f,o,f2,f3,o2;
	bool round1 = false, round2 = false, round3 = false, round4 = false;
	for (int i = 1; i < 9; i++)// Loop for Oponent;
	{
		for (int j = 1; j < 9; j++)
		{
			f = movingboard->getPieceonPos(i, j);
			if (f != 'e' && f != 'x' && f != 'm' && f != 'h')
			{
				myeva->computeMovesfigure(i, j, myboard);
				while (myeva->makeNextMovesfigure())
				{
					wert = myeva->getFigurenwert();
					knt++;
					if (wert != figurenwert)
					{
						if (wert < figurenwert)
						{
							if (!whitetomove)
								break;
							round1 = true;
							diff1 =  (diff1+wert+figurenwert)/2;
						}
						if (wert >figurenwert)
						{
							if (whitetomove)
								break;
							round1 = true;
							diff1 = (diff1+wert+figurenwert);
						}
						ni = myeva->getZug(true);
						nj = myeva->getZug(false);
						o = myboard->maketestmove(i, j, ni, nj);
						myboard->setwhitetoMove(!myboard->getwhitetoMove());
						movingboard2 = myeva2->possibleMoves(myboard);
						for (int i = 1; i < 9; i++)// Loop for Oponent;
						{
							for (int j = 1; j < 9; j++)
							{
								f2 = movingboard2->getPieceonPos(i, j);
								if (f2 != 'e' && f2 != 'x' && f2 != 'm' && f2 != 'h')
								{
									myeva2->computeMovesfigure(i, j, myboard);
									while (myeva2->makeNextMovesfigure())
									{
										wert2 = myeva2->getFigurenwert();
										knt++;
										if (wert2 != figurenwert+wert)
										{
											if (wert2 < (figurenwert + wert))
											{
												if (!whitetomove)
													break;
												round2 = true;
												diff2 = (diff1 + wert2+ figurenwert + wert)/2;
											}
											if (wert2 > (figurenwert + wert))
											{
												if (whitetomove)
													break;
												round2 = true;
												diff2 = (diff1 + wert2+ figurenwert + wert)/2;
											}
											ni2 = myeva->getZug(true);
											nj2 = myeva->getZug(false);
											o2 = myboard->maketestmove(i, j, ni2, nj2);
											myboard->setwhitetoMove(!myboard->getwhitetoMove());
											movingboard3 = myeva3->possibleMoves(myboard);
											for (int i = 1; i < 9; i++)// Loop for Oponent;
											{
												for (int j = 1; j < 9; j++)
												{
													f3 = movingboard2->getPieceonPos(i, j);
													if (f3 != 'e' && f3 != 'x' && f3 != 'm' && f3 != 'h')
													{
														myeva3->computeMovesfigure(i, j, myboard);
														while (myeva3->makeNextMovesfigure())
														{
															wert3 = myeva2->getFigurenwert();
															knt++;
															if (wert3!= figurenwert + wert+ wert2)
															{
																if (wert3 < (figurenwert + wert+wert2))
																{
																	if (!whitetomove)
																		break;
																	round3 = true;
																	diff3 = (diff3 + figurenwert + wert +wert2+ wert3) / 2;
																}
																if (wert3 >(figurenwert + wert+wert2))
																{
																	if (whitetomove)
																		break;
																	round3 = true;
																	diff3 =( diff3 + figurenwert + wert+wert2 + wert3)/2;
																}
																															}
														}
													}
												}
											}
											myboard->takebacktestmove(i, j, ni2, nj2, o2);
											myboard->setwhitetoMove(!myboard->getwhitetoMove());
										}
									}
								}
							}
						}
						myboard->takebacktestmove(i, j, ni, nj, o);
						myboard->setwhitetoMove(!myboard->getwhitetoMove());
					}

				}
			}
		}
	}
	printf("wert %d %d %d\n", diff1,diff2,diff3);
	if(round3)
		*mybewert = diff3;
	else if(round2)
		*mybewert = diff2;
	else if(round1)
		*mybewert = diff1;
	delete myeva;
	delete myeva2;
	delete myeva3;
	return knt;
}

int Calculus::getBewertungHitsZuegeBadWay(Board *myboard, int *mybewert, int tiefe, int figurenwert)
{
	EvaluationRekurs *myeva = new EvaluationRekurs();
	Board *movingboard= myeva->possibleMoves(myboard);
	Pieces *pic = new Pieces();
	bool whitetomove = !myboard->getwhitetoMove();
	int wert=0, knt = 0,ni,nj,vi,vj,min=0,max=0;
	char o,f;
	*mybewert = 0;
	int figwert = figurenwert;
	for (int i = 0; i < tiefe; i++)
	{

		ni = 0, nj = 0;
		for (int i = 1; i < 9; i++)// Loop for Oponent;
		{
			for (int j = 1; j < 9; j++)
			{
				f = movingboard->getPieceonPos(i, j);
				if (f != 'e' && f != 'x' && f != 'm' && f != 'h')
				{
                
					myeva->computeMovesfigure(i, j, myboard);
					while (myeva->makeNextMovesfigure())
					{
						wert = myeva->getFigurenwert();
						knt++;
						if (whitetomove && wert < min)
						{
							min = wert;
							vi = i;
							vj = j;
							ni = myeva->getZug(true);
							nj = myeva->getZug(false);
						}
						else if (!whitetomove && wert > max)
						{
							max = wert;
							vi = i;
							vj = j;
							ni = myeva->getZug(true);
							nj = myeva->getZug(false);
						}
					}
				}
			}
		}
		if (ni > 0 && nj > 0)
		{
			if (whitetomove)
			{
				*mybewert = min + figwert;
			}
			else
			{
				*mybewert = max + figwert;
			}
			o = myboard->maketestmove(vi,vj, ni, nj);
			if (o != 'e')
			{
				pic->init();
				pic->setName(o);
				figwert += pic->getWert();
			}
			myboard->setwhitetoMove(!myboard->getwhitetoMove());
			movingboard = myeva->possibleMoves(myboard);
			ni = 0, nj = 0;
			for (int i = 1; i < 9; i++)// Loop for Me;
			{
				for (int j = 1; j < 9; j++)
				{
					f = movingboard->getPieceonPos(i, j);
					if (f != 'e' && f != 'x' && f != 'm' && f != 'h')
					{

						myeva->computeMovesfigure(i, j, myboard);
						while (myeva->makeNextMovesfigure())
						{
							wert = myeva->getFigurenwert();
							knt++;
							if (!whitetomove && wert < min)
							{
								min = wert;
								vi = i;
								vj = j;
								ni = myeva->getZug(true);
								nj = myeva->getZug(false);
							}
							else if (!whitetomove && wert > max)
							{
								max = wert;
								vi = i;
								vj = j;
								ni = myeva->getZug(true);
								nj = myeva->getZug(false);
							}
						}
					}
				}
			}
			if (ni > 0 && nj > 0)
			{
				if (!whitetomove)
				{
					*mybewert = max;
				}
				else
				{
					*mybewert = min;
				}
			}
		}
		if (ni > 0 && nj > 0)
		{
			o = myboard->maketestmove(vi, vj, ni, nj);
			if (o != 'e')
			{
				pic->init();
				pic->setName(o);
				figwert += pic->getWert();
			}
			myboard->setwhitetoMove(!myboard->getwhitetoMove());
			movingboard = myeva->possibleMoves(myboard);
		}
		else
		{
			delete myeva;
			return knt;
		}
	}
	delete myeva;
	return knt;
}
