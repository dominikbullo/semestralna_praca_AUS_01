#pragma once
#include "Vozidlo.h"
class CentralnySklad
{
public:
	CentralnySklad();
	~CentralnySklad();
	void prijmiZasielky(Vozidlo *vozidlo);
private:
	structures::ArrayList<Zasielka *> * arrayListZasielok;
};

