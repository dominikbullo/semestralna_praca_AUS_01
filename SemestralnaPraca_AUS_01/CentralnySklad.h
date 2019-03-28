#pragma once
#include "Vozidlo.h"
class CentralnySklad
{
public:
	CentralnySklad();
	~CentralnySklad();
	void prijmiZasielky(Vozidlo *vozidlo);
	void vypisZoznamZasielok();
	void naplVozidla();
private:
	structures::ArrayList<Zasielka *> * arrayListZasielok;
};

