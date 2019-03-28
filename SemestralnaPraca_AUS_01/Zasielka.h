#pragma once
#include <string>
#include <iostream>
#include "Konstatnty.h"
#include "Objednavka.h"
// NO WAY!
//#include "Prekladisko.h"
using namespace std;
class Zasielka
{
public:
	Zasielka(double hmotnost, Objednavka* objednavka);
	~Zasielka();
	void toString();

	// SETTERS
	void setDatumaCasSpracovania(std::string datum_a_cas) { datumaCasSpracovania_ = datum_a_cas; }
	void setdatumaCasPrevzatia(std::string datum_a_cas) { datumaCasPrevzatia_ = datum_a_cas; }
	void setDatumaCasUkoncenia(std::string datum_a_cas) { datumaCasUkoncenia_ = datum_a_cas; }
	//void setPrekladisko(Prekladisko * prekladisko) { prekladisko_ = prekladisko; }

	// GETTERS
	string getDatumaCasSpracovania() { return datumaCasSpracovania_; }
	string getdatumaCasUkoncenia_() { return datumaCasUkoncenia_; }
	double getHmotnost() { return hmotnost_; }
	double getVzdialenost() { return vzdialenostOdPrekladiska_; }
	std::string getRegion() { return region_; }


private:
	Objednavka* objednavka_;
	double hmotnost_;
	double vzdialenostOdPrekladiska_;
	std::string region_; // prekladisko, ktor� moment�lne spravuje z�sielku

	std::string datumaCasSpracovania_;
	std::string datumaCasPrevzatia_;
	std::string datumaCasUkoncenia_;
	eStavObjednavky stav_;
};

