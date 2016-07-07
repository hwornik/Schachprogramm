#pragma once
#include <stdio.h>
	const char row[8] = { 'a','b','c','d','e','f','g','h' };
	const char figure[2][4] = { { 'Q','R','B','N' },{ 'q','r','b','n' } };
class Zuege
{
public:
	Zuege();
	~Zuege();
	int getZugNr();
	void setZugNr(int zug);
	int getWhitePiece(bool from, bool xwert);
	int getBlackPiece(bool from, bool xwert);
	char getWhiteTrade();
	char getBlackTrade();
	void setWhiteTrade(char pie);
	void setBlackTrade(char pie);
	bool setWhitePiece(char movenot[5]);
	bool setWhitePiece(int vx, int vy, int nx, int ny);
	bool setBlackPiece(char movenot[5]);
	bool setBlackPiece(int vx, int vy, int nx, int ny);
	char* getWhiteMove();
	char* getBlackMove();
	bool isWhiteTrade();
	bool isBlackTrade();
	Zuege *next;
	void init();
private:
	int zugnr;
	char whitemove[5], blackmove[5];
	int blvx, blvy, blnx, blny;
	int whvx, whvy, whnx, whny;
	int bltr, whtr;
	bool convert(char movenot[5], bool white);
	bool whitetrade, blacktrade;

};

