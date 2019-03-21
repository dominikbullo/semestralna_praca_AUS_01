#include "Prekladisko.h"
#include "Dron.h"



Prekladisko::Prekladisko(std::string okres)
{
	okres_ = okres;
	arrayDronov = new structures::ArrayList<Dron*>();
}


Prekladisko::~Prekladisko()
{
	for (Dron * dron : *arrayDronov) {
		delete dron;
	}
	delete arrayDronov;
}

void Prekladisko::pridajDron(Dron* novyDron)
{
	arrayDronov->add(novyDron);
}

void Prekladisko::vypisZoznamDronov() {
	std::cout << "Vypisujem vsetkych dronov pre prekladisko z okresu - " << okres_ << std::endl;
	for (Dron * dron : *arrayDronov) {
		dron->toString();
	};
}
