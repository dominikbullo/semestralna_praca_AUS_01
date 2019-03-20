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
	for (Dron * dron : *arrayDronov) {
		dron->toString();
	};
}