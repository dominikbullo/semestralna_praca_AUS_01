#include "structures/heap_monitor.h"
#include "Vozidlo.h"
// moze
#include "Firma.h"

using namespace std;

Vozidlo::Vozidlo(double nostnostVozidla, int prevadzkoveNaklady, std::string SPZ)
{
	aktualnaNosnost_ = nostnostVozidla; //v kilogramoch!
	maxNosnost_ = nostnostVozidla;
	prevadzkoveNaklady_ = prevadzkoveNaklady;
	SPZ_ = SPZ;
	datumaCasEvidencie_ = Datum::getAktualnyDatumaCas();

	linkedListTrasaVozidla_ = new structures::LinkedList<Prekladisko*>();
	arrayListZasielok_ = new structures::ArrayList<Zasielka*>();
}

Vozidlo::~Vozidlo()
{
	for (Zasielka* zasielka : *arrayListZasielok_)
	{
		delete zasielka;
	}
	delete arrayListZasielok_;

	delete linkedListTrasaVozidla_;
}

void Vozidlo::toString()
{
	std::cout << "Prevazdkove naklady - " <<
		prevadzkoveNaklady_ << "\t SPZ - " <<
		SPZ_ << "\t CELKOVE NAKLADY: " <<
		naklady_ << " " << std::endl;
}

void Vozidlo::pridajZasielkuDoVozidla(Zasielka * zasielka)
{
	this->arrayListZasielok_->add(zasielka);
}
void Vozidlo::pridajPrekladiskoDoTrasyVozidla(Prekladisko* prekladisko)
{
	linkedListTrasaVozidla_->add(prekladisko);
}

void Vozidlo::vypisZasielkyVozidla()
{
	for (Zasielka *zasielka : *arrayListZasielok_)
	{
		zasielka->toString();
	}
}

ostream & operator<<(ostream & os, Vozidlo & vozidlo)
{
	// Atributy
	os <<
		vozidlo.aktualnaNosnost_ << " " <<
		vozidlo.prevadzkoveNaklady_ << " " <<
		vozidlo.SPZ_ << " " <<
		vozidlo.maxNosnost_ << " " <<

		vozidlo.datumaCasEvidencie_ << " " <<
		vozidlo.naklady_ << " "  "\n";

	// Struktury 
	// TODO staèi regiony
	os << vozidlo.linkedListTrasaVozidla_->size() << "\n";
	for (Prekladisko * var : *vozidlo.linkedListTrasaVozidla_) {
		os << var->dajRegion() << " ";
	}
	os << "\n" << vozidlo.arrayListZasielok_->size() << "\n";
	for (Zasielka * var : *vozidlo.arrayListZasielok_) {
		os << *var;
	}

	os << "\n";
	return os;
}

istream & operator>>(istream & is, Vozidlo & vozidlo)
{
	std::string datum, pom, cas;
	double maxNosnost, naklady;
	is >> maxNosnost >> datum >> pom >> cas >> naklady;

	vozidlo.maxNosnost_ = maxNosnost;
	vozidlo.datumaCasEvidencie_ = datum + " " + pom + " " + cas;
	vozidlo.naklady_;

	return is;
}
