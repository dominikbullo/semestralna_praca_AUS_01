#include "Objednavka.h"

using namespace std;
Objednavka::Objednavka(double hmotnostZasielky, Odosielatel * odosielatel, Adresat * adresat)
{
	hmotnostZasielky_ = hmotnostZasielky;
	odosielatel_ = odosielatel;
	adresat_ = adresat;
	datumaCasVytvoreniaObjednavky_ = Datum::getAktualnyDatumaCas();
	//datumaCasSpracovania_ = Datum::getAktualnyDatumaCas();
	//datumaCasUkonCenia = Datum::getAktualnyDatumaCas();
}

Objednavka::~Objednavka()
{
	delete odosielatel_;
	delete adresat_;
}
string Objednavka::getCasDokonceniaObjednavky(time_t casLetu, double vzdialenost)
{
	time_t aktualnyCas = Datum::string_to_time_t(Datum::getAktualnyDatumaCas());
	return Datum::time_t_to_string(aktualnyCas + casLetu);
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

void Objednavka::toString()
{
	cout << "*****************************************************************" << endl;
	cout <<
		"Hmotnost zasielky: " << hmotnostZasielky_ << endl <<
		"Region odosielatela: " << odosielatel_->getRegion() << endl <<
		"Vzdialenost odosielatela od prekladiska: " << odosielatel_->getVzdialenostOdPrekladiska() << endl <<
		"Region adresata: " << adresat_->getRegion() << endl <<
		"Vzdialenost adresata od prekladiska: " << adresat_->getVzdialenostOdPrekladiska() << endl <<
		"Datum a cas vytvorenia zasielky: " << datumaCasVytvoreniaObjednavky_ << endl <<
		"Stav: " << stringStav() << endl;
	cout << "*****************************************************************" << endl;


}

Odosielatel::Odosielatel(std::string region, double vzdialenostOdPrekladiska)
{
	region_ = region;
	vzdialenostOdPrekladiska_ = vzdialenostOdPrekladiska;
}

Adresat::Adresat(std::string region, double vzdialenostOdPrekladiska)
{
	region_ = region;
	vzdialenostOdPrekladiska_ = vzdialenostOdPrekladiska;
}
