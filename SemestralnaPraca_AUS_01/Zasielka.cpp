#include "Zasielka.h"

using namespace std;


Zasielka::Zasielka(double hmotnost, double vzdialenost, std::string region)
{
	this->hmotnost_ = hmotnost;
	this->vzdialenostOdPrekladiska_ = vzdialenost;
	this->region_ = region;
}

Zasielka::~Zasielka()
{
}


void Zasielka::toString()
{
	cout << "******************** Informacie o zasielkeke **********************" << endl;
	cout <<
		"Hmotnost zasielky: " << hmotnost_ << endl <<
		"datumaCasSpracovania_: " << datumaCasSpracovania_ << endl <<
		"datumaCasPrevzatia_: " << datumaCasPrevzatia_ << endl <<
		"datumaCasUkoncenia_: " << datumaCasUkoncenia_ << endl;
	cout << "*******************************************************************" << endl;
}
