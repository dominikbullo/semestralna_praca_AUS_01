#pragma once
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
	std::string dajOkres() {
		return okres_;
	}
private:
	structures::ArrayList<Dron*> * arrayDronov;
	std::string okres_;
};

