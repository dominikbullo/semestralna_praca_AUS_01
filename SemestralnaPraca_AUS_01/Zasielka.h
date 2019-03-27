#pragma once
#include <string>
#include <iostream>
#include "Konstatnty.h"
// NO WAY!
//#include "Prekladisko.h"
using namespace std;
class Zasielka
{
public:
	Zasielka(double hmotnost, double vzdialenost, std::string region);
	~Zasielka();
	void toString();
	void setDatumaCasSpracovania_(std::string datum_a_cas) {
		datumaCasSpracovania_ = datum_a_cas;
	}
	void setDatumaCasUkoncenia_(std::string datum_a_cas) {
		datumaCasUkoncenia_ = datum_a_cas;
	}

	double getHmotnost() { return hmotnost_; }
	double getVzdialenost() { return vzdialenostOdPrekladiska_; }

	std::string getRegion() { return region_; }
	//void setPrekladisko(Prekladisko * prekladisko) { prekladisko_ = prekladisko; }

private:
	double hmotnost_;
	double vzdialenostOdPrekladiska_;
	std::string region_; // prekladisko, ktoré momentálne spravuje zásielku

	std::string datumaCasSpracovania_;
	std::string datumaCasUkoncenia_;
	eStavObjednavky stav_;
};

