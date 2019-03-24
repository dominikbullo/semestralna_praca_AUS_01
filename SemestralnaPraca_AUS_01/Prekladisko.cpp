#include<iostream> 
#include<algorithm> 

#include "Prekladisko.h"
#include "Dron.h"

int Prekladisko::unikatneSerioveCislo_ = 000000;

Prekladisko::Prekladisko(std::string region)
{
	unikatneSerioveCislo_ = 000000;
	region_ = region;
	arrayListDronov = new structures::ArrayList<Dron*>();

	// evidujem čakajúce objednávky v skladisku
	frontObjednavok = new structures::ExplicitQueue<Objednavka*>();

	//arrayListObjednavokNaVybavenie->push(new Objednavka(10, new Odosielatel("BA", 10), new Adresat("MA", 15.5)));

	// prekladisko má vždy aspoň pár dronov pri vytváraní
	this->pridajDron(new Dron(eDrony::JEDEN, set_get_SerioveCislo()));
	this->pridajDron(new Dron(eDrony::DVA, set_get_SerioveCislo()));
	this->pridajDron(new Dron(eDrony::DVA, set_get_SerioveCislo()));
}

Prekladisko::~Prekladisko()
{
	for (Dron * dron : *arrayListDronov) {
		delete dron;
	}
	delete arrayListDronov;

	frontObjednavok->clear();
	delete frontObjednavok;
}

void Prekladisko::pridajDron(Dron * novyDron)
{
	// TODO sort by date
	//int index = 0;
	//for (Vozidlo *vozidlo : *arrayListVozidiel) {
	//	// FIXED zaraďovanie podľa dátumu aj času
	//	if (noveVozidlo->getDatumaCasEvidencie() < vozidlo->getDatumaCasEvidencie()) {
	//		arrayListVozidiel->insert(noveVozidlo, index);
	//		return;
	//	}
	//	index++;
	//}
	//arrayListVozidiel->add(noveVozidlo);
	arrayListDronov->add(novyDron);
}

void Prekladisko::pridajObjednavku(Objednavka * objednavka)
{
	frontObjednavok->push(objednavka);
}
void Prekladisko::spracujObjednavky()
{
	cout << "Spracovavam objednavky v regione: " << this->dajRegion() << endl;
	while (!frontObjednavok->isEmpty())
	{
		cout << "Spracovavam objednavku: " << endl;
		frontObjednavok->pop()->toString();
	}
}

void Prekladisko::vypisZoznamDronov() {
	std::cout << "Vypisujem vsetkych dronov pre prekladisko z okresu - " << region_ << std::endl;
	for (Dron * dron : *arrayListDronov) {
		dron->toString();
	}
}

Dron * Prekladisko::vyberDrona(double hmotnostZasielky, double vzdialenost, string casVytvoreniaObjednavky)
{
	// NOTE výber správneho drona na doručenie zásielky od adresáta/odosielatela z/do skladiska
	Dron* kandidatNaDrona = nullptr;

	for (Dron * dron : *arrayListDronov) {
		// premenna tak dam toho prveho
		// hľadaj tu najlepšieho drona
		// dron musí byť voľný;
		if (!dron->unesieZasielku(hmotnostZasielky)) { continue; }
		if (!dron->jeVolny()) {
			if (kandidatNaDrona == nullptr) {
				kandidatNaDrona = dron;
				continue;
			}
			else {
				kandidatNaDrona = dajLelpšiehoDrona(dron, kandidatNaDrona);
				continue;
			}
		}

		if (dron->zvladneLet(vzdialenost) &&
			dron->stihnePriletietPreZasielku(vzdialenost))
		{
			return dron;
		}

	}

	//std::cout << "Takuto objednavku nezvladne dorucit ziaden dron" << std::endl;
	return (kandidatNaDrona == nullptr) ? NULL : kandidatNaDrona;
}

Dron* Prekladisko::dajLelpšiehoDrona(Dron* dron1, Dron* dron2) {
	if (dron1->getNosnost() == dron2->getNosnost()) {
		return (dron1->getAktualnaKapacitaBaterie() > dron2->getAktualnaKapacitaBaterie()) ? dron1 : dron2;
	}
	else {
		return (dron1->getNosnost() < dron2->getNosnost()) ? dron1 : dron2;
	}
}

std::string Prekladisko::set_get_SerioveCislo()
{
	int pom = ++unikatneSerioveCislo_;
	std::string formated = std::string(6 - std::to_string(pom).length(), '0') + std::to_string(pom);
	serioveCislo_ = region_ + formated;
	return serioveCislo_;
}

