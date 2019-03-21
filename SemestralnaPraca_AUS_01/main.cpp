#include <iostream>
#include "structures/heap_monitor.h"
#include "structures/array/array.h"
#include "structures/list/array_list.h"
#include "Vozidlo.h"
#include "Datum.h"
#include "Dron.h"
#include "Firma.h"
#include "main.h"
#include "Objednavka.h"
#include "Konstatnty.h"

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS -> because of time 

int main()
{
	initHeapMonitor();

	Firma * firma = new Firma("AoE");

	// NOTE 1: Pridanie nového vozidla do vozového parku spoločnosti AoE. Vozidlo je jednoznačne
	//		identifikovateľné na základe ŠPZ.Každé vozidlo má definovanú nosnosť(v tonách)a prevádzkové náklady(EUR / región).

	// TODO pridávanie vozidla -> SPZ spýtať sa čo a ako ? 
	firma->pridajVozidlo(new Vozidlo(10, 100));
	firma->pridajVozidlo(new Vozidlo(14560, 1045550));

	// NOTE 2: Vypísanie zoznamu vozidiel podľa dátumu zaradenia do evidencie. Vypíše sa ŠPZ,
	//		nosnosť vozidla a celkové prevádzkové náklady od dátumu zaradenia do evidencie.

	// NOTE -> zaraďujem postupne, je treba podľa dátumu ?
	firma->vypisZoznamVozidiel();

	// NOTE 3: Pridanie nového dronu do lokálneho prekladiska. Dron je charakterizovaný sériovým
	//		číslom a typom, ktorý určuje jeho ďalšie atribúty, ktorými sú nosnosť, rýchlosť, doba letu a doba nabíjania.

		// TODO 3.1 : Pridanie všetkých prekladísk, na základe char arrayu okresov
					// NOTE -> cyklus zo súboru načítam kraje a ich názvy a vytvorím -> aká údajová štruktúra na uloženie všetkých prekladísk ? Pole ?

	//char * okresy[23] = { "MA","BA","TT","TN","NR","KN","PD","LV","CA","MT","BB","ZV","KA","NO","LM","LC","RA","SL","SN","PO","KE","HE","MI" };

	pridajVsetkyPrekladiska(firma);

	firma->dajPrekladiskoPodlaRegionu("MA")->pridajDron(new Dron(eDrony::JEDEN));

	// NOTE 4: Vypísanie všetkých dronov evidovaných v zadanom lokálnom prekladisku. Pri
	//každom drone sa vypíše jeho dátum zaradenia do evidencie, typ, celkový počet nalietaných hodín a celkový počet prepravených zásielok.


	//firma->dajPrekladiskoPodlaRegionu("MA")->vypisZoznamDronov();
	//firma->dajPrekladiskoPodlaRegionu("BA")->vypisZoznamDronov();


	// TODO 5: Vytvorenie novej objednávky. V rámci objednávky sa definuje:
	//			 hmotnosť zásielky(kg; napr. 1, 4kg), ktorá má byť prepravená,
	//			 miesto(región a vzdialenosť odosielateľa od lokálneho prekladiska v príslušnom regióne), kde ju má dron vyzdvihnúť,
	//			 miesto(región a vzdialenosť adresáta od lokálneho prekladiska v príslušnom regióne), kam má byť zásielka doručená.
	//		Pri vytváraní objednávky je nutné kontrolovať, či nedôjde k jej zamietnutiu zo strany AoE.
	//		Dokončená objednávka je zaradená do frontu objednávok čakajúcich na spracovanie.


			// TODO -> ASK -> Trieda zákazník je potrebná ? 
			// TODO -> ASK -> evidencia ako samostatná trieda ? alebo priamo vo firme/prekladisku ? 
	//Odosielatel* Jozko = new Odosielatel("BA", 35);
	//Adresat* Ferko = new Adresat("MA", 50.75);

	Dron* dron = new Dron(eDrony::JEDEN);
	std::cout << (dron->zvladneLet(55) ? "ano" : "nie") << std::endl;

	firma->vytvorObjednavku(2.75, new Odosielatel("BA", 35), new Adresat("MA", 50.75));

	// TODO 6: Naplánovanie vyzdvihnutia zásielky u odosielateľa. V rámci tohto bodu sa skontroluje,
	//		či je v lokálnom prekladisku dron, prostredníctvom ktorého je možné vyzdvihnúť zásielku,
	//		ktorá je priradená k prvej objednávke nachádzajúcej sa vo fronte objednávok čakajúcich na spracovanie.
	//		
	//		Vhodný dron sa vyberie podľa nasledujúcich pravidiel :
	//				 dron musí byť voľný;
	//				 ak viac dronov spĺňa vyššie špecifikované pravidlá, prioritne sa použije drons najmenšou nosnosťou,
	//					ktorá ešte umožní prepraviť danú zásielku;
	//				 ak viac dronov spĺňa vyššie špecifikované pravidlá, vyberie sa ten, ktorý je aktuálne najviac nabitý.
	//		
	//		Ak sú všetky drony, ktoré sa nachádzajú v lokálnom prekladisku, aktuálne vyťažené
	//		alebo majú naplánovanú už inú akciu, je vypočítaný čas, za ktorý sa môže dostať dron,
	//		ktorý dokáže vyzdvihnúť danú zásielku a ktorý ako prvý dokončí svoju aktuálne
	//		vykonávanú úlohu, k odosielateľovi.Ak je tento čas väčší ako jedna hodina, zákazník je
	//		o tom informovaný a objednávku môže zrušiť.Ak objednávku nezruší, tak bude
	//		obslúžený vyššie uvedeným dronom.

	// TODO 7: Návrat vozidiel do centrálneho skladu. V rámci tohto kroku sa vrátia všetky vozidlá z jednotlivých regiónov
	//		do centrálneho skladu. Vozidlá počas spiatočnej cesty prechádzajú jednotlivými regiónmi (ak sa jedná o prvú jazdu vozidla,
	//		nájdite vhodný spôsob získania týchto regiónov) a v lokálnych prekladiskách sú do nich naložené zásielky,
	//		ktoré počas dňa pozbierali drony. Po návrate vozidiel do centrálneho skladu dôjde k vyloženiu zásielok a
	//		aktualizujú sa celkové prevádzkové náklady jednotlivých vozidiel podľa nasledujúceho vzorca:
	//		2 * prevádzkové náklady * počet regiónov, v ktorých vozidlo operovalo


	// TODO 8:Naplnenie vozidiel v centrálnom sklade zásielkami. Počas tejto operácie sa zásielky v centrálnom sklade roztriedia do jednotlivých vozidiel podľa nasledujúcich pravidiel:
	//		 regiónom, do ktorých v daný deň nesmeruje žiadna zásielka, bude pre(prípadný) zber zásielok na konci dňa priradené vozidlo s minimálnymi celkovými prevádzkovými nákladmi;
	//		 pri nakladaní nesmie byť prekročená nosnosť vozidla;
	//		 na prepravu zásielok z centrálneho skladu do lokálnych prekladísk by mal byť použitý minimálny počet vozidiel(pre jednoduchosť je možné teoreticky uvažovať s jediným vozidlom 
	//		schopným obslúžiť všetky regióny).



	delete firma;
	system("pause");
	return 0;
}

void pridajVsetkyPrekladiska(Firma * firma)
{
	firma->pridajPrekladisko(new Prekladisko("MA"));
	firma->pridajPrekladisko(new Prekladisko("BA"));
	firma->pridajPrekladisko(new Prekladisko("TT"));
	firma->pridajPrekladisko(new Prekladisko("TN"));
	firma->pridajPrekladisko(new Prekladisko("NR"));
	firma->pridajPrekladisko(new Prekladisko("KN"));
	firma->pridajPrekladisko(new Prekladisko("PD"));
	firma->pridajPrekladisko(new Prekladisko("LV"));
	firma->pridajPrekladisko(new Prekladisko("CA"));
	firma->pridajPrekladisko(new Prekladisko("MT"));
	firma->pridajPrekladisko(new Prekladisko("BB"));
	firma->pridajPrekladisko(new Prekladisko("ZV"));
	firma->pridajPrekladisko(new Prekladisko("KA"));
	firma->pridajPrekladisko(new Prekladisko("NO"));
	firma->pridajPrekladisko(new Prekladisko("LM"));
	firma->pridajPrekladisko(new Prekladisko("LC"));
	firma->pridajPrekladisko(new Prekladisko("RA"));
	firma->pridajPrekladisko(new Prekladisko("SL"));
	firma->pridajPrekladisko(new Prekladisko("SN"));
	firma->pridajPrekladisko(new Prekladisko("PO"));
	firma->pridajPrekladisko(new Prekladisko("KE"));
	firma->pridajPrekladisko(new Prekladisko("HE"));
	firma->pridajPrekladisko(new Prekladisko("MI"));
}
