#pragma once
#include "Konstatnty.h"
#include <string>
#include <iostream>
#include <stdio.h>

class Dron
{
public:
	Dron(const eDrony typDronu);
	~Dron();
private:
	eDrony typ_;
	int nosnost_;  //pis to v kilach
	int primernaRychlost_;
	int maxDobaLetu_;
	int casNaNabitie10Percent_;
};

