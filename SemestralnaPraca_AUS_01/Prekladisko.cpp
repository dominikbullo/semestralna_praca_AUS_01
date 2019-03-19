#include "Prekladisko.h"
#include "Dron.h"



Prekladisko::Prekladisko(std::string okres)
{
	okres_ = okres;
	arrayDronov = new structures::ArrayList<Dron*>();
}


Prekladisko::~Prekladisko()
{
}

void Prekladisko::pridajDron(Dron* novyDron)
{
}