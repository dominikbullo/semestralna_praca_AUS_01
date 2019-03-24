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
	void pridajObjednavku(Objednavka * objednavka);
	void toString();
	bool stihnePriletietPreZasielku(double vzdialenost);

	bool jeVolny() {
		return vytazeny_;
	};

	std::string dronBudeNajblizieVolnyO() {
		//array casov ??? 
	};

	bool zvladneLet(double vzdialenost) {
		// zohæadnin˝ aj stav nabitia
		return maxDobaLetu_ * (aktualnaKapacitaBaterie / 100) * (primernaRychlost_ / 60.0) / 2 >= vzdialenost ? true : false;
	}
	bool unesieZasielku(double hmotnostZasielky) {
		return  nosnost_ >= hmotnostZasielky ? true : false;
	}
	// NOTE: trvanie cesty tam aj sp‰ù
	double trvanieLetu(double vzdialenost) {
		return (vzdialenost / primernaRychlost_) * 60 * 60 * 2;
	}
	time_t casPriletuPreZasielku(double vzdialenost) {
		return Datum::string_to_time_t(Datum::getAktualnyDatumaCas()) + (trvanieLetu(vzdialenost) / 2.0);
	}


private:
	eDrony typ_;
	structures::ArrayList<Objednavka*> * arrayListObjednavokNaVybavenie;

	std::string datumEvidencie_;
	std::string serioveCislo_;
	bool vytazeny_ = false;

	int nosnost_;  //pis to v kilach
	int primernaRychlost_;
	int maxDobaLetu_;
	int casNaNabitie10Percent_;
	double aktualnaKapacitaBaterie = 100.0;
	double celkovyPocetNalietanychHodin = 0.0;
	int celkovyPocetPrepravenychZasielok = 0;

};

