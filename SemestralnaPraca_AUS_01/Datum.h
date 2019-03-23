#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
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

	void posunCasoHodinu(int pocetSekund);
	//Datum* get();
	static std::string getAktualnyDatumaCas() {
		return datum_a_cas_;
	}

	static std::string time_t_to_string(time_t t);
	static time_t string_to_time_t(std::string s);
private:
	static std::string datum_a_cas_;
	static tm *ltm_;
	static Datum * instance;
	Datum();
	Datum(Datum const& copy);
};


