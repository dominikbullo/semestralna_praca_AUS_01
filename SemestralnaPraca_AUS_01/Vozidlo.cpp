#include "Vozidlo.h"
#include "structures/heap_monitor.h"


Vozidlo::Vozidlo(int nostnostVozidla, int prevadzkoveNaklady, std::string SPZ)
{

	//Vozidlo bude vdy obsluhova tú istú trasu (niekedy môe vynecha stredisko, ak tam niè nevezie). Túto mu je potrebné priradi, èo môete spravi dvomi spôsobmi:
	//Pevná trasa mu bude priradená(napr., keï ho vytvorím a vloím do systému, tak mu aj vyberiem / vyskladám trasu, po ktorej bude vdy chodi)
	//Trasa mu bude zakadım poèítaná(ve¾mi pekné a flexibilné riešenie, ale nemusíte to rieši takto)

	celkovaNosnost_ = nostnostVozidla;
	prevadzkoveNaklady_ = prevadzkoveNaklady;
	datumaCasEvidencie_ = Datum::getAktualnyDatum();
	SPZ_ = SPZ;
}

int Vozidlo::unikatnostSPZ_ = 000;

Vozidlo::~Vozidlo()
{
}

void Vozidlo::toString()
{
	std::cout << "Prevazdkove naklady - " << prevadzkoveNaklady_ << "\t SPZ - " << SPZ_ << "\t CELKOVE NAKLADY: " << naklady_ << " " << std::endl;
}