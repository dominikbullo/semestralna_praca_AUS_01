#pragma once
#include "structures/heap_monitor.h"
#include "structures/list/array_list.h"
#include "structures/list/linked_list.h"
#include "Vozidlo.h"
#include "Datum.h"
#include "Prekladisko.h"
#include "Objednavka.h"
#include "Dron.h"

class Firma
{
public:
	Firma(std::string nazovFirmy);
	~Firma();
	void pridajPrekladisko(Prekladisko * noveVozidlo);
	void pridajVozidlo(Vozidlo * noveVozidlo);
	void vypisZoznamVozidiel();
	Prekladisko * dajPrekladiskoPodlaRegionu(std::string okres);
	Objednavka * vytvorObjednavku(double hmotnostZasielky, Odosielatel * odosielatel, Adresat * adresat);
private:
	std::string nazovFirmy_;
	structures::ArrayList<Vozidlo*> * arrayVozidiel;
	structures::ArrayList<Prekladisko*> * arrayPrekladisk;
	//structures::LinkedList<Objednavka*> * linkObjednavok;
};
