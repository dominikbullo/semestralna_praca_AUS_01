#include "structures/heap_monitor.h"
#include "Vozidlo.h"

using namespace std;

Vozidlo::Vozidlo(int nostnostVozidla, int prevadzkoveNaklady, std::string SPZ)
{
	nosnost_ = nostnostVozidla;
	prevadzkoveNaklady_ = prevadzkoveNaklady;
	SPZ_ = SPZ;
	datumaCasEvidencie_ = Datum::getAktualnyDatumaCas();

	linkedListTrasaVozidla = new structures::LinkedList<Prekladisko*>();
	arrayListZasielok = new structures::ArrayList<Zasielka*>();
}

Vozidlo::~Vozidlo()
{
	for (Zasielka* zasielka : *arrayListZasielok)
	{
		delete zasielka;
	}
	delete linkedListTrasaVozidla;
	delete arrayListZasielok;
}

void Vozidlo::toString()
{
	std::cout << "Prevazdkove naklady - " << prevadzkoveNaklady_ << "\t SPZ - " << SPZ_ << "\t CELKOVE NAKLADY: " << naklady_ << " " << std::endl;
}

void Vozidlo::pridajPrekladiskoDoTrasyVozidla(Prekladisko* prekladisko) {
	linkedListTrasaVozidla->add(prekladisko);
}

void Vozidlo::vypisZasielkyVozidla()
{
	for (Zasielka *zasielka : *arrayListZasielok)
	{
		zasielka->toString();
	}
}