#pragma once
#include "structures/heap_monitor.h"
#include "structures/list/array_list.h"
#include "Vozidlo.h"

using namespace std;

class evidenciaVozidla
{
public:
	evidenciaVozidla(Vozidlo * noveVoz, string datum);
	Vozidlo& getVozidlo();
	Vozidlo* dajVozidlo();
	string getDatum();
	void setDatum(string dat) {
		datumEvidencie_ = dat;
	}
	~evidenciaVozidla();


private:
	Vozidlo * voz_;
	string datumEvidencie_;
};


class Firma
{
public:
	Firma();
	~Firma();
	void pridajVozidlo(Vozidlo * noveVozidlo);
private:
	structures::ArrayList<Vozidlo*> * arrayVozidiel;
};
