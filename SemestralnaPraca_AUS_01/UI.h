#pragma once
#include "structures/heap_monitor.h"
#include "structures/array/array.h"
#include "structures/list/array_list.h"
#include "Firma.h"

class UI
{
public:
	UI();
	~UI();
	void hlavneMenu();
	int getInputFromUser(std::string consoleOutput);
	void pridajVsetkyPrekladiska();
private:
	Firma * firma;
};