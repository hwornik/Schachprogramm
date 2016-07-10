//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Unit1.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Wichtig: Methoden und Eigenschaften von Objekten in der VCL können nur
//   in Methoden verwendet werden, die mit 'Synchronize' aufgerufen wurden, z.B.:
//
//      Synchronize(&UpdateCaption);
//
//   wobei UpdateCaption so aussehen könnte:
//
//      void __fastcall CalculusTopTh::UpdateCaption()
//      {
//        Form1->Caption = "Im Thread aktualisiert";
//      }
//---------------------------------------------------------------------------

__fastcall CalculusTopTh::CalculusTopTh(bool CreateSuspended)
	: TThread(CreateSuspended)
{

}
//---------------------------------------------------------------------------
void __fastcall CalculusTopTh::Execute()
{
	// ---- Fügen Sie den Thread-Code hier ein ----
	myevatst   = new Evaluation();
	myeva = new Evaluation();
	pic = new Pieces();
	for(int i=0;i<4;i++)
	{
         bestMove[i]= new Zuege();
	}
    for(int i=0;i<64;i++)
	{
		bestzuege[i]= new Zuege();
	}
	threadarr = new DeepSearchTh*[MAX_THREADS];
	fthreadarr = new UnderAttackTh*[MAX_THREADS];
    for(int i=0;i<MAX_THREADS;i++)
	{
		 threadarr[i]=new DeepSearchTh(true);
		 fthreadarr[i]=new UnderAttackTh(true);
	}
	TCHAR msgBuf[BUF_SIZE];
	size_t cchStringSize;
	DWORD dwChars;
	Board *masterboard = myboard;
	Board *movingboard = myeva->possibleMoves(masterboard);
	//myeva->printStats();
	int grenze = myeva->getMovesFigures();
	char f;
	int moves[64], hits[64], bewegfig[64], kontrol[64], wert = 0;
	bool boardok[64];
	//zug = new char*[64];
	for(int i=0;i<64;i++)
	{
		//zug[i]= new char[8];
		moves[i]=0;
		hits[i]=0;
		bewegfig[i]=0;
		kontrol[i]=0;
		boardok[i]=true;
	}
	int kontrolle=0;
	int bewegfigure=0;
	int hit=0;
	int movezahl=0;
	int zi = 0, zugnr;
	int *tbewertung, *ttaktik;
	int taktik = 0, bewertt=0;
	tbewertung = &bewertt;
	ttaktik = &taktik;
	int tiefe = 0, startzug = 0, halbzug = 0;
	bool movewhite = masterboard->getwhitetoMove();
	zugnr = masterboard->getZugNr();
	//char **zzug;
	//zzug = new char*[4];
	//Thread
	int aktindex = 0;
    int aktthread=0;
	int aktberech[16];

	int	wwerta[4], bwerta[4],kontrollea[4],bewegfigurea[4], hita[4], movezahla[4],bzuga[4];
	// init
	for(int i=0;i<16;i++)
	{
		aktberech[i]=0;
		bewisready[i]=true;
        fbewisready[i]=true;
	}
	zugnr++;
	int wwert1 = 0 - 8 * 1 - 4 * 3 - 2 * 5 - 9 - 9999 - 1;
	wwert1 *= 100;
	int wwert2=wwert1;
	int bwert1 = 8 * 1 + 4 * 3 + 2 * 5 + 9 + 9999 + 1;
	bwert1 *= 100;
	int bwert2=bwert1;
	for(int i=0;i<4;i++)
	{
		wwerta[i]=wwert1;
		bwerta[i]=bwert1;
    }
	HANDLE set = GetStdHandle(STD_OUTPUT_HANDLE);
	if (searchmvs)  // Bestimmte Züge bewerten!!
	{
		for (int i = 1; i <= mynot->getAktZugNr(); i++)
		{
			Zuege *zg = mynot->getZugNr(i);
			
		}
	}
	else    // Alle möglichen Züge ermitteln
	{
		for (int i = 1; i < 9; i++)// my next move
		{
			for (int j = 1; j < 9; j++)
			{
				f = movingboard->getPieceonPos(i, j);
				if (f != 'e' && f != 'x' && f != 'm' && f != 'h')
				{

					myeva->computeMovesfigure(i, j, myboard);
					//delete ubgboard;
					while (myeva->makeNextMovesfigure())
					{
						ubgboarda[aktindex] = myboard->copyBoard();
						ubgboarda[aktindex]->makeMove(myeva->getZug(true,true),myeva->getZug(true,false),myeva->getZug(false,true),myeva->getZug(false,false));
						bewr[aktindex]=myeva->getFigurenwert();
						 //std::cout << "Zug " << myeva->getZugStr() << "\n";
						 taktikarr[aktindex] = myeva->getKontrolFields()
							+ myeva->getHits() + myeva->getMovesFigures() + myeva->getZuege();
						//// Threads start
						kontrol[aktindex] = myeva->getKontrolFields();
						bewegfig[aktindex] = myeva->getMovesFigures();
						hits[aktindex] = myeva->getHits();
						moves[aktindex] = myeva->getZuege();
						//zug[aktindex]=myeva->getZugStr();
						this->bestzuege[aktindex]->setWhitePiece(myeva->getZug(true,true),myeva->getZug(true,false),myeva->getZug(false,true),myeva->getZug(false,false));
						//// Teste ob Figur genommen werden kann. Wenn nicht, berechne Zugwerte
					   //std::cout <<  this->bestzuege[aktindex]->getWhiteMove() << " " << bewr[aktindex] << "\n";

						testeFigurAttacke(ubgboarda[aktindex],myeva->getZug(false,true),myeva->getZug(false,false),&boardok[aktindex],&fbewisready[aktindex]);
						//this->berechneZugwerte(zug[aktindex],ubgboarda[aktindex],bewr[aktindex],&bewertarr[aktindex],&tbewertarr[aktindex],bestzuege[aktindex]->getWhitePiece(true,true),bestzuege[aktindex]->getWhitePiece(true,false),bestzuege[aktindex]->getWhitePiece(false,true), bestzuege[aktindex]->getWhitePiece(false,false),false);

						///-------------------------Ende
						//std::cout <<   zug[aktindex] << " " << taktikarr[aktindex] <<  " " << kontrol[aktindex] << " " << bewegfig[aktindex] << " " << hits[aktindex] << " " << moves[aktindex] << "\n";
                        aktindex++;
					/*if (*ending)
					{
						mycom->sendmoves(zug, zug2);
						return;
					}
					  */
                    }
				}
			}
		}
		int count=0;
		while(count<MAX_THREADS)
		{
			for(int ix=0;ix<MAX_THREADS;ix++)
			{
				while(!fbewisready[ix])
				{
					 Sleep(100);
				}
                Sleep(100);
				//fthreadarr[ix]->CheckTerminated();
				count++;
			}
		}
		for(int i=0;i<aktindex;i++)
		{
			//std::cout << bestzuege[i]->getWhiteMove();
			if(boardok[i])
			{
			   this->berechneZugwerte(bestzuege[i]->getWhiteMove(),ubgboarda[i],bewr[i],&bewertarr[i],&tbewertarr[i],false);
			}
			else
			{
				std::cout << "\nFigur weg bei " << bestzuege[i]->getWhiteMove() << "\n";
			   if(myboard->getwhitetoMove())
					bewertarr[aktindex]=-1000000;
				else
				   bewertarr[aktindex]=1000000;
			}
		}
        count=0;
		while(count<MAX_THREADS)
		{
			for(int ix=0;ix<MAX_THREADS;ix++)
			{
				while(!bewisready[ix])
				{
					 Sleep(100);
				}
				count++;
			}
		}
		//Auswahl der 4 besten Zuegt
		//std::cout << aktindex << "\n" ;
		for(int i=0; i< aktindex;i++)
		{
				for(int j=0;j<2;j++)
				{
				   //	std::cout << "www " << zug[i] << " " << wwerta[j] << ":"<< bewertarr[i] << "\n";
					if ((movewhite && (wwerta[j] < bewertarr[i])) || (!movewhite &&(bwerta[j] > bewertarr[i])))
					{
						for(int z=3;z>j;z--)
						{
							bestMove[z]->setWhitePiece(bestMove[z-1]->getWhitePiece(true,true) ,bestMove[z-1]->getWhitePiece(true,false),bestMove[z-1]->getWhitePiece(false,true),bestMove[z-1]->getWhitePiece(false,false));
							bzuga[z]==bzuga[z-1];
							wwerta[z] = wwerta[z-1];
							bwerta[z] = bwerta[z-1];
							kontrollea[z]=kontrollea[z-1];
							bewegfigurea[z]=bewegfigurea[z-1];
							hita[z]=hita[z-1];
							//zzug[z]=zzug[z-1];
							movezahla[z]=movezahla[z-1];
						}
						bestMove[j]->setWhitePiece(bestzuege[i]->getWhitePiece(true,true) ,bestzuege[i]->getWhitePiece(true,false),bestzuege[i]->getWhitePiece(false,true),bestzuege[i]->getWhitePiece(false,false));
						wwerta[j] = bewertarr[i];
						bwerta[j] = bewertarr[i];
						kontrollea[j]=kontrol[i];
						bewegfigurea[j]=bewegfig[i];
						hita[j]=hits[i];
						movezahla[j]=moves[i];
						//zzug[j]=bestzuege[i]->getWhiteMove();
						break;
					}
					else if ((wwerta[j] == bewertarr[i] || bwerta[j]==bewertarr[i]) && ((kontrollea[j] + bewegfigurea[j] + hita[j] + movezahla[j])< (kontrol[i] + hits[i] + bewegfig[i] + moves[i])))
					{
						for(int z=3;z>j;z--)
						{
							bestMove[z]->setWhitePiece(bestMove[z-1]->getWhitePiece(true,true) ,bestMove[z-1]->getWhitePiece(true,false),bestMove[z-1]->getWhitePiece(false,true),bestMove[z-1]->getWhitePiece(false,false));
							bzuga[z]==bzuga[z-1];
							wwerta[z] = wwerta[z-1];
							bwerta[z] = bwerta[z-1];
							kontrollea[z]=kontrollea[z-1];
							bewegfigurea[z]=bewegfigurea[z-1];
							hita[z]=hita[z-1];
							//zzug[z]=zzug[z-1];
							movezahla[z]=movezahla[z-1];
						}
						bestMove[j]->setWhitePiece(bestzuege[i]->getWhitePiece(true,true) ,bestzuege[i]->getWhitePiece(true,false),bestzuege[i]->getWhitePiece(false,true),bestzuege[i]->getWhitePiece(false,false));
						wwerta[j] = bewertarr[i];
						bwerta[j] = bewertarr[i];
						kontrollea[j]=kontrol[i];
						bewegfigurea[j]=bewegfig[i];
						hita[j]=hits[i];
						movezahla[j]=moves[i];
						//zzug[j]=bestzuege[i]->getWhiteMove();
						break;
					}
				}

		}
		for(int i=0;i<2;i++ )
		{
			std::cout <<   bestMove[i]->getWhiteMove() << " " << kontrollea[i] << " " << bewegfigurea[i] << " " << hita[i] <<"\n";
		}

    }
	// Print the parameter values using thread-safe functions.
	StringCchPrintf(msgBuf, BUF_SIZE, TEXT("info score cp%d time %d\n"),wert, clock() - movetime);
	StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
	WriteConsole(set, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);
	//Print Thread safe ende
	mycom->sendmoves(bestMove[0]->getWhiteMove(), bestMove[0]->getWhiteMove());
	delete masterboard;
	for(int i=0;i<64;i++)
	{
		delete ubgboarda[i];
	}
    for(int i=0;i<MAX_THREADS;i++)
	{
		 delete threadarr[i];
	}
   //	delete [] ubgboarda;
   // delete [] threadarr;
	return;
}

void CalculusTopTh::setData(Notation *mynot, bool searchmvs, Board* myboard, Communicate *mycom, clock_t movetime)
{
	   this->mynot=mynot;
	   this->searchmvs=searchmvs;
	   this->myboard=myboard;
	   this->mycom=mycom;
	   this->movetime=movetime;
}

void CalculusTopTh::berechneZugwerte(char *zuga,Board *grboard,int bewr, int *bewertarr,int *taktikarr,bool masterwhitetomove)
{
		char ok;
		int count=0;
		//----------------------------------
		// Thread Bewertungen
		while(count==0)
		{
			for(int ix=0;ix<MAX_THREADS;ix++)
			{
				if(bewisready[ix])
				{
				    delete threadarr[ix];
					threadarr[ix]=new DeepSearchTh(true);
					bewisready[ix]=false;
					threadarr[ix]->setData(&bewisready[ix],grboard,bewertarr,1,taktikarr,bewr,false,zuga,masterwhitetomove);
					threadarr[ix]->Start();
					count++;
					break;
				}
				if(count>0)
					break;

			}
			if(count==0)
			{
				Sleep(100);
			}
			else
				break;
		}
	   //	zwboard->takebacktestmove(i, j, myeva->getZug(true), myeva->getZug(false),ok);
	   //	zwboard->setwhitetoMove(!zwboard->getwhitetoMove());

}

void CalculusTopTh::testeFigurAttacke(Board *myboard,int posx,int posy,bool *isunderattack,bool *fertig)
{
		int count=0;
		//----------------------------------
		// Thread Bewertungen
		while(count==0)
		{
			for(int ix=0;ix<MAX_THREADS;ix++)
			{
				if(bewisready[ix])
				{
					delete fthreadarr[ix];
					fthreadarr[ix]=new UnderAttackTh(true);
					fthreadarr[ix]->setData(myboard,posx,posy,!myboard->getwhitetoMove(),isunderattack,fertig);
					fthreadarr[ix]->Start();
					count++;
					break;
				}
				if(count>0)
					break;

			}
			if(count==0)
			{
				Sleep(100);
			}
			else
			break;
		}
}
//---------------------------------------------------------------------------
