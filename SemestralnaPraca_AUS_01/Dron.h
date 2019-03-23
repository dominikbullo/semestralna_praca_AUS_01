#pragma once
#pragma warning(disable : 4189) // referenced but not used
#include <string>
#include <iostream>
#include <stdio.h>

#include "structures/heap_monitor.h"
#include "Konstatnty.h"
#include "Datum.h"

// FIXED -> neviem preèo to hádže chybu ale
// #include "Firma.h"

class Dron
{
public:
	Dron(const eDrony typDronu, std::string serioveCislo);
	~Dron();
	void toString();

	bool zvladneLet(double vzdialenost) {
		// zoh¾adniný aj stav nabitia
		return maxDobaLetu_ * (aktualnaKapacitaBaterie / 100) * (primernaRychlost_ / 60.0) / 2 >= vzdialenost ? true : false;
	}
	bool unesieZasielku(double hmotnostZasielky) {
		return  nosnost_ >= hmotnostZasielky ? true : false;
	}
	bool stihnePriletietPreZasielku(double vzdialenost) {
		time_t aktualnyCas = Datum::string_to_time_t(Datum::getAktualnyDatumaCas());

		tm *ltm = localtime(&aktualnyCas);
		struct tm casNajneskor = *ltm;
		casNajneskor.tm_hour = 20;
		casNajneskor.tm_min = 00;

		// t=s/v
		// nejaký static/dynamic cast -> warning -> POSSIBLE LOSS OF DATA
		time_t ocakavanyCasPriletu = aktualnyCas + (vzdialenost / primernaRychlost_) * 60 * 60;
		std::cout <<
			(ocakavanyCasPriletu <= mktime(&casNajneskor) ?
				"Predpokladany cas priletu dronu : " + Datum::time_t_to_string(ocakavanyCasPriletu) :
				"Dron to nestihne") << std::endl;
		return ocakavanyCasPriletu <= mktime(&casNajneskor);
	}
private:
	eDrony typ_;
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

