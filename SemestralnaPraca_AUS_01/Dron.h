#pragma once
#include <string>
#include <iostream>
#include <stdio.h>

#include "structures/heap_monitor.h"
#include "Konstatnty.h"
#include "Datum.h"
#include "Firma.h"

class Dron
{
public:
	Dron(const eDrony typDronu);
	~Dron();
	void toString();

	inline bool zvladneLet(double vzdialenost) {
		// TODO zohæadniù stav nabitia
		return maxDobaLetu_ * (aktualnaKapacitaBaterie / 100) * (primernaRychlost_ / 60.0) / 2 >= vzdialenost ? true : false;
	}
	inline bool unesieZasielku(double hmotnostZasielky) {
		return  nosnost_ >= hmotnostZasielky ? true : false;
	}
	inline bool stihnePriletietPreZasielku(double vzdialenost) {
		// TODO vypoËÌtaù Ëi to stihne do 20:00, pridaù Ëas do parametrov metÛdy
		return  true;
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

