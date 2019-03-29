// #pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS -> because of time 
#include "structures/heap_monitor.h"
#include "UI.h"

int main()
{

	// TODO: Vypísanie nasledujúcich sumárnych štatistík:
	// TODO: Uloženie a načítanie aktuálneho stavu evidencie do/zo súboru.

	initHeapMonitor();
	UI *userInterface = new UI();
	userInterface->hlavneMenu();

	delete userInterface;
	system("pause");
	return 0;
}

