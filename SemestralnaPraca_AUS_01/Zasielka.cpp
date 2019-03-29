#include "Zasielka.h"

using namespace std;

Zasielka::Zasielka(Objednavka * objednavka)
{
	this->hmotnost_ = objednavka->getHmotnostZasielky();
	this->region_ = objednavka->getOdosielatel()->getRegion();
	this->vzdialenostOdPrekladiska_ = objednavka->getOdosielatel()->getVzdialenostOdPrekladiska();
	this->objednavka_ = objednavka;
	// NOTE: nemusím vedie smer, v sklade iba zmenim region a vzdialenost
	//this->smerZasielky = eSmerZasielky::DO_CENTRALNEHO_SKLADU;
}

Zasielka::~Zasielka()
{
	this->hmotnost_ = 0;
	this->vzdialenostOdPrekladiska_ = 0;
	this->region_ = "";
}


void Zasielka::toString()
{
	cout << "********************* Informacie o zasielke ***********************" << endl;
	cout <<
		"Hmotnost zasielky: " << hmotnost_ << endl <<
		"datumaCasSpracovania_: " << datumaCasSpracovania_ << endl <<
		"datumaCasPrevzatia_: " << datumaCasPrevzatia_ << endl <<
		"datumaCasUkoncenia_: " << datumaCasUkoncenia_ << endl;
	cout << "********************** Pre tuto objednavku ************************" << endl;
	this->objednavka_->toString();
	cout << "*******************************************************************" << endl;
	cout << "*******************************************************************" << endl;
	cout << "*******************************************************************" << endl;
}

ostream & operator<<(ostream & os, Zasielka & zasielka)
{
	// Atributy
	// TODO objednavka
	os << *zasielka.objednavka_ << "\n";

	os <<
		zasielka.vzdialenostOdPrekladiska_ << " " <<
		zasielka.region_ << " " <<
		zasielka.datumaCasSpracovania_ << " " <<
		zasielka.datumaCasPrevzatia_ << " " <<
		zasielka.datumaCasUkoncenia_ << " " << "\n";

	return os;
}

istream & operator>>(istream & is, Zasielka & zasielka)
{
	// TODO: insert return statement here
	return is;
}
