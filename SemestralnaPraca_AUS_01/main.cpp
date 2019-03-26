// #pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS -> because of time 
#include "structures/heap_monitor.h"
#include "UI.h"

int main()
{
	// TODO: nabíjanie drona -> ako

	// TODO: Návrat áut do centrálneho skladu
	// TODO: Naplnenie vozidiel v centrálnom sklade zásielkami.
	// TODO: Transport zásielok z centrálneho skladu do lokálnych prekladísk.
	// TODO: Odovzdanie zásielky adresátovi vo zvolenom lokálnom prekladisku.
	// TODO: Vypísanie nasledujúcich sumárnych štatistík:
	// TODO: Uloženie a načítanie aktuálneho stavu evidencie do/zo súboru.

	initHeapMonitor();
	//std::string datumaCasEvidencie_ = Datum::getAktualnyDatumaCas();
	//time_t testtime = Datum::string_to_time_t(datumaCasEvidencie_);
	UI *userInterface = new UI();
	userInterface->hlavneMenu();

	delete userInterface;
	system("pause");
	return 0;
}

