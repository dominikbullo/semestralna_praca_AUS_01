#pragma once
#include<string>

#include "structures/heap_monitor.h"
#include "structures/list/array_list.h"
#include "Dron.h"


class Prekladisko
{
public:
	Prekladisko(std::string okres);
	~Prekladisko();
	void pridajDron(Dron * novyDron);
	void vypisZoznamDronov();
	Dron * vyberDrona(double hmotnostZasielky, double vzdialenost);
	std::string dajOkres() {
		return region_;
	}
private:
	structures::ArrayList<Dron*> * arrayDronov;
	std::string region_;
};

