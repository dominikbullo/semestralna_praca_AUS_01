#pragma once
#include "structures/heap_monitor.h"
#include "structures/list/array_list.h"
#include "Dron.h"

class Prekladisko
{
public:
	Prekladisko();
	~Prekladisko();
	void pridajDron(Dron * novyDron);
private:
	structures::ArrayList<Dron*> * arrayDronov;
};

