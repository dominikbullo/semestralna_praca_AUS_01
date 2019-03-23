#pragma once
#include <algorithm>
#include <string>
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
	Firma * get();
	std::string getNazovFirmy() {
		return nazovFirmy_;
	}
	void pridajPrekladisko(Prekladisko * noveVozidlo);
	void pridajVozidlo(Vozidlo * noveVozidlo);
	void pridajRegionyDoTrasyVozidla(Vozidlo * vozidlo);

	Vozidlo* getVozidloBySPZ(std::string SPZ)
	{
		for (Vozidlo* vozidlo : *arrayListVozidiel)
		{
			if (vozidlo->getSPZ() == SPZ)
			{
				return vozidlo;
			}
		}
		return NULL;
	}
	void vypisZoznamVozidiel()
	{
		for (Vozidlo* vozidlo : *arrayListVozidiel)
		{
			vozidlo->toString();
		}
	}

	Prekladisko * dajPrekladiskoPodlaRegionu(std::string okres);
	Vozidlo * vyberVozidlo(double hmotnostZasielky, Prekladisko * prekladiskoNaPrevzatieZasielky);
	bool mamDostupneProstriedkyNaDorucenieObjednavky(double hmotnostZasielky, Prekladisko * prekladisko, double vzdialenostOdPrekladiska);
	Objednavka * vytvorObjednavku(double hmotnostZasielky, Odosielatel * odosielatel, Adresat * adresat);
private:
	std::string nazovFirmy_;
	structures::ArrayList<Vozidlo*> * arrayListVozidiel;
	structures::ArrayList<Prekladisko*> * arrayListPrekladisk;
	structures::LinkedList<Objednavka*> * linkedListObjednavok;
};
