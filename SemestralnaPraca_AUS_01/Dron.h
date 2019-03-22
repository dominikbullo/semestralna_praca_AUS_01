#pragma once
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
	Dron(const eDrony typDronu);
	~Dron();
	void toString();

	bool zvladneLet(double vzdialenost) {
		// TODO zoh¾adni stav nabitia
		return maxDobaLetu_ * (aktualnaKapacitaBaterie / 100) * (primernaRychlost_ / 60.0) / 2 >= vzdialenost ? true : false;
	}
	bool unesieZasielku(double hmotnostZasielky) {
		return  nosnost_ >= hmotnostZasielky ? true : false;
	}
	bool stihnePriletietPreZasielku(double vzdialenost) {
		// TODO vypoèíta èi to stihne do 20:00, prida èas do parametrov metódy
		// zober si èas -> ak je po 20:00 a menej ako 7:00 ani nerieš
		// vypoèítaj èas potrebný na let k danému miestu
		//maxDobaLetu_ * (aktualnaKapacitaBaterie / 100) * (primernaRychlost_ / 60.0) / 2

		return true;
	}
private:
	eDrony typ_;
	std::string datumEvidencie_;

	int nosnost_;  //pis to v kilach
	int primernaRychlost_;
	int maxDobaLetu_;
	int casNaNabitie10Percent_;
	double aktualnaKapacitaBaterie = 100.0;
	double celkovyPocetNalietanychHodin = 0.0;
	int celkovyPocetPrepravenychZasielok = 0;

};

