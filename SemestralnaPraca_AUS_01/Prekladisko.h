#pragma once
#include<string>
#include<iostream> 
#include<algorithm> 

#include "structures/heap_monitor.h"
#include "structures/list/array_list.h"

//#include "Vozidlo.h"
#include "Dron.h"
#include "Objednavka.h"
#include "Zasielka.h"

using namespace std;

class Prekladisko
{
public:
	Prekladisko(std::string okres);
	~Prekladisko();
	void pridajDron(Dron * novyDron);
	void vypisZoznamDronov();
	void spracujZasielky();

	Dron * vyberDrona(Zasielka * zasielka);
	std::string Prekladisko::set_get_SerioveCislo();

	std::string dajRegion() { return region_; }
	Dron * dajLepšiehoVolnehoDrona(Dron * dron1, Dron * dron2);
	Dron * dajLelpšiehoObsadenehoDrona(Dron * dron1, Dron * dron2);

	friend ostream& operator<< (ostream& os, Prekladisko& prekladisko);
	friend istream& operator>> (istream& is, Prekladisko& prekladisko);
private:
	std::string region_;

	structures::ArrayList<Dron*> * arrayListDronov_;
	structures::ArrayList<Zasielka*> * arrayListZasielok_;

protected:
	std::string serioveCislo_ = region_;
	static int unikatneSerioveCislo_;
};

