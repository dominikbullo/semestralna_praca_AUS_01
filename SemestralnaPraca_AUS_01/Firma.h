#pragma once
#include "structures/heap_monitor.h"
#include "structures/list/array_list.h"
#include "Vozidlo.h"
#include "Datum.h"
#include "Prekladisko.h"

class Firma
{
public:
	Firma(std::string nazovFirmy);
	~Firma();
	void pridajPrekladisko(Prekladisko * noveVozidlo);
	void pridajVozidlo(Vozidlo * noveVozidlo);
	void vypisZoznamVozidiel();
private:
	std::string nazovFirmy_;
	structures::ArrayList<Vozidlo*> * arrayVozidiel;
	structures::ArrayList<Prekladisko*> * arrayPrekladisk;
};
