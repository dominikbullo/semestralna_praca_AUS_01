#pragma once
#include<string>

#include "structures/heap_monitor.h"
#include "structures/list/array_list.h"

#include "Dron.h"
#include"Objednavka.h"

using namespace std;

class Prekladisko
{
public:
	Prekladisko(std::string okres);
	~Prekladisko();
	void pridajDron(Dron * novyDron);
	void pridajObjednavku(Objednavka * objednavka);
	void spracujObjednavky();
	void vypisZoznamDronov();
	Dron * vyberDrona(double hmotnostZasielky, double vzdialenost, string casVytvoreniaObjednavky);
	std::string dajRegion() {
		return region_;
	}
	Dron * dajLelpšiehoDrona(Dron * dron1, Dron * dron2);
	std::string Prekladisko::set_get_SerioveCislo();
private:
	std::string region_;
	std::string serioveCislo_ = region_;
	structures::ArrayList<Dron*> * arrayListDronov_;

protected:
	static int unikatneSerioveCislo_;
};

