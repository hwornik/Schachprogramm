#include "stdafx.h"
#include "Notation.h"


Notation::Notation()
{
	this->mymoves = new Zuege();
	zugnr = 0;
}


Notation::~Notation()
{
	while (zugnr > 0)
		this->deleteLastZug();
}


bool Notation::addZug(Zuege *zug)
{
	Zuege *akt;
	zugnr++;
	akt = this->mymoves;
	while (akt->next != 0)
		akt = akt->next;
	akt->next = zug;
	return true;
}

Zuege *Notation::getAktZug()
{
	Zuege *akt;
	akt = this->mymoves;
	while (akt->next != 0)
		akt = akt->next;
	return akt;
}
Zuege *Notation::getZugNr(int nr)
{
	Zuege *akt;
	akt = this->mymoves;
	while (akt->next != 0)
	{
		if (akt->getZugNr() == nr)
			return akt;
		akt = akt->next;
	}
	if (akt->getZugNr() == nr)
		return akt;
	return 0;
}

int Notation::getAktZugNr()
{
	return zugnr;
}

bool Notation::deleteLastZug()
{

	Zuege *akt, *del;
	zugnr--;
	akt = this->mymoves;
	if (akt->next != 0)
	{
		del = akt->next;
		while (del->next != 0)
		{
			akt = del;
			del = del->next;
		}
		akt->next = 0;
		delete del;
		return true;
	}
	return false;
}

char *Notation::getZuegeStr()
{
	std::string str;
	if (this->mymoves->next != 0)
	{
		std::string str;
		char tr[20];
		Zuege *akt;
		akt = mymoves->next;
		while (akt->next != 0)
		{
			str += akt->getZugNr() + 48;
			str += '. ';
			str += akt->getWhiteMove();
			str += ' ';
			str += akt->getBlackMove();
			str += ' ';
			akt = akt->next;
		}
		str += akt->getZugNr() + 48;
		str += '. ';
		str += akt->getWhiteMove();
		str += ' ';
		str += akt->getBlackMove();
		str += ' ';
		return strdup(str.c_str());
	}
	return strdup(str.c_str());
}

int Notation::getBewertung()
{
	return this->bewertung;
}
void Notation::setBewertung(int bew)
{
	this->bewertung = bew;
}
