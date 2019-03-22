#include "Vozidlo.h"
#include "structures/heap_monitor.h"


Vozidlo::Vozidlo(int nostnostVozidla, int prevadzkoveNaklady)
{

	//Vozidlo bude vdy obsluhova tú istú trasu (niekedy môe vynecha stredisko, ak tam niè nevezie). Túto mu je potrebné priradi, èo môete spravi dvomi spôsobmi:
	//Pevná trasa mu bude priradená(napr., keï ho vytvorím a vloím do systému, tak mu aj vyberiem / vyskladám trasu, po ktorej bude vdy chodi)
	//Trasa mu bude zakadım poèítaná(ve¾mi pekné a flexibilné riešenie, ale nemusíte to rieši takto)

	celkovaNosnost_ = nostnostVozidla;
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
