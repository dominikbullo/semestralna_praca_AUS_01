#include "Prekladisko.h"
#include "Dron.h"

int Prekladisko::unikatneSerioveCislo_ = 000000;

Prekladisko::Prekladisko(std::string region)
{
	region_ = region;
	arrayListDronov = new structures::ArrayList<Dron*>();
	unikatneSerioveCislo_ = 000000;

	// prekladisko m� v�dy aspo� dvoch dronov pri vytv�ran�
	this->pridajDron(new Dron(eDrony::JEDEN, set_get_SerioveCislo()));
	this->pridajDron(new Dron(eDrony::DVA, set_get_SerioveCislo()));
	this->pridajDron(new Dron(eDrony::JEDEN, set_get_SerioveCislo()));
}

Prekladisko::~Prekladisko()
{
	for (Dron * dron : *arrayListDronov) {
		delete dron;
	}
	delete arrayListDronov;
}

void Prekladisko::pridajDron(Dron * novyDron)
{
	// TODO sort by date
	//int index = 0;
	//for (Vozidlo *vozidlo : *arrayListVozidiel) {
	//	// FIXED zara�ovanie pod�a d�tumu aj �asu
	//	if (noveVozidlo->getDatumaCasEvidencie() < vozidlo->getDatumaCasEvidencie()) {
	//		arrayListVozidiel->insert(noveVozidlo, index);
	//		return;
	//	}
	//	index++;
	//}
	//arrayListVozidiel->add(noveVozidlo);
	arrayListDronov->add(novyDron);
}

void Prekladisko::vypisZoznamDronov() {
	std::cout << "Vypisujem vsetkych dronov pre prekladisko z okresu - " << region_ << std::endl;
	for (Dron * dron : *arrayListDronov) {
		dron->toString();
	}
}

Dron * Prekladisko::vyberDrona(double hmotnostZasielky, double vzdialenost)
{
	// TODO v�ber spr�vneho drona na doru�enie z�sielky od adres�ta/odosielatela z/do skladiska
	for (Dron * dron : *arrayListDronov) {
		if (dron->zvladneLet(vzdialenost) &&
			dron->unesieZasielku(hmotnostZasielky) &&
			dron->stihnePriletietPreZasielku(vzdialenost))
		{
			return dron;
		}
	}
	std::cout << "Takuto objednavku nezvladne dorucit ziaden dron" << std::endl;
	return NULL;
}

std::string Prekladisko::set_get_SerioveCislo()
{
	int pom = ++unikatneSerioveCislo_;
	std::string formated = std::string(6 - std::to_string(pom).length(), '0') + std::to_string(pom);
	serioveCislo_ = region_ + formated;
	return serioveCislo_;
}


