#pragma once
#include "Vozidlo.h"
class CentralnySklad
{
public:
	CentralnySklad();
	~CentralnySklad();
	void prijmiZasielky(Vozidlo *vozidlo);
	void vypisZoznamZasielok();
	structures::ArrayList<Zasielka*> getArrayListZasielok()
	{
		return *arrayListZasielok_;
	}

	friend ostream& operator<< (ostream& os, CentralnySklad& centralnySklad);
	friend istream& operator>> (istream& is, CentralnySklad& centralnySklad);
private:
	structures::ArrayList<Zasielka *> * arrayListZasielok_;
	structures::ArrayList<Vozidlo*> * zoznamVozidiel_;
};

