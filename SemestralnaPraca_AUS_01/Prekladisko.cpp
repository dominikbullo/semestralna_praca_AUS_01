#include "Prekladisko.h"
#include "Dron.h"


Prekladisko::Prekladisko(std::string region)
{
	region_ = region;
	arrayDronov = new structures::ArrayList<Dron*>();

	// prekladisko má vždy aspoò dvoch dronov pri vytváraní
	arrayDronov->add(new Dron(eDrony::JEDEN));
	arrayDronov->add(new Dron(eDrony::DVA));
	arrayDronov->add(new Dron(eDrony::DVA));
}


Prekladisko::~Prekladisko()
{
	for (Dron * dron : *arrayDronov) {
		delete dron;
	}
	delete arrayDronov;
}

void Prekladisko::pridajDron(Dron * novyDron)
{
	// TODO sort by date
	arrayDronov->add(novyDron);
}

void Prekladisko::vypisZoznamDronov() {
	std::cout << "Vypisujem vsetkych dronov pre prekladisko z okresu - " << region_ << std::endl;
	for (Dron * dron : *arrayDronov) {
		dron->toString();
	}
}

Dron * Prekladisko::vyberDrona(double hmotnostZasielky, double vzdialenost)
{
	// TODO pokraèovanie -> výber správneho drona na doruèenie zásielky od adresáta/odosielatela z/do skladiska
	for (Dron * dron : *arrayDronov) {
		if (dron->zvladneLet(vzdialenost) && dron->unesieZasielku(hmotnostZasielky)) {
			return dron;
		}
	}
	return 0;
}