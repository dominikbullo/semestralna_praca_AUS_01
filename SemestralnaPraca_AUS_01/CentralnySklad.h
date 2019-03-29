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


	friend ostream& operator<< (ostream& os, CentralnySklad& centralnySklad);
	friend istream& operator>> (istream& is, CentralnySklad& centralnySklad);
private:
	structures::ArrayList<Zasielka *> * arrayListZasielok;
};

