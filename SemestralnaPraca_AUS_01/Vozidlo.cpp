#include "Vozidlo.h"
#include "structures/heap_monitor.h"

using namespace std;

Vozidlo::Vozidlo(int nostnostVozidla, int prevadzkoveNaklady, std::string SPZ)
{
	nosnost_ = nostnostVozidla;
	prevadzkoveNaklady_ = prevadzkoveNaklady;
	SPZ_ = SPZ;
	datumaCasEvidencie_ = Datum::getAktualnyDatumaCas();
	// Zmenil som Linked na Array - POZOR 
	linkedListTrasaVozidla = new structures::ArrayList<Prekladisko*>();
}

Vozidlo::~Vozidlo()
{
	delete linkedListTrasaVozidla;
}

void Vozidlo::toString()
{
	std::cout << "Prevazdkove naklady - " << prevadzkoveNaklady_ << "\t SPZ - " << SPZ_ << "\t CELKOVE NAKLADY: " << naklady_ << " " << std::endl;
}

void Vozidlo::pridajPrekladiskoDoTrasyVozidla(Prekladisko* prekladisko) {
	linkedListTrasaVozidla->add(prekladisko);
}