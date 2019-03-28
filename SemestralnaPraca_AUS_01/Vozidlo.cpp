#include "structures/heap_monitor.h"
#include "Vozidlo.h"

using namespace std;

Vozidlo::Vozidlo(int nostnostVozidla, int prevadzkoveNaklady, std::string SPZ)
{
	nosnost_ = nostnostVozidla;
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
	delete linkedListTrasaVozidla_;
	delete arrayListZasielok_;
}

void Vozidlo::toString()
{
	std::cout << "Prevazdkove naklady - " << prevadzkoveNaklady_ << "\t SPZ - " << SPZ_ << "\t CELKOVE NAKLADY: " << naklady_ << " " << std::endl;
}

void Vozidlo::pridajPrekladiskoDoTrasyVozidla(Prekladisko* prekladisko) {
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
	// TODO: insert return statement here
	throw std::exception("Dorobit");
}

istream & operator>>(istream & is, Vozidlo & vozidlo)
{
	throw std::exception("Dorobit");
	// TODO: insert return statement here
}
