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
	void vypisanieVsetkychObjednavok();
	void pridajVozidlo(Vozidlo * noveVozidlo);
	void pridajRegionyDoTrasyVozidla(Vozidlo * vozidlo);

	std::string getNazovFirmy() {
		return nazovFirmy_;
	}

	void pridajPrekladisko(Prekladisko * novePrekladisko) {
		arrayListPrekladisk->add(novePrekladisko);
	};

	void spracujVsetkyObjednavky()
	{
		for (Prekladisko* prekladisko : *arrayListPrekladisk)
		{
			prekladisko->spracujObjednavky();
		}

	};

	Vozidlo* getVozidloBySPZ(std::string SPZ)
	{
		// TODO inline int ArrayList<T>::getIndexOf(const T & data)
		for (Vozidlo* vozidlo : *arrayListVozidiel) {
			if (vozidlo->getSPZ() == SPZ) {
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
	void vytvorObjednavku(double hmotnostZasielky, Odosielatel * odosielatel, Adresat * adresat);
private:
	std::string nazovFirmy_;
	structures::ArrayList<Vozidlo*> * arrayListVozidiel;
	structures::ArrayList<Prekladisko*> * arrayListPrekladisk;
	structures::LinkedList<Objednavka*> * linkedListObjednavok;
};
