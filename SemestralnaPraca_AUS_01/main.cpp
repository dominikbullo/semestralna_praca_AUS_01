#include <iostream>
#include "structures/heap_monitor.h"
#include "structures/array/array.h"
#include "structures/list/array_list.h"
#include "Vozidlo.h"
#include "Datum.h"
#include "Dron.h"
#include "Firma.h"

int main()
{
	initHeapMonitor();
	// TODO 2: Vypísanie zoznamu vozidiel pod¾a dátumu zaradenia do evidencie. Vypíše sa ŠPZ,
	// nosnos vozidla a celkové prevádzkové náklady od dátumu zaradenia do evidencie.

	// TODO 3: Pridanie nového dronu do lokálneho prekladiska. Dron je charakterizovaný sériovým
	//èíslom a typom, ktorý urèuje jeho ïalšie atribúty, ktorými sú nosnos, rýchlos, doba letu a doba nabíjania.

	// TODO 4: Vypísanie všetkých dronov evidovaných v zadanom lokálnom prekladisku. Pri
	//každom drone sa vypíše jeho dátum zaradenia do evidencie, typ, celkový poèet nalietaných hodín a celkový poèet prepravených zásielok.

	Firma * firma = new Firma();
	firma->pridajVozidlo(new Vozidlo(10, 100));
	firma->pridajVozidlo(new Vozidlo(10, 100));
	firma->pridajVozidlo(new Vozidlo(10, 100));
	firma->pridajVozidlo(new Vozidlo(10, 100));
	firma->pridajVozidlo(new Vozidlo(10, 100));

	Dron * dron1 = new Dron(eDrony::JEDEN);
	Dron * dron2 = new Dron(eDrony::DVA);



	system("pause");
	return 0;
}