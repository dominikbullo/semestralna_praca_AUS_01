// #pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS -> because of time 
#include "structures/heap_monitor.h"
#include "UI.h"

int main()
{
	// TODO vypisaniePoctuKilometrovPodlaTypuDrona
	// TODO Uložiť a načítať centrálny sklad

	//// TODO 
	//// prekladsiko->prijmiZasielky(vozidlo)
	//firma->vylozZasielkyvPrekladiskach();
	// TODO Vyber vozidiel v centralnom sklade, zaslanie zasielky do lokalnych prekladisk


	initHeapMonitor();
	UI *userInterface = new UI();
	userInterface->hlavneMenu();

	delete userInterface;
	system("pause");
	return 0;
}
