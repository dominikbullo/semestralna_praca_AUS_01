#pragma once
#include "structures/heap_monitor.h"

enum class eStavObjednavky
{
	PRIJATA = 1,
	ZAMIETNUTA = 2,
	ZRUSENA = 3,
	ZREALIZOVANA = 4,
	PRIPRAVENA = 5
};


enum class eDrony
{
	JEDEN,
	DVA
};

enum class dronTypuJeden {
	NOSNOST = 2,
	PRIEMERNA_RYCHLOST = 80,
	MAX_DOBA_LETU = 40,
	CAS_NABITIE_10_PERCENT = 3
};

enum class dronTypuDva {
	NOSNOST = 5,
	PRIEMERNA_RYCHLOST = 40,
	MAX_DOBA_LETU = 60,
	CAS_NABITIE_10_PERCENT = 5

};