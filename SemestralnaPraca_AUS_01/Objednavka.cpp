#include "Objednavka.h"

using namespace std;
Objednavka::Objednavka(double hmotnostZasielky, Odosielatel * odosielatel, Adresat * adresat)
{
	hmotnostZasielky_ = hmotnostZasielky;
	odosielatel_ = odosielatel;
	adresat_ = adresat;
	datumaCasVytvoreniaObjednavky_ = Datum::getAktualnyDatumaCas();
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
	case eStavObjednavky::DORUCENA:
		pom = "DORUCENA";
		break;
	}
	return pom;
}

void Objednavka::toString()
{
	cout << "******************** Informacie o objednavke **********************" << endl;
	cout <<
		"Hmotnost zasielky: " << hmotnostZasielky_ << endl <<
		"Region odosielatela: " << odosielatel_->getRegion() << endl <<
		"Vzdialenost odosielatela od prekladiska: " << odosielatel_->getVzdialenostOdPrekladiska() << endl <<
		"Region adresata: " << adresat_->getRegion() << endl <<
		"Vzdialenost adresata od prekladiska: " << adresat_->getVzdialenostOdPrekladiska() << endl <<
		"Datum a cas vytvorenia objednavky: " << datumaCasVytvoreniaObjednavky_ << endl <<
		"Datum a cas spracovania objednavky: " << datumaCasSpracovania_ << endl <<
		//"Datum a cas ukoncenia zasielky: " << datumaCasUkoncenia_ << endl <<
		"Stav: " << stringStav() << endl <<
		(stav_ == eStavObjednavky::ZAMIETNUTA ? "Dovod zamietnutia: " + dovodZamietnutia_ : "")
		<< endl;
	cout << "*******************************************************************" << endl;


}

void Objednavka::zamietniObjednavku(string dovodZamietnutia)
{
	this->stav_ = eStavObjednavky::ZAMIETNUTA;
	this->dovodZamietnutia_ = dovodZamietnutia;
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

ostream & operator<<(ostream & os, Objednavka & objednavka)
{
	os <<
		objednavka.hmotnostZasielky_ << " " <<
		objednavka.odosielatel_->getRegion() << " " <<
		objednavka.odosielatel_->getVzdialenostOdPrekladiska() << " " <<
		objednavka.adresat_->getRegion() << " " <<
		objednavka.adresat_->getVzdialenostOdPrekladiska() << " " <<
		objednavka.datumaCasVytvoreniaObjednavky_ << " " <<
		(int)objednavka.stav_ << " " <<
		// NOTE pozor na to - niekedy je, niekedy nie 
		objednavka.dovodZamietnutia_ << " " <<
		// NOTE pozor na to - niekedy je, niekedy nie 
		objednavka.datumaCasSpracovania_ << " " << "\n";
	return os;
}
istream & operator>>(istream & is, Objednavka & objednavka)
{
	std::string datum, pom, cas;

	is >> datum >> pom >> cas;
	objednavka.datumaCasVytvoreniaObjednavky_ = datum + " " + pom + " " + cas;

	int pomStav;
	is >> pomStav;
	objednavka.stav_ = (eStavObjednavky)pomStav;

	if (objednavka.stav_ == eStavObjednavky::ZRUSENA)
	{
		return is;
	}
	if (objednavka.stav_ == eStavObjednavky::ZAMIETNUTA)
	{
		// TODO dovod zamietnutia pokracovat ? poradie ? 
		return is;
	}

	is >> datum >> pom >> cas;
	objednavka.datumaCasSpracovania_ = datum + " " + pom + " " + cas;

	return is;
}

