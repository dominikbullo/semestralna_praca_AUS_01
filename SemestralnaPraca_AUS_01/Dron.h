#pragma once
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
	bool stihnePriletietPreZasielku(Zasielka * zasielka);
	void prepocitajInformacieoDosupnosti();
	void pridajZasielku(Zasielka * zasielka);
	void spracujObjednavky();
	bool jeVolny() { return !vytazeny_; };

	std::string vytazenyDo() { return vytazenyDo_; };
	std::string getDatumaCasEvidencie() { return datumaCasEvidencie_; }

	bool unesieZasielku(Zasielka * zasielka) { return  nosnost_ >= zasielka->getHmotnost() ? true : false; }
	bool zvladneLet(Zasielka * zasielka) { return maxDobaLetu_ * (kapacitaBaterie_ / 100) * (primernaRychlost_ / 60.0) / 2 >= zasielka->getVzdialenost() ? true : false; }
	double trvanieLetu(Zasielka* zasielka) { return (zasielka->getVzdialenost() / primernaRychlost_) * 60 * 60 * 2; }


	time_t casPriletuPreZasielku(Zasielka * zasielka)
	{
		auto test1 = Datum::string_to_time_t(vytazenyDo_);
		auto test2 = getCasPotrebnyNaDobitie(getPocetPercentNaZvladnutieLetu(zasielka));
		auto test3 = trvanieLetu(zasielka) / 2.0;
		return Datum::string_to_time_t(vytazenyDo_) +
			getCasPotrebnyNaDobitie(getPocetPercentNaZvladnutieLetu(zasielka)) +
			(trvanieLetu(zasielka) / 2.0);
	}

	double getAktualnaKapacitaBaterie() { return kapacitaBaterie_; }
	double getCelkovyPocetNalietanychHodin() { return celkovyPocetNalietanychHodin_; }
	int getCelkovyPocetPrepravenychZasielok() { return celkovyPocetPrepravenychZasielok_; }
	int getNosnost() { return nosnost_; }
	void znizKapacituBaterie(double pocetSekundLetu) { kapacitaBaterie_ -= (pocetSekundLetu / 60) * (100.0 / maxDobaLetu_); }
	double getCasPotrebnyNaDobitie(double potrebnyPocetPercent);
	double getPocetPercentNaZvladnutieLetu(Zasielka* zasielka);


	void nabiDrona(double pocetSekundNaNabijacke)
	{
		double pocetPercetDobitia = (pocetSekundNaNabijacke / 60) / (10 / casNaNabitie10Percent_ * 60);
		(kapacitaBaterie_ + pocetPercetDobitia > 100) ? kapacitaBaterie_ = 100 : kapacitaBaterie_ += pocetPercetDobitia;
	}

private:
	eDrony typ_;
	bool vytazeny_ = false;
	structures::ExplicitQueue<Zasielka*> * frontZasielok_;

	std::string datumaCasEvidencie_;
	std::string serioveCislo_;
	std::string vytazenyDo_ = Datum::getAktualnyDatumaCas();

	int nosnost_;  //pis to v kilach
	int primernaRychlost_;
	int maxDobaLetu_;
	int casNaNabitie10Percent_;
	double kapacitaBaterie_ = 100.0;
	double celkovyPocetNalietanychHodin_ = 0.0;
	int celkovyPocetPrepravenychZasielok_ = 0;
};

