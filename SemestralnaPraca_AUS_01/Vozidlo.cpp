#include "Vozidlo.h"
#include "structures/heap_monitor.h"


Vozidlo::Vozidlo(int nostnostVozidla, int prevadzkoveNaklady)
{
	nosnost_ = nostnostVozidla;
	prevadzkoveNaklady_ = prevadzkoveNaklady;
	setSPZ();
}

int Vozidlo::unikatnostSPZ_ = 000;

Vozidlo::~Vozidlo()
{
}

void Vozidlo::toString()
{
	std::cout << "Prevazdkove naklady - " << prevadzkoveNaklady_ << "\t SPZ - " << SPZ_ << "\t NAKLADY: " << naklady_ << " " << std::endl;
}

void Vozidlo::setSPZ()
{
	int pom = ++unikatnostSPZ_;
	std::string formated = std::string(3 - std::to_string(pom).length(), '0') + std::to_string(pom);
	// TODO maybe better SPZ
	SPZ_ += formated + "CF";
}
