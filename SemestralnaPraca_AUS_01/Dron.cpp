#include "Dron.h"
#include "Konstatnty.h"


Dron::Dron(const eDrony typDronu)
{
	typ_ = typDronu;

	switch (typDronu) {
	case eDrony::JEDEN:
		nosnost_ = (int)dronTypuJeden::NOSNOST;
		primernaRychlost_ = (int)dronTypuJeden::PRIEMERNA_RYCHLOST;
		maxDobaLetu_ = (int)dronTypuJeden::MAX_DOBA_LETU;
		casNaNabitie10Percent_ = (int)dronTypuJeden::CAS_NABITIE_10_PERCENT;
		break;

	case eDrony::DVA:
		nosnost_ = (int)dronTypuDva::NOSNOST;
		primernaRychlost_ = (int)dronTypuDva::PRIEMERNA_RYCHLOST;
		maxDobaLetu_ = (int)dronTypuDva::MAX_DOBA_LETU;
		casNaNabitie10Percent_ = (int)dronTypuDva::CAS_NABITIE_10_PERCENT;
		break;

	default:
		std::cout << "Neviem vytvorit takyto dron" << std::endl;
	}
}

Dron::~Dron()
{
}

void Dron::setSerialNumber() {
}
