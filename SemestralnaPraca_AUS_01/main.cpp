// #pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS -> because of time 
#include "structures/heap_monitor.h"
#include "UI.h"

int main()
{
	// TODO vrátiť sa k výberu drona -> zoptimalizovať
	// TODO pri spracovańí objednávok, prechádzam každý sklad a potom každého drona, ktorý je v tom sklade -> znížiť zložitosť 

	initHeapMonitor();
	//std::string datumaCasEvidencie_ = Datum::getAktualnyDatumaCas();
	//time_t testtime = Datum::string_to_time_t(datumaCasEvidencie_);
	UI *userInterface = new UI();
	userInterface->hlavneMenu();

	delete userInterface;
	system("pause");
	return 0;
}

