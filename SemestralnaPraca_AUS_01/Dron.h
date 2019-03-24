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

// FIXED -> neviem preËo to h·dûe chybu ale
// #include "Firma.h"

class Dron
{
public:
	Dron(const eDrony typDronu, std::string serioveCislo);
	~Dron();
	void pridajObjednavku(Objednavka * objednavka);
	bool jeVolny(std::string cas, double vzdialenost);
	void toString();

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
	time_t ocakavanyCasPriletuPreZasielku(double vzdialenost) {
		return Datum::string_to_time_t(Datum::getAktualnyDatumaCas()) + (trvanieLetu(vzdialenost) / 2.0);
	}
	bool stihnePriletietPreZasielku(double vzdialenost) {
		time_t aktualnyCas = Datum::string_to_time_t(Datum::getAktualnyDatumaCas());

		tm *ltm = localtime(&aktualnyCas);
		struct tm casNajneskor = *ltm;
		casNajneskor.tm_hour = 20;
		casNajneskor.tm_min = 00;

		time_t ocakavanyCasPriletu = ocakavanyCasPriletuPreZasielku(vzdialenost);
		std::cout <<
			(ocakavanyCasPriletu <= mktime(&casNajneskor) ?
				"Predpokladany cas priletu dronu : " + Datum::time_t_to_string(ocakavanyCasPriletu) : "Dron to nestihne") <<
			std::endl;
		return ocakavanyCasPriletu <= mktime(&casNajneskor);
	}
private:
	eDrony typ_;
	structures::ArrayList<Objednavka*> * arrayListObjednavokNaVybavenie;

	std::string datumEvidencie_;
	std::string serioveCislo_;

	int nosnost_;  //pis to v kilach
	int primernaRychlost_;
	int maxDobaLetu_;
	int casNaNabitie10Percent_;
	double aktualnaKapacitaBaterie = 100.0;
	double celkovyPocetNalietanychHodin = 0.0;
	int celkovyPocetPrepravenychZasielok = 0;

};

