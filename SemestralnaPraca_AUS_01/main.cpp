#include <iostream>
#include "structures/heap_monitor.h"
#include "structures/array/array.h"
#include "structures/list/array_list.h"
#include "Vozidlo.h"
#include "Datum.h"
#include "Dron.h"
#include "Firma.h"
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS -> because of time 

int main()
{
	initHeapMonitor();
	Firma * firma = new Firma();

	// TODO 1: Pridanie nového vozidla do vozového parku spoločnosti AoE. Vozidlo je jednoznačne
	// identifikovateľné na základe ŠPZ.Každé vozidlo má definovanú nosnosť(v tonách)a prevádzkové náklady(EUR / región).
	firma->pridajVozidlo(new Vozidlo(10, 100));
	firma->pridajVozidlo(new Vozidlo(14560, 1045550));

	// TODO 2: Vypísanie zoznamu vozidiel podľa dátumu zaradenia do evidencie. Vypíše sa ŠPZ,
	// nosnosť vozidla a celkové prevádzkové náklady od dátumu zaradenia do evidencie.


	// TODO 3: Pridanie nového dronu do lokálneho prekladiska. Dron je charakterizovaný sériovým
	//číslom a typom, ktorý určuje jeho ďalšie atribúty, ktorými sú nosnosť, rýchlosť, doba letu a doba nabíjania.

		// TODO 3.1 : Pridanie všetkých prekladísk, na základe char arrayu okresov

		// TODO 3.2 : Pridanie drona zaradeného do evidencie

	Prekladisko* prekladiskoZilina = new Prekladisko("ZA");
	firma->pridajPrekladisko(prekladiskoZilina);


	// TODO 4: Vypísanie všetkých dronov evidovaných v zadanom lokálnom prekladisku. Pri
	//každom drone sa vypíše jeho dátum zaradenia do evidencie, typ, celkový počet nalietaných hodín a celkový počet prepravených zásielok.


	// TODO 5: Vytvorenie novej objednávky. V rámci objednávky sa definuje:
	/*	 hmotnosť zásielky(kg; napr. 1, 4kg), ktorá má byť prepravená,
		 miesto(región a vzdialenosť odosielateľa od lokálneho prekladiska v príslušnom regióne), kde ju má dron vyzdvihnúť,
		 miesto(región a vzdialenosť adresáta od lokálneho prekladiska v príslušnom regióne), kam má byť zásielka doručená.
		Pri vytváraní objednávky je nutné kontrolovať, či nedôjde k jej zamietnutiu zo strany AoE.
	Dokončená objednávka je zaradená do frontu objednávok čakajúcich na spracovanie.
	*/

	// TODO 6: Naplánovanie vyzdvihnutia zásielky u odosielateľa. V rámci tohto bodu sa skontroluje,
	/* či je v lokálnom prekladisku dron, prostredníctvom ktorého je možné vyzdvihnúť zásielku,
	ktorá je priradená k prvej objednávke nachádzajúcej sa vo fronte objednávok čakajúcich na spracovanie.
	Vhodný dron sa vyberie podľa nasledujúcich pravidiel :
	 dron musí byť voľný;
	 ak viac dronov spĺňa vyššie špecifikované pravidlá, prioritne sa použije drons najmenšou nosnosťou,
		ktorá ešte umožní prepraviť danú zásielku;
	 ak viac dronov spĺňa vyššie špecifikované pravidlá, vyberie sa ten, ktorý je aktuálne najviac nabitý.

	Ak sú všetky drony, ktoré sa nachádzajú v lokálnom prekladisku, aktuálne vyťažené
	alebo majú naplánovanú už inú akciu, je vypočítaný čas, za ktorý sa môže dostať dron,
	ktorý dokáže vyzdvihnúť danú zásielku a ktorý ako prvý dokončí svoju aktuálne
	vykonávanú úlohu, k odosielateľovi.Ak je tento čas väčší ako jedna hodina, zákazník je
	o tom informovaný a objednávku môže zrušiť.Ak objednávku nezruší, tak bude
	obslúžený vyššie uvedeným dronom.
	*/



	//Dron * dron1 = new Dron(eDrony::JEDEN);
	//Dron * dron2 = new Dron(eDrony::DVA);



	system("pause");
	return 0;
}