#include "Objednavka.h"


Objednavka::Objednavka(double hmotnostZasielky, Odosielatel * odosielatel, Adresat * adresat)
{
	hmotnostZasielky_ = hmotnostZasielky;
	odosielatel_ = odosielatel;
	adresat_ = adresat;
}

Objednavka::~Objednavka()
{
	delete odosielatel_;
	delete adresat_;
}


std::string Objednavka::stringStav()
{
	std::string pom;
	switch (stav_) {
	case eStavObjednavky::PRIJATA:
		pom = "PRIJATA";
		break;
	case eStavObjednavky::ZAMIETNUTA:
		pom = "ZAMIETNUTA";
		break;
	case eStavObjednavky::ZRUSENA:
		pom = "ZRUSENA";
		break;
	case eStavObjednavky::ZREALIZOVANA:
		pom = "ZREALIZOVANA";
		break;
	}
	return pom;
}

Odosielatel::Odosielatel(std::string region, double vzdialenostOdPrekladiska)
{
	region_ = region;
	vzdialenostOdPrekladiska_ = vzdialenostOdPrekladiska;
}

Odosielatel::~Odosielatel()
{
}

Adresat::Adresat(std::string region, double vzdialenostOdPrekladiska)
{
	region_ = region;
	vzdialenostOdPrekladiska_ = vzdialenostOdPrekladiska;
}

Adresat::~Adresat()
{
}
