#pragma once
#include "Vozidlo.h"
class CentralnySklad
{
public:
	CentralnySklad();
	~CentralnySklad();
	void prijmiZasielky(Vozidlo *vozidlo);
	void vypisZoznamZasielok();
private:
	structures::ArrayList<Zasielka *> * arrayListZasielok;
};

