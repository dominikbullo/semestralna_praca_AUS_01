#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS -> because of time 
#include "structures/heap_monitor.h"
#include "UI.h"

int main()
{
	// TODO 23.03 -> pridať pole regionov
	// TODO 23.03 -> pridať autu pole regionov ako trasu ktorou pôjde

	// TODO 23.03 -> meneźovanie času, kontrola dronu, či stihne vyzdvihnuť zasielku
	// TODO 23.03 -> uloženie vozidla do Arraylistu podľa dátumu

	// TODO 23.03 ->!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// TODO 23.03 -> POROZMÝŠĽAŤ ako evidovať objednávku, kde si ju ukladať a čo s ňou potom spraviť
	// TODO 23.03 ->!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	// TODO 23.03 -> či naloženie zásielky neprekročí hmotnosť auta
	// TODO 23.03 -> dron musí byť voľný;
	// TODO 23.03 -> ak viac dronov spĺňa vyššie špecifikované pravidlá, prioritne sa použije dron s najmenšou nosnosťou, ktorá ešte umožní prepraviť danú zásielku;
	// TODO 23.03 -> ak viac dronov spĺňa vyššie špecifikované pravidlá, vyberie sa ten, ktorý je aktuálne najviac nabitý.

	// TODO 24.03 -> 7 - 8 - 11 -> ukladanie ho súbora ?

	initHeapMonitor();
	UI *userInterface = new UI();
	userInterface->hlavneMenu();

	delete userInterface;
	system("pause");
	return 0;
}

