#include "Vozidlo.h"
#include "structures/heap_monitor.h"

using namespace std;

Vozidlo::Vozidlo(int nostnostVozidla, int prevadzkoveNaklady, std::string SPZ)
{
	//Vozidlo bude vdy obsluhova tú istú trasu (niekedy môe vynecha stredisko, ak tam niè nevezie). Túto mu je potrebné priradi, èo môete spravi dvomi spôsobmi:
	//Pevná trasa mu bude priradená(napr., keï ho vytvorím a vloím do systému, tak mu aj vyberiem / vyskladám trasu, po ktorej bude vdy chodi)
	//Trasa mu bude zakadım poèítaná(ve¾mi pekné a flexibilné riešenie, ale nemusíte to rieši takto)

	celkovaNosnost_ = nostnostVozidla;
	prevadzkoveNaklady_ = prevadzkoveNaklady;
	SPZ_ = SPZ;
	datumaCasEvidencie_ = Datum::getAktualnyDatumaCas();
	linkedListTrasaVozidla = new structures::LinkedList<string>();
	this->pridajRegionyDoTrasyVozidla();
}

Vozidlo::~Vozidlo()
{
	delete linkedListTrasaVozidla;
}

void Vozidlo::toString()
{
	std::cout << "Prevazdkove naklady - " << prevadzkoveNaklady_ << "\t SPZ - " << SPZ_ << "\t CELKOVE NAKLADY: " << naklady_ << " " << std::endl;
}

void Vozidlo::pridajRegionyDoTrasyVozidla() {
	// TODO: POMOOOOOOOOOOOOOOOOOOOOOOOOC

	string userInput;
	while (userInput != "0") {
		cout << "Ktory region chces pridat do trasy vozidla - " << SPZ_ << " " << endl;
		cin >> userInput;
		if (userInput != "0") {
			linkedListTrasaVozidla->add(userInput);
		}
	}
	return;
}