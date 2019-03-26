#pragma once
#pragma warning(disable : 4189) // referenced but not used
#include <string>
#include <iostream>
#include <stdio.h>

#include "structures/heap_monitor.h"
#include "structures/queue/explicit_queue.h"
#include "structures/list/array_list.h"

#include "Konstatnty.h"
#include "Datum.h"
#include "Objednavka.h"

class Dron
{
public:
	Dron(const eDrony typDronu, std::string serioveCislo);
	~Dron();
	void toString();
	void pridajObjednavku(Objednavka * objednavka);
	void spracujObjednavky();
	bool stihnePriletietPreZasielku(double vzdialenost);

	bool jeVolny() {
		return !vytazeny_;
	};

	std::string dronBudeNajblizieVolnyO() {
		//array casov ??? 
	};

	std::string getDatumaCasEvidencie() {
		return datumaCasEvidencie_;
	}

	bool zvladneLet(double vzdialenost) {
		// zohľadniný aj stav nabitia
		return maxDobaLetu_ * (aktualnaKapacitaBaterie_ / 100) * (primernaRychlost_ / 60.0) / 2 >= vzdialenost ? true : false;
	}
	bool unesieZasielku(double hmotnostZasielky) {
		return  nosnost_ >= hmotnostZasielky ? true : false;
	}
	// NOTE: trvanie cesty tam aj späť
	double trvanieLetu(double vzdialenost) {
		return (vzdialenost / primernaRychlost_) * 60 * 60 * 2;
	}
	time_t casPriletuPreZasielku(double vzdialenost) {
		return Datum::string_to_time_t(Datum::getAktualnyDatumaCas()) + (trvanieLetu(vzdialenost) / 2.0);
	}
	double getAktualnaKapacitaBaterie() {
		return aktualnaKapacitaBaterie_;
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


private:
	eDrony typ_;
	structures::ExplicitQueue<Objednavka*> * frontObjednavok;

	std::string datumaCasEvidencie_;
	std::string serioveCislo_;
	bool vytazeny_ = false;

	int nosnost_;  //pis to v kilach
	int primernaRychlost_;
	int maxDobaLetu_;
	int casNaNabitie10Percent_;
	double aktualnaKapacitaBaterie_ = 100.0;
	double celkovyPocetNalietanychHodin_ = 0.0;
	int celkovyPocetPrepravenychZasielok_ = 0;

};

