#include "Vozidlo.h"
#include "structures/heap_monitor.h"


Vozidlo::Vozidlo(int nostnostVozidla, int prevadzkoveNaklady)
{
	nosnost_ = nostnostVozidla;
	prevadzkoveNaklady_ = prevadzkoveNaklady;
	datumEvidencie_ = Datum::getAktualnyDatum();
	setSPZ();
}

int Vozidlo::unikatnostSPZ_ = 000;

Vozidlo::~Vozidlo()
{
}

void Vozidlo::toString()
{
	std::cout << "Prevazdkove naklady - " << prevadzkoveNaklady_ << "\t SPZ - " << SPZ_ << "\t CELKOVE NAKLADY: " << naklady_ << " " << std::endl;
}

void Vozidlo::setSPZ()
{
	int pom = ++unikatnostSPZ_;
	//const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";


	std::string lastLettersSPZ = "_AA";
	std::string formated = std::string(3 - std::to_string(pom).length(), '0') + std::to_string(pom);

	// TODO maybe better SPZ
	/*if (pom >= 1000) {
		std::string lastLettersSPZ = "AA";
	}*/
	SPZ_ += formated + lastLettersSPZ;
}
