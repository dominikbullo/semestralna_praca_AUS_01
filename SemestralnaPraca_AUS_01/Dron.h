#pragma once
#include <string>
#include <iostream>
#include <stdio.h>

#include "Konstatnty.h"
#include "Datum.h"

class Dron
{
public:
	Dron(const eDrony typDronu);
	~Dron();
	void setSerialNumber();
	void toString();
private:
	eDrony typ_;
	std::string datumEvidencie_;

	int nosnost_;  //pis to v kilach
	int primernaRychlost_;
	int maxDobaLetu_;
	int casNaNabitie10Percent_;
	int celkovyPocetPrepravenychZasielok = 0;
	float celkovyPocetNalietanychHodin = 0.0;

};

