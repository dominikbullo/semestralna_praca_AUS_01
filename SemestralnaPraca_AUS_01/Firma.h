#pragma once
#include <algorithm>
#include <string>
#include "structures/heap_monitor.h"
#include "structures/list/array_list.h"
#include "structures/list/linked_list.h"
#include "Vozidlo.h"
#include "Konstatnty.h"
#include "Datum.h"
#include "Prekladisko.h"
#include "Objednavka.h"
#include "Dron.h"
#include "CentralnySklad.h"

class Firma
{
public:
	Firma(std::string nazovFirmy);
	~Firma();
	void vypisanieVsetkychObjednavok();
	void pridajVozidlo(Vozidlo * noveVozidlo);
	void pridajVsetkyRegionyDoTrasyVozidla(Vozidlo * vozidlo);
	void pridajRegionyDoTrasyVozidla(Vozidlo * vozidlo);
	void vratVozidlaDoCentralnehoSkladu();

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
			prekladisko->spracujZasielky();
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
	Vozidlo * vyberVozidlo(Zasielka * zasielka);
	Vozidlo * vyberVozidlo(Zasielka * zasielka, Prekladisko * prekladisko);
	void vytvorObjednavku(double hmotnostZasielky, Odosielatel * odosielatel, Adresat * adresat);
	bool chceUserZrusitObjednavku(Dron * dronPreOdosielatela, Zasielka * zasielka);
private:
	std::string nazovFirmy_;
	CentralnySklad* centralnySklad_;
	structures::ArrayList<Vozidlo*> * arrayListVozidiel;
	structures::ArrayList<Prekladisko*> * arrayListPrekladisk;
	structures::LinkedList<Objednavka*> * linkedListObjednavok;
};
