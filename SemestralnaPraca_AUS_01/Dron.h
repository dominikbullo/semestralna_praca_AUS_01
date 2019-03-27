﻿#pragma once
#pragma warning(disable : 4189) // referenced but not used
#pragma warning(disable : 4244) // referenced but not used
#include <string>
#include <iostream>
#include <stdio.h>

#include "structures/heap_monitor.h"
#include "structures/queue/explicit_queue.h"
#include "structures/list/array_list.h"

#include "Konstatnty.h"
#include "Datum.h"
#include "Objednavka.h"
#include "Zasielka.h"

class Dron
{
public:
	Dron(const eDrony typDronu, std::string serioveCislo);
	~Dron();
	void toString();
	bool stihnePriletietPreZasielku(double vzdialenost);
	void prepocitajInformacieoDosupnosti();
	void pridajZasielku(Zasielka * zasielka);
	void spracujObjednavky();

	bool jeVolny() { return !vytazeny_; };
	std::string vytazenyDo() { return vytazenyDo_; };
	std::string getDatumaCasEvidencie() { return datumaCasEvidencie_; }
	bool unesieZasielku(double hmotnostZasielky) { return  nosnost_ >= hmotnostZasielky ? true : false; }

	bool zvladneLet(double vzdialenost) {
		// zohľadniný aj stav nabitia
		return maxDobaLetu_ * (kapacitaBaterie_ / 100) * (primernaRychlost_ / 60.0) / 2 >= vzdialenost ? true : false;
	}

	// NOTE: trvanie cesty tam aj späť
	double trvanieLetu(double vzdialenost) { return (vzdialenost / primernaRychlost_) * 60 * 60 * 2; }

	time_t casPriletuPreZasielku(double vzdialenost) {
		return Datum::string_to_time_t(Datum::getAktualnyDatumaCas()) + ((trvanieLetu(vzdialenost) / 2.0));
	}

	double getAktualnaKapacitaBaterie() {
		return kapacitaBaterie_;
	}
	double getCelkovyPocetNalietanychHodin() {
		return celkovyPocetNalietanychHodin_;
	}
	int getCelkovyPocetPrepravenychZasielok() {
		return celkovyPocetPrepravenychZasielok_;
	}
	int getNosnost() {
		return nosnost_;
	}
	void znizKapacituBaterie(double pocetSekundLetu) {
		kapacitaBaterie_ -= (pocetSekundLetu / 60) * (100.0 / maxDobaLetu_);
	}
	void nabiDrona(double pocetSekundNaNabijacke) {
		// TODO VZOREEEEEEEEEEC
		kapacitaBaterie_ += pocetSekundNaNabijacke;

		// Overflow 
		if (kapacitaBaterie_ > 100) { kapacitaBaterie_ = 100; }
	}

private:
	eDrony typ_;
	structures::ExplicitQueue<Zasielka*> * frontZasielok_;

	std::string datumaCasEvidencie_;
	std::string serioveCislo_;
	bool vytazeny_ = false;
	// TODO vytazenie do ? inicializovane ?
	std::string vytazenyDo_ = Datum::getAktualnyDatumaCas();

	int nosnost_;  //pis to v kilach
	int primernaRychlost_;
	int maxDobaLetu_;
	int casNaNabitie10Percent_;
	double kapacitaBaterie_ = 100.0;
	double celkovyPocetNalietanychHodin_ = 0.0;
	int celkovyPocetPrepravenychZasielok_ = 0;

};

