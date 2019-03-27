#include "Zasielka.h"

using namespace std;


Zasielka::Zasielka(double hmotnost, double vzdialenost, std::string region)
{
	this->hmotnost_ = hmotnost;
	this->vzdialenostOdPrekladiska_;
	this->region_ = region;
}

Zasielka::~Zasielka()
{
}


void Zasielka::toString()
{
	cout << "******************** Informacie o objednavke **********************" << endl;
	cout <<
		"Hmotnost zasielky: " << hmotnost_ << endl <<
		"datumaCasSpracovania_: " << datumaCasSpracovania_ << endl <<
		"datumaCasUkoncenia_: " << datumaCasUkoncenia_ << endl;
	cout << "*******************************************************************" << endl;
}
