#include "Prekladisko.h"
#include "Dron.h"

int Prekladisko::unikatneSerioveCislo_ = 000000;

Prekladisko::Prekladisko(std::string region)
{
	region_ = region;
	arrayListDronov = new structures::ArrayList<Dron*>();
	unikatneSerioveCislo_ = 000000;

	// prekladisko má vždy aspoò dvoch dronov pri vytváraní
	this->pridajDron(new Dron(eDrony::JEDEN, getSerioveCislo()));
	this->pridajDron(new Dron(eDrony::JEDEN, getSerioveCislo()));
	this->pridajDron(new Dron(eDrony::JEDEN, getSerioveCislo()));
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
	setSerioveCislo();
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
	// TODO výber správneho drona na doruèenie zásielky od adresáta/odosielatela z/do skladiska
	for (Dron * dron : *arrayListDronov) {
		if (dron->zvladneLet(vzdialenost) &&
			dron->unesieZasielku(hmotnostZasielky) &&
			dron->stihnePriletietPreZasielku(vzdialenost))
		{
			return dron;
		}
	}
	return 0;
}

void Prekladisko::setSerioveCislo()
{
	int pom = ++unikatneSerioveCislo_;
	std::string formated = std::string(6 - std::to_string(pom).length(), '0') + std::to_string(pom);
	serioveCislo_ = region_ + formated;
}


