// #pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS -> because of time 
#include "structures/heap_monitor.h"
#include "UI.h"

int main()
{

	// TODO Nosnoť vozidla skontroluj
	// TODO Zasielky sa duplikuju aj vo fronte, aj vo vozidle, zisti, či to nie je chyba, ale nemala by byť
	// TODO Vyber vozidiel v centralnom sklade, zaslanie zasielky do lokalnych prekladisk
	// TODO Odoslanie z prekladisk userom

	initHeapMonitor();
	UI *userInterface = new UI();
	userInterface->hlavneMenu();

	delete userInterface;
	system("pause");
	return 0;
}
