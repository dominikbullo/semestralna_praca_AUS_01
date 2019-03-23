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
	std::string getStrInputFromUser(std::string consoleOutput);
	int getIntInputFromUser(std::string consoleOutput);
	void pridajVsetkyPrekladiska();
	void menuVozidla(std::string text, bool clearTerminal);
	void menuVozidla(bool clearTerminal) {
		menuVozidla("", clearTerminal);
	};
	void menuPrekladiska(std::string text, bool clearTerminal);
	void menuPrekladiska(bool clearTerminal) {
		menuPrekladiska("", clearTerminal);
	};
	void menuObjednavky();
private:
	Firma * firma;
	Datum * datumUI;
	structures::Array<std::string> *poleRegionov;
};