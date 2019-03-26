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


	//Dron* kandidatNaDrona = nullptr;

	//for (Dron * dron : *arrayListDronov_) {
	//	// premenna tak dam toho prveho
	//	// hľadaj tu najlepšieho drona
	//	// dron musí byť voľný;
	//	if (!dron->unesieZasielku(hmotnostZasielky)) { continue; }
	//	if (!dron->jeVolny()) {
	//		if (kandidatNaDrona == nullptr) {
	//			kandidatNaDrona = dron;
	//			continue;
	//		}
	//		else {
	//			kandidatNaDrona = dajLelpšiehoDrona(dron, kandidatNaDrona);
	//			continue;
	//		}
	//	}

	//	if (dron->zvladneLet(vzdialenost) &&
	//		dron->stihnePriletietPreZasielku(vzdialenost))
	//	{
	//		return dron;
	//	}

	//}

	////std::cout << "Takuto objednavku nezvladne dorucit ziaden dron" << std::endl;
	//return (kandidatNaDrona == nullptr) ? NULL : kandidatNaDrona;
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

