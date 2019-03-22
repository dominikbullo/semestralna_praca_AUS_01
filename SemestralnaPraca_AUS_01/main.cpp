#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS -> because of time 
#include "structures/heap_monitor.h"
#include "UI.h"

int main()
{
	initHeapMonitor();
	UI *userInterface = new UI();
	userInterface->hlavneMenu();

	delete userInterface;
	system("pause");
	return 0;
}

