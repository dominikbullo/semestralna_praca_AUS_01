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
	//structures::ArrayList<Zasielka*>  vyzdvihniZasielky();
	//void nalozVozidlo(Vozidlo* vozidloNaNalozenie);
	std::string dajRegion() { return region_; }

	Dron * vyberDrona(Zasielka * zasielka);
	Dron * dajLepöiehoVolnehoDrona(Dron * dron1, Dron * dron2);
	Dron * dajLelpöiehoObsadenehoDrona(Dron * dron1, Dron * dron2);
	std::string Prekladisko::set_get_SerioveCislo();
private:
	std::string region_;
	std::string serioveCislo_ = region_;

	// TODO ako vraciaù toto ? 
	structures::ArrayList<Dron*> * arrayListDronov_;
	structures::ArrayList<Zasielka*> * arrayListZasielok_;

protected:
	static int unikatneSerioveCislo_;
};

