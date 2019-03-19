#pragma once
#include "structures/heap_monitor.h"
#include "structures/list/array_list.h"
#include "Vozidlo.h"

class Firma
{
public:
	Firma();
	~Firma();
	void pridajVozidlo(Vozidlo * noveVozidlo);
private:
	structures::ArrayList<Vozidlo*> * arrayVozidiel;
};

