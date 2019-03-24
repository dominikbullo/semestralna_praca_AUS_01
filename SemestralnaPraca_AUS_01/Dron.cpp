#include "Dron.h"


Dron::Dron(const eDrony typDronu, std::string serioveCislo)
{
	typ_ = typDronu;
	serioveCislo_ = serioveCislo;
	datumEvidencie_ = Datum::getAktualnyDatumaCas();

	// evidujem bud˙ce objedn·vky, ktorÈ m· dron vybaviù
	arrayListObjednavokNaVybavenie = new structures::ArrayList<Objednavka*>();

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
void Dron::pridajObjednavku(Objednavka * novaObjednavka) {

	int index = 0;
	for (Objednavka *objednavka : *arrayListObjednavokNaVybavenie) {
		if (novaObjednavka->getDatumaCasVytvorenia() < objednavka->getDatumaCasVytvorenia())
			arrayListObjednavokNaVybavenie->insert(objednavka, index);
		return;
	}
	index++;

	arrayListObjednavokNaVybavenie->add(novaObjednavka);
}

void Dron::toString()
{
	std::cout << "Datum zaradenia do prevadzky - " << this->datumEvidencie_ <<
		"\t Seriove cislo - " << this->serioveCislo_ <<
		"\t TYP - " << ((typ_ == eDrony::JEDEN) ? "jeden" : "dva") << "\t celkovyPocetNalietanychHodin - " <<
		this->celkovyPocetNalietanychHodin << "\t celkovyPocetPrepravenychZasielok - " <<
		this->celkovyPocetPrepravenychZasielok << std::endl;
}