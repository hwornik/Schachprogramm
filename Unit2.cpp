//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Unit2.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Wichtig: Methoden und Eigenschaften von Objekten in der VCL können nur
//   in Methoden verwendet werden, die mit 'Synchronize' aufgerufen wurden, z.B.:
//
//      Synchronize(&UpdateCaption);
//
//   wobei UpdateCaption so aussehen könnte:
//
//      void __fastcall DeepSearchTh::UpdateCaption()
//      {
//        Form1->Caption = "Im Thread aktualisiert";
//      }
//---------------------------------------------------------------------------

__fastcall DeepSearchTh::DeepSearchTh(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall DeepSearchTh::Execute()
{
	// ---- Fügen Sie den Thread-Code hier ein ----
   	int ni, nj, ni2, nj2, ni3, nj3, ni4, nj4, knt = 0;
	EvaluationRekurs *myeva2= new EvaluationRekurs();
	int figwert2 = 0, figwert3 = 0, figwert4 = 0, figwert5 = 0;
	EvaluationRekurs *myeva3, *myeva4;
	EvaluationRekurs *myeva;
	int anzahl=0,anzhl1=1, taktikw1=0,anzhl2=1, taktikw2=0;
	int xi=0,xi2=0,mw=0,stdab=0;
	myeva4 = new EvaluationRekurs();
	myeva3 = new EvaluationRekurs();
	myeva = new EvaluationRekurs();
	Board *movingboard, *movingboard2, *movingboard3,*movingboard4;
	//Board *myboard2, *myboard3;
	bool whitetomove = !myboard->getwhitetoMove();
	bool round1 = false, round2 = false, round3 = false, round4 = false, round5 = false;
	char f, o, z,f2,o2,f3,o3,f4,o4;
	int min = 0;
	int max = 0;
	int tst=0;
	int grup[5], grdown[5];
	int summe1= 0, summe2 = 0, summe3 = 0;
	 for(int i=0;i<5;i++)
	{
		grup[i] = 0;
		grdown[i] = 0;
	}
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
					round1 = true;
					//printf(" Zug %d bew %d ",i*10+j, *bewert);
					ni = myeva->getZug(true);
					nj = myeva->getZug(false);
					o = myboard->maketestmove(i, j, ni, nj);
					myboard->setwhitetoMove(!myboard->getwhitetoMove());
					figwert2 = figurenwert+tst;
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
									tst = myeva2->getFigurenwert();
									round2 = true;
									ni2 = myeva2->getZug(true);
									nj2 = myeva2->getZug(false);
									o2 = myboard->maketestmove(i2, j2, ni2, nj2);
									myboard->setwhitetoMove(!myboard->getwhitetoMove());
									movingboard3 = myeva3->possibleMoves(myboard);
									figwert3 = tst+figwert2;
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
													figwert4 = tst + figwert3;
													round3 = true;
													mw+= figwert4;
													anzahl++;
													xi2+= (figwert4*figwert4);
													if (figwert4 > max)
														max = figwert4;
													if (min < figwert4)
														min = figwert4;
												  /*
													ni3 = myeva3->getZug(true);
													nj3 = myeva3->getZug(false);
													o3 = myboard->maketestmove(i3, j3, ni3, nj3);
													myboard->setwhitetoMove(!myboard->getwhitetoMove());
													movingboard4 = myeva4->possibleMoves(myboard);
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

																	figwert5 = tst+figwert4;
																	mw+= figwert5;
																	anzahl++;
																	xi2+= ((figwert5)*(figwert5));
																	if ((figwert5) > max)
																		max = tst+figwert5;
																	if (min < (figwert5))
																		min = (tst+figwert5);
																}

															}
														}
													}
													myboard->takebacktestmove(i3, j3, ni3, nj3, o3);
													myboard->setwhitetoMove(!myboard->getwhitetoMove());
                                                    */
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
	xi=mw;
	stdab=1;
	//std::cout << mw << " " << xi2 << " " << anzahl << "\n";
	if(anzahl>2)
	{
		xi=(mw*mw)/anzahl;
		stdab=(xi2-xi)/(anzahl-1);
		if(stdab>0)
			stdab=sqrt((double)stdab)/10;
		else
			stdab=sqrt((double)-stdab)/10;
        mw=mw/anzahl;
	}
	if (whitetomove)
	{
		*taktikwert = stdab;
		if(stdab<31)
			*bewert = mw;// wert1 - wert2 / 2 + wert3 / 3 - wert4 / 4;
			else
			*bewert=-10000;
	}
	else
	{
		*taktikwert = stdab ;
		if(stdab<31)
		*bewert = mw;// -wert1 + wert2 / 2 - wert3 / 3 + wert4 / 4;
		else
        *bewert=10000;
	}
	//std::cout << anzahl << "\n";
    if(!masterwhitetomove)
	printf("info %s mw %d std: %d t: %d t1: %d t2: %d bew %d %d %d  ges %d min %d max %d\n",zug,mw,stdab,*taktikwert,taktikw1,taktikw2,summe1,summe2,summe3,*bewert,min, max);
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
	*isready=true;
    return;
}

int DeepSearchTh::setData(bool *isready,Board *myboard,int *bewert, int tiefe,int *taktikwert,int figurenwert,bool nullproove, char *zug,bool masterwhitetomove)
{
	this->myboard=myboard;
	this->bewert=bewert;
	this->taktikwert=taktikwert;
	this->figurenwert=figurenwert;
	this->nullproove=nullproove;
	this->isready=isready;
	this->zug=zug;
	this->masterwhitetomove=masterwhitetomove;
}
//---------------------------------------------------------------------------
