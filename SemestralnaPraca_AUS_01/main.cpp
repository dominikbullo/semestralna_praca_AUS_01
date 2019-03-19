#include <iostream>
#include "structures/heap_monitor.h"
#include "structures/array/array.h"
#include "structures/list/array_list.h"
#include "Vozidlo.h"
#include "Firma.h"


int main()
{
	initHeapMonitor();
	// TODO 2: Vypísanie zoznamu vozidiel pod¾a dátumu zaradenia do evidencie. Vypíše sa ŠPZ,
	// nosnos vozidla a celkové prevádzkové náklady od dátumu zaradenia do evidencie.

	// TODO 3: Pridanie nového dronu do lokálneho prekladiska. Dron je charakterizovanı sériovım
	//èíslom a typom, ktorı urèuje jeho ïalšie atribúty, ktorımi sú nosnos, rıchlos, doba letu a doba nabíjania.

	// TODO 4: Vypísanie všetkıch dronov evidovanıch v zadanom lokálnom prekladisku. Pri
	//kadom drone sa vypíše jeho dátum zaradenia do evidencie, typ, celkovı poèet nalietanıch hodín a celkovı poèet prepravenıch zásielok.

	Firma * firma = new Firma();


	system("pause");
	return 0;
}