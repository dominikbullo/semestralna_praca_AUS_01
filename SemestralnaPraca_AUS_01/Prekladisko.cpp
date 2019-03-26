#include<iostream> 
#include<algorithm> 

#include "Prekladisko.h"
#include "Dron.h"

int Prekladisko::unikatneSerioveCislo_ = 000000;

Prekladisko::Prekladisko(std::string region)
{
	unikatneSerioveCislo_ = 000000;
	region_ = region;
	arrayListDronov_ = new structures::ArrayList<Dron*>();


	// prekladisko má vždy aspoň pár dronov pri vytváraní
	this->pridajDron(new Dron(eDrony::JEDEN, set_get_SerioveCislo()));
	this->pridajDron(new Dron(eDrony::DVA, set_get_SerioveCislo()));
	this->pridajDron(new Dron(eDrony::DVA, set_get_SerioveCislo()));
}

Prekladisko::~Prekladisko()
{
	for (Dron * dron : *arrayListDronov_) {
		delete dron;
	}
	delete arrayListDronov_;

}

void Prekladisko::pridajDron(Dron * novyDron)
{
	for (int i = 0; i < arrayListDronov_->size(); i++)
	{
		if (arrayListDronov_->operator[](i)->getDatumaCasEvidencie() > novyDron->getDatumaCasEvidencie())
		{
			arrayListDronov_->insert(novyDron, i);
			return;
		}

	}
	arrayListDronov_->add(novyDron);
}


void Prekladisko::vypisZoznamDronov() {
	std::cout << "Vypisujem vsetkych dronov pre prekladisko z okresu - " << region_ << std::endl;
	for (Dron * dron : *arrayListDronov_) {
		dron->toString();
	}
}

Dron * Prekladisko::vyberDrona(double hmotnostZasielky, double vzdialenost, string casVytvoreniaObjednavky)
{
	//Ak sú všetky drony, ktoré sa nachádzajú v lokálnom prekladisku, 
	// aktuálne vyťažené alebo majú naplánovanú už inú akciu, je vypočítaný čas, 
	// za ktorý sa môže dostať dron, ktorý dokáže vyzdvihnúť danú zásielku a 
	// ktorý ako prvý dokončí svoju aktuálne vykonávanú úlohu, k odosielateľovi.
	//Ak je tento čas väčší ako jedna hodina, zákazník je o tom informovaný a 
	// objednávku môže zrušiť. Ak objednávku nezruší, tak bude obslúžený vyššie uvedeným dronom.
	Dron* kandidatNaDrona = nullptr;
	for (Dron * dron : *arrayListDronov_) {
		// v príapde, že dron nespĺňa tieto podmienky, nie je žiadnym spôsobom možné, že by mohol ttúto zásielku doručiť
		if (!dron->unesieZasielku(hmotnostZasielky) ||
			!dron->zvladneLet(vzdialenost) ||
			!dron->stihnePriletietPreZasielku(vzdialenost)) {
			continue;
		}
		if (dron->jeVolny()) {
			kandidatNaDrona = dajLelpšiehoDrona(dron, kandidatNaDrona);
			continue;
		}
		else
		{
			//poznač si, že nemáš voľného -> ale zvláda podmienky
			continue;
		}

	}
	//kandidatNaDrona == nullptr ? "treba bypocitat cas " : mam volneho drona;
	//std::cout << "Takuto objednavku nezvladne dorucit ziaden dron" << std::endl;
	return (kandidatNaDrona == nullptr) ? NULL : kandidatNaDrona;
}

Dron* Prekladisko::dajLelpšiehoDrona(Dron* dron1, Dron* dron2) {
	// TODO porovnávať časi, možného príletu
	if (dron1 == nullptr) { return dron2; }
	if (dron2 == nullptr) { return dron1; }

	if (dron1->getNosnost() == dron2->getNosnost()) {
		return dron1->getAktualnaKapacitaBaterie() > dron2->getAktualnaKapacitaBaterie() ? dron1 : dron2;
	}
	return dron1->getNosnost() < dron2->getNosnost() ? dron1 : dron2;
}

std::string Prekladisko::set_get_SerioveCislo()
{
	int pom = ++unikatneSerioveCislo_;
	std::string formated = std::string(6 - std::to_string(pom).length(), '0') + std::to_string(pom);
	serioveCislo_ = region_ + formated;
	return serioveCislo_;
}

