#pragma once
#include "Zuege.h"
#include <string.h>
#include <string>

class Notation
{
public:
	Notation();
	~Notation();
	bool addZug(Zuege *zug);
	Zuege *getZugNr(int nr);
	int getAktZugNr();
	Zuege *getAktZug();
	bool deleteLastZug();
	char *getZuegeStr();
	int getBewertung();
	void setBewertung(int bew);
private:
	Zuege *mymoves;
	int zugnr;
	int bewertung;
};

