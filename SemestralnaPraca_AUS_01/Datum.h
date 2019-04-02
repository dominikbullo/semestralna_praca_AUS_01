#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "Konstatnty.h"

class Datum
{
public:
	static Datum* getInstance()
	{
		if (instance == 0)
		{
			instance = new Datum();
		}

		return instance;
	}

	//Datum* get();
	static std::string getAktualnyDatumaCas() {
		return datum_a_cas_;
	}
	static time_t getAktualnyDatumaCasAsTime() {
		return Datum::string_to_time_t(datum_a_cas_);
	}
	void posunCas(int pocetSekund);
	std::string pridajCas(int pocetMinut) {
		return Datum::time_t_to_string(Datum::string_to_time_t(Datum::getAktualnyDatumaCas()) + (pocetMinut * 60));
	}

	static std::string time_t_to_string(time_t t);
	static time_t string_to_time_t(std::string s);
	void static posunCasNaUrcituHodinu(eOtvoracieHodiny celaHodina);
private:
	static std::string datum_a_cas_;
	static tm *ltm_;
	static Datum * instance;
	Datum();
	Datum(Datum const& copy);
};

