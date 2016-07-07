#pragma once
#include <ctype.h>

class Board
{
public:
	Board();
	void init();
	~Board();
	int loadFromFen(char pos[100]);
	bool makeMove(int vx, int vy, int nx, int ny);
	char *toString();
	char getPieceonPos(int abc, int zahl);
	bool getwhitetoMove();
	bool setwhitetoMove(bool white);
	bool getcastleKs(int col);
	bool getcastleQs(int col);
	bool setcastleKs(int col, bool castle);
	bool setcastleQs(int col, bool castle);
	int getHalbzug();
	bool setHalbzug(int zug);
	int getZugNr();
	bool setZugNr(int zug);
	bool setPiece(char p, int nx, int ny);
	bool setPieceTrade(char p, int nx, int ny);
	bool setEnPassant(int ny, bool xwert);
	bool getEnPassant();
	char maketestmove(int vx, int vy, int nx, int ny);
	bool takebacktestmove(int vx, int vy, int nx, int ny, char old);
	int getWhiteKingPos(bool xpos);
	int getBlackKingPos(bool xpos);
	bool setWhiteKingPos(int wert, bool xpos);
	bool setBlackKingPos(int wert, bool xpos);
	bool makeRochade(Board * myboard, int vx, int vy, int nx, int ny);
	int getFigurenwert();
	bool setBewertung(int bewert);
	int getBewertung();
	bool setFigurenwert(int wert);
	bool setWiederHol(int wert, int a, int b, int c);
	int getWiederHol(int a, int b, int c);
	int getWiederCount();
	bool setWiederCount(int wert);
	bool setRemie(bool rem, bool white);
	bool getRemie(bool white);
	int getEnPassantField(bool xwert);
	Board * copyBoard();
	bool setEnPassantFalse();
private:
	char chessboard[8][8];
	int bewertung;
	int figurenwert;
	char fenstring[85];
	void boardString();
	bool castleKs[2];
	bool castleQs[2];
	bool whitetoMove;
	int enpassant[2];
	int zugnr;
	int halbzug;
	int wiederholung[6][2][2];
	int wieder;
	int whiteKing[2];
	int blackKing[2];
	bool searchKings();
	bool remie[2];
	bool isenpassant;
};

