// #pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS -> because of time 
#include "structures/heap_monitor.h"
#include "UI.h"

int main()
{
	// TODO PREKLADISKA MAJU PEVNY POCET!!! ARRAY!!!!!

	// TODO 29.03
	// TODO: Uloženie a načítanie aktuálneho stavu evidencie do/zo súboru.
	// TODO: Bug fix battery.


	// TODO do 31.3
	// TODO Vyber vozidiel v centralnom sklade, zaslanie zasielky do lokalnych prekladisk
	// TODO Odoslanie z prekladisk userom
	// TODO: Vypísanie nasledujúcich sumárnych štatistík:

	initHeapMonitor();
	UI *userInterface = new UI();
	userInterface->hlavneMenu();

	delete userInterface;
	system("pause");
	return 0;
}
